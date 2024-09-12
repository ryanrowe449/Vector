//constructors and destructor
template<class T> Vector<T>::Vector(){
    theSize = 0;
    theCapacity = 0;
    array = new T[theCapacity];
    //array = nullptr;
}
template<class T> Vector<T>::Vector(const Vector &rhs){
    theSize = rhs.theSize;
    theCapacity = rhs.theCapacity;
    array = new T[theCapacity];
    for (int i = 0; i < theSize; i++){
        array[i] = rhs.array[i];
    }
}
//taken from book
template<class T> const Vector<T> &Vector<T>::operator=(const Vector &rhs){
    Vector copy = rhs;			// calling copy constructor
    std::swap( *this, copy );
    return *this;
}
//taken from book
template<class T> Vector<T> &Vector<T>::operator=(Vector &&rhs){
    std::swap( theSize, rhs.theSize );
    std::swap( theCapacity, rhs.theCapacity );
    std::swap( array, rhs.array );
        
    return *this;
}
//taken from book
template<class T> Vector<T>::Vector(Vector &&rhs):theSize(rhs.theSize), theCapacity(rhs.theCapacity), array(rhs.array){
    rhs.array = nullptr;
    rhs.theSize = 0;
    rhs.theCapacity = 0;
}
//modified from book
template<class T> Vector<T>::Vector(int num, const T& val){
    theSize = num;
    theCapacity = num;
    array = new T[theCapacity];
    for (int i = 0; i < theSize; i++){
        array[i] = val;
    }
}
template<class T> Vector<T>::Vector(const_iterator start, const_iterator end): theSize(0), theCapacity(0), array(nullptr) {
    int newsize = end - start;
    if (newsize <= 0) {
        return;
    }
    reserve(newsize);
    for (const_iterator itr = start; itr != end; ++itr) {
        push_back(*itr);
    }
}
template<class T> Vector<T>::~Vector(){
    delete [] array;
}
//other stuff
//taken from book
template<class T> bool Vector<T>::empty() const{
    return size() == 0;
}
template<class T> void Vector<T>::reserve(int newCapacity){
    if (newCapacity < theSize) return;
    if (newCapacity == 0) newCapacity = 1;
    T *newArray = new T[newCapacity];
    for(int i = 0; i < theSize; i++){
        newArray[i] = array[i];
    }
    theCapacity = newCapacity;
    delete [] array;
    array = newArray;
}
template<class T> typename Vector<T>::iterator Vector<T>::erase(iterator itr){
    if (itr == end())return end();
    iterator next = itr+1;
    if (next != end()) {
        for (iterator cur = itr; next != end(); ++cur, ++next) {
            *cur = *next;
        }
    }
    theSize--;
    return itr;
}
template<class T> typename Vector<T>::iterator Vector<T>::erase(iterator start, iterator end){
    int remove = end - start;
    if (start < begin() || end > Vector<T>::end() || start >= end) {
        return Vector<T>::end();
    }
    iterator high = end;
    iterator low = start;
    while (high != Vector<T>::end()){
        *low = *high;
        low++;
        high++;
    }
    theSize -= remove;
    return start;
}
template<class T> void Vector<T>::push_back(const T & val){
    if(theSize == theCapacity)reserve(2 * theCapacity);
    array[theSize++] = val;
}
template<class T> void Vector<T>::pop_back(){
    theSize--;
}
template<class T> void Vector<T>::clear(){
    theSize = 0;
}
template<class T> int Vector<T>::size() const{
    return theSize;
}
template<class T> int Vector<T>::capacity() const{
    return theCapacity;
}
template<class T> T& Vector<T>::front(){
    return array[0];
}
template<class T> const T& Vector<T>::front() const{
    return array[0];
}
template<class T> T& Vector<T>::back(){
    return array[theSize - 1];
}
template<class T> const T& Vector<T>::back() const{
    return array[theSize - 1];
}
template<class T> void Vector<T>::print(std::ostream& os, char ofc) const{
    for (const_iterator itr = begin(); itr != end(); itr++) {
       os << *itr;
       if (itr + 1 != end())os << ofc;
    }
}
//taken from book
template<class T> T& Vector<T>::operator[](int index){
    return array[index];
}
//taken from book
template<class T> const T& Vector<T>::operator[](int index) const{
    return array[index];
}
template<class T> T& Vector<T>::at(int loc){
    return array[loc];
}
template<class T> const T& Vector<T>::at(int loc) const{
    return array[loc];
}
//iterator stuff
template<class T> typename Vector<T>::iterator Vector<T>::begin(){
    return &array[0];
}
template<class T> typename Vector<T>::iterator Vector<T>::end(){
    return &array[theSize];
}
template<class T> typename Vector<T>::const_iterator Vector<T>::begin() const{
    return &array[0];
}
template<class T> typename Vector<T>::const_iterator Vector<T>::end() const{
    return &array[theSize];
}
template<class T> typename Vector<T>::iterator Vector<T>::insert(iterator itr, const T& val){
    //how many items b/w itr and first element; keeping in case iterator changes due to reserve
    int index = itr - begin();
    if (theSize == theCapacity) {
        reserve(2 * theCapacity);
        itr = begin() + index;
    }
    for (iterator cur = end(); cur > itr; --cur) {
        *cur = *(cur - 1);
    }
    *itr = val;
    theSize++;
    return itr;
}
//taken from book
template<class T> void Vector<T>::resize(int num, T val){
    if(num > theCapacity)reserve(num * 2);
    theSize = num;
}
template<class T> void Vector<T>::doubleCapacity(){
    if (theCapacity == 0)theCapacity = 1;
    else theCapacity *= 2;
}
//overloads
template<typename T>std::ostream &operator<<(std::ostream &os, const Vector<T> &v) {
    for (typename Vector<T>::const_iterator itr = v.begin(); itr != v.end(); ++itr) {
        os << *itr;
        if (itr + 1 != v.end()) {
            os << ' ';
        }
    }
    return os;
}
template<typename T> bool operator==(const Vector<T> & lhs, const Vector<T> &rhs){
    if(lhs.size() != rhs.size()) return false;
    for (int i = 0; i < lhs.size(); i++){
        if(lhs[i] != rhs[i]) return false;
    }
    return true;
}
template<typename T> bool operator!=(const Vector<T> & lhs, const Vector<T> &rhs){
    if (lhs == rhs)return false;
    return true;
}