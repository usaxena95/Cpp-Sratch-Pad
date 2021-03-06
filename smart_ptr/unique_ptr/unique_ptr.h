#include <iostream>

template <typename T> class unique_ptr {
public:
  unique_ptr(T *ptr) : ptr_(ptr) {
    std::cout << "unique_ptr(T*) constructed for \"" << ptr_->str() << "\"\n";
  }
  T *get() const { return ptr_; }
  T *release() {
    std::cout << "unique_ptr::release called for \"" << ptr_->str() << "\"\n";
    T *ret = ptr_;
    ptr_ = nullptr;
    return ret;
  }
  void reset(T *p = nullptr) {
    if (ptr_ != p) {
      this->~unique_ptr();
      ptr_ = p;
    }
  }
  unique_ptr(unique_ptr &&other) { // move constructor
    if (ptr_ != other.get()) {
      std::cout << "unique_ptr(&&) move contructor called for \"" << ptr_->str()
                << "\"\n";
      this->~unique_ptr();
      ptr_ = other.release();
    }
  }
  unique_ptr &operator=(unique_ptr &&other) {
    if (ptr_ != other.get()) {
      std::cout << "unique_ptr(&&) move contructor called for \"" << ptr_->str()
                << "\"\n";
      this->~unique_ptr();
      ptr_ = other.release();
    }
    return *this;
  }

  T *operator->() { return ptr_; }

  ~unique_ptr() {
    if (ptr_ != nullptr) {
      std::cout << "unique_ptr desctructed for \"" << ptr_->str() << "\"\n";
      delete ptr_;
    }
  }

private:
  T *ptr_;
};
