#ifndef MYSTL_BASIC_STRING_H_
#define MYSTL_BASIC_STRING_H_

// ���ͷ�ļ�����һ��ģ���� basic_string
// ���ڱ�ʾ�ַ�������

#include <iostream>			//�ַ������������

#include "iterator.h"		//������
#include "memory.h"			//�߼��Ķ�̬�ڴ����
#include "functional.h"		//�º������ϣ����
#include "exceptdef.h"		//�쳣

namespace mystl {

// char_traits

template <class CharType>struct char_traits {		//char����
	typedef CharType char_type;

	static size_t length(const char_type* str) {		//�����ַ�������
		size_t len = 0;
		for (; *str != char_type(0); ++str) {
			++len;
		}
		return len;
	}

	static char_type* copy(char_type* dst, const char_type* src, size_t n) {	//�����ַ���
		MYSTL_DEBUG(src + n <= dst || dst + n <= src);
		char_type* r = dst;
		fror(; n != 0; --n, ++dst, ++src) {
			*dst = *src;
		}
		return r;
	}

	static char_type* move(char_type* dst, const char_type* src, size_t n) {	//�ƶ��ַ���
		char_type* r = dst;
		if (dst < src) {
			for (; n != 0; --n, ++dst, ++src)
				*dst = *src;
		}
		else if (src < dst) {
			dst += n;
			src += n;
			for (; n != 0; --n)
				*--dst = *--src;
		}
		return r;
	}

	static char_type* fill(char_type* dst, char_type* ch, size_t count) {		//����ַ���
		char_type* r = dst;
		for (; count > 0; --count, ++dst)
			*dst = ch;
		return r;
	}
};

// Partialized. char_traits<char>
template <>struct char_trais<char> {	//ƫ�ػ�ģ����
	typedef char char_type;

	//���´����ӿ�ȥ����C���Եĺ���
	static size_t length(const char_type* str)noexcept {	//�����ַ�������
		return std::strlen(str);
	}

	static int compare(const char_type* s1, const char_type* s2, size_t n)noexcept {	//�Ƚ��ַ���
		return std::memcmp(s1, s2, n);
	}

	static char_type* copy(char_type* dst, const char_type* src, size_t n) noexcept {	//�����ַ���
		MYSTL_DEBUG(src + n <= dst || dst + n <= src);
		return static_cast<char_type*>(std::memcpy(dst, src, n));
	}

	static char_type* move(char_type* dst, const char_type* src, size_t n) noexcept		//�ƶ��ַ���
	{
		return static_cast<char_type*>(std::memmove(dst, src, n));
	}

	static char_type* fill(char_type* dst, char_type ch, size_t count) noexcept			//����ַ���
	{
		return static_cast<char_type*>(std::memset(dst, ch, count));
	}
};

// Partialized. char_traits<wchar_t>	���ֽڵ�char
template <>
struct char_traits<wchar_t> {			//ģ��ƫ�ػ���
	
	typedef wchar_t char_type;

	//���´����ӿڵ��ÿ��ֽڵĺ���
	static size_t length(const char_type* str) noexcept			//�����ַ�������
	{
		return std::wcslen(str);
	}

	static int compare(const char_type* s1, const char_type* s2, size_t n) noexcept		//�Ƚ��ַ���
	{
		return std::wmemcmp(s1, s2, n);
	}

	static char_type* copy(char_type* dst, const char_type* src, size_t n) noexcept		//�����ַ���
	{
		MYSTL_DEBUG(src + n <= dst || dst + n <= src);
		return static_cast<char_type*>(std::wmemcpy(dst, src, n));
	}

	static char_type* move(char_type* dst, const char_type* src, size_t n) noexcept		//�ƶ��ַ���
	{
		return static_cast<char_type*>(std::wmemmove(dst, src, n));
	}

	static char_type* fill(char_type* dst, char_type ch, size_t count) noexcept			//����ַ���
	{
		return static_cast<char_type*>(std::wmemset(dst, ch, count));
	}
};

// Partialized. char_traits<char16_t> 16λ��char
template <>
struct char_traits<char16_t>
{
	typedef char16_t char_type;

	static size_t length(const char_type* str) noexcept		//�����ַ�������
	{
		size_t len = 0;
		for (; *str != char_type(0); ++str)
			++len;
		return len;
	}

	static int compare(const char_type* s1, const char_type* s2, size_t n) noexcept		//�Ƚ��ַ���
	{
		for (; n != 0; --n, ++s1, ++s2)
		{
			if (*s1 < *s2)
				return -1;
			if (*s2 < *s1)
				return 1;
		}
		return 0;
	}

	static char_type* copy(char_type* dst, const char_type* src, size_t n) noexcept		//�����ַ���
	{
		MYSTL_DEBUG(src + n <= dst || dst + n <= src);
		char_type* r = dst;
		for (; n != 0; --n, ++dst, ++src)
			*dst = *src;
		return r;
	}

	static char_type* move(char_type* dst, const char_type* src, size_t n) noexcept		//�ƶ��ַ���
	{
		char_type* r = dst;
		if (dst < src)
		{
			for (; n != 0; --n, ++dst, ++src)
				*dst = *src;
		}
		else if (src < dst)
		{
			dst += n;
			src += n;
			for (; n != 0; --n)
				*--dst = *--src;
		}
		return r;
	}

	static char_type* fill(char_type* dst, char_type ch, size_t count) noexcept			//����ַ���
	{
		char_type* r = dst;
		for (; count > 0; --count, ++dst)
			*dst = ch;
		return r;
	}
};

// Partialized. char_traits<char32_t> 32λ��char
template <>
struct char_traits<char32_t>
{
	typedef char32_t char_type;

	static size_t length(const char_type* str) noexcept		//�����ַ�������
	{
		size_t len = 0;
		for (; *str != char_type(0); ++str)
			++len;
		return len;
	}

	static int compare(const char_type* s1, const char_type* s2, size_t n) noexcept		//�Ƚ��ַ���
	{
		for (; n != 0; --n, ++s1, ++s2)
		{
			if (*s1 < *s2)
				return -1;
			if (*s2 < *s1)
				return 1;
		}
		return 0;
	}

	static char_type* copy(char_type* dst, const char_type* src, size_t n) noexcept		//�����ַ���
	{
		MYSTL_DEBUG(src + n <= dst || dst + n <= src);
		char_type* r = dst;
		for (; n != 0; --n, ++dst, ++src)
			*dst = *src;
		return r;
	}

	static char_type* move(char_type* dst, const char_type* src, size_t n) noexcept		//�ƶ��ַ���
	{
		char_type* r = dst;
		if (dst < src)
		{
			for (; n != 0; --n, ++dst, ++src)
				*dst = *src;
		}
		else if (src < dst)
		{
			dst += n;
			src += n;
			for (; n != 0; --n)
				*--dst = *--src;
		}
		return r;
	}

	static char_type* fill(char_type* dst, char_type ch, size_t count) noexcept			//����ַ���
	{
		char_type* r = dst;
		for (; count > 0; --count, ++dst)
			*dst = ch;
		return r;
	}
};


// ��ʼ�� basic_string ���Է������С buffer ��С�����ܱ�����
#define STRING_INIT_SIZE 32

// ģ���� basic_string
// ����һ�����ַ����ͣ�������������ȡ�ַ����͵ķ�ʽ��ȱʡʹ�� mystl::char_traits
template <class CharType, class CharTraits = mystl::char_traits<CharType>> class basic_string {

public:
	//��ȡ���ͱ�
	typedef CharTraits                               traits_type;
	typedef CharTraits                               char_traits;

	//�ռ��������ͱ�
	typedef mystl::allocator<CharType>               allocator_type;
	typedef mystl::allocator<CharType>               data_allocator;

	//��Ƕ�ͱ�
	typedef typename allocator_type::value_type      value_type;
	typedef typename allocator_type::pointer         pointer;
	typedef typename allocator_type::const_pointer   const_pointer;
	typedef typename allocator_type::reference       reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::size_type       size_type;
	typedef typename allocator_type::difference_type difference_type;

	//�������ͱ�
	typedef value_type* iterator;
	typedef const value_type* const_iterator;
	typedef mystl::reverse_iterator<iterator>        reverse_iterator;
	typedef mystl::reverse_iterator<const_iterator>  const_reverse_iterator;

	//��ȡ�ռ��������ͱ�
	allocator_type get_allocator() { return allocator_type(); }

	//��̬����
	static_assert(std::is_pod<CharType>::value, "Character type of basic_string must be a POD");	//�ж��Ƿ�POD�ͱ�
	static_assert(std::is_same<CharType, typename traits_type::char_type>::value,			//�ж��ͱ��Ƿ���ͬ
		"CharType must be same as traits_type::char_type");

public:
	// ĩβλ�õ�ֵ����:
	// if (str.find('a') != string::npos) { /* do something */ }	
	static constexpr size_type npos = static_cast<size_type>(-1);//����һ���޷��ŵ����ͣ���string���׿����ɵ�����С

private:
	iterator	buffer_;  // �����ַ�������ʼλ��
	size_type	size_;    // ��С
	size_type	cap_;     // ����

public:
	// ���졢���ơ��ƶ�����������

	basic_string() noexcept			//���캯��
	{
		try_init();
	}

	basic_string(size_type n, value_type ch)		//���캯����ʹ�ó�ʼ���б�
		:buffer_(nullptr), size_(0), cap_(0)
	{
		fill_init(n, ch);
	}

	basic_string(const basic_string& other, size_type pos)		//���캯��
		:buffer_(nullptr), size_(0), cap_(0)
	{
		init_from(other.buffer_, pos, other.size_ - pos);
	}
	basic_string(const basic_string& other, size_type pos, size_type count)		//���캯��
		:buffer_(nullptr), size_(0), cap_(0)
	{
		init_from(other.buffer_, pos, count);
	}

	basic_string(const_pointer str)							//���캯��
		:buffer_(nullptr), size_(0), cap_(0)
	{
		init_from(str, 0, char_traits::length(str));
	}
	basic_string(const_pointer str, size_type count)		//���캯��
		:buffer_(nullptr), size_(0), cap_(0)
	{
		init_from(str, 0, count);
	}

	template <class Iter, typename std::enable_if<
		mystl::is_input_iterator<Iter>::value, int>::type = 0>
		basic_string(Iter first, Iter last)							//���캯��ģ��
	{
		copy_init(first, last, iterator_category(first));
	}

	basic_string(const basic_string& rhs)							//�������캯��
		:buffer_(nullptr), size_(0), cap_(0)
	{
		init_from(rhs.buffer_, 0, rhs.size_);
	}
	basic_string(basic_string&& rhs) noexcept						//�ƶ����캯��
		:buffer_(rhs.buffer_), size_(rhs.size_), cap_(rhs.cap_)
	{
		rhs.buffer_ = nullptr;
		rhs.size_ = 0;
		rhs.cap_ = 0;
	}

	basic_string& operator=(const basic_string& rhs);				//������ֵ��������أ���ֵ�汾
	basic_string& operator=(basic_string&& rhs) noexcept;			//������ֵ��������أ���ֵ�汾

	basic_string& operator=(const_pointer str);						//������ֵ�����
	basic_string& operator=(value_type ch);							//������ֵ�����

	~basic_string() { destroy_buffer(); }							//��������

public:
	// ��������ز���
	//���������
	iterator               begin()         noexcept
	{
		return buffer_;
	}
	const_iterator         begin()   const noexcept
	{
		return buffer_;
	}
	iterator               end()           noexcept
	{
		return buffer_ + size_;
	}
	const_iterator         end()     const noexcept
	{
		return buffer_ + size_;
	}

	//���������
	reverse_iterator       rbegin()        noexcept
	{
		return reverse_iterator(end());
	}
	const_reverse_iterator rbegin()  const noexcept
	{
		return const_reverse_iterator(end());
	}
	reverse_iterator       rend()          noexcept
	{
		return reverse_iterator(begin());
	}
	const_reverse_iterator rend()    const noexcept
	{
		return const_reverse_iterator(begin());
	}

	//const������
	const_iterator         cbegin()  const noexcept
	{
		return begin();
	}
	const_iterator         cend()    const noexcept
	{
		return end();
	}
	const_reverse_iterator crbegin() const noexcept
	{
		return rbegin();
	}
	const_reverse_iterator crend()   const noexcept
	{
		return rend();
	}

	// ������ز���
	bool      empty()    const noexcept
	{
		return size_ == 0;
	}

	size_type size()     const noexcept
	{
		return size_;
	}
	size_type length()   const noexcept
	{
		return size_;
	}
	size_type capacity() const noexcept
	{
		return cap_;
	}
	size_type max_size() const noexcept
	{
		return static_cast<size_type>(-1);
	}

	void      reserve(size_type n);
	void      shrink_to_fit();
	
	// ����Ԫ����ز���
	reference       operator[](size_type n)
	{
		MYSTL_DEBUG(n <= size_);
		if (n == size_)
			*(buffer_ + n) = value_type();
		return *(buffer_ + n);
	}
	const_reference operator[](size_type n) const
	{
		MYSTL_DEBUG(n <= size_);
		if (n == size_)
			*(buffer_ + n) = value_type();
		return *(buffer_ + n);
	}

	reference       at(size_type n)
	{
		THROW_OUT_OF_RANGE_IF(n >= size_, "basic_string<Char, Traits>::at()"
			"subscript out of range");
		return (*this)[n];
	}
	const_reference at(size_type n) const
	{
		THROW_OUT_OF_RANGE_IF(n >= size_, "basic_string<Char, Traits>::at()"
			"subscript out of range");
		return (*this)[n];
	}

	reference       front()
	{
		MYSTL_DEBUG(!empty());
		return *begin();
	}
	const_reference front() const
	{
		MYSTL_DEBUG(!empty());
		return *begin();
	}

	reference       back()
	{
		MYSTL_DEBUG(!empty());
		return *(end() - 1);
	}
	const_reference back()  const
	{
		MYSTL_DEBUG(!empty());
		return *(end() - 1);
	}

	const_pointer   data()  const noexcept
	{
		return to_raw_pointer();
	}
	const_pointer   c_str() const noexcept
	{
		return to_raw_pointer();
	}
	
	// ����ɾ����ز���

	// insert
	iterator insert(const_iterator pos, value_type ch);
	iterator insert(const_iterator pos, size_type count, value_type ch);

	template <class Iter>
	iterator insert(const_iterator pos, Iter first, Iter last);


	// push_back / pop_back
	void     push_back(value_type ch)
	{
		append(1, ch);
	}
	void     pop_back()
	{
		MYSTL_DEBUG(!empty());
		--size_;
	}

	// append	ƴ�Ӳ���
	basic_string& append(size_type count, value_type ch);

	basic_string& append(const basic_string& str)
	{
		return append(str, 0, str.size_);
	}
	basic_string& append(const basic_string& str, size_type pos)
	{
		return append(str, pos, str.size_ - pos);
	}
	basic_string& append(const basic_string& str, size_type pos, size_type count);

	basic_string& append(const_pointer s)
	{
		return append(s, char_traits::length(s));
	}
	basic_string& append(const_pointer s, size_type count);

	template <class Iter, typename std::enable_if<
		mystl::is_input_iterator<Iter>::value, int>::type = 0>
		basic_string& append(Iter first, Iter last)
	{
		return append_range(first, last);
	}

	// erase 	�Ƴ�
	iterator erase(const_iterator pos);
	iterator erase(const_iterator first, const_iterator last);

	// resize	���ô�С
	void resize(size_type count)
	{
		resize(count, value_type());
	}
	void resize(size_type count, value_type ch);

	//clear		���
	void     clear() noexcept
	{
		size_ = 0;
	}

	// basic_string ��ز���

	// compare	�Ƚϲ���
	int compare(const basic_string& other) const;
	int compare(size_type pos1, size_type count1, const basic_string& other) const;
	int compare(size_type pos1, size_type count1, const basic_string& other,
		size_type pos2, size_type count2 = npos) const;
	int compare(const_pointer s) const;
	int compare(size_type pos1, size_type count1, const_pointer s) const;
	int compare(size_type pos1, size_type count1, const_pointer s, size_type count2) const;

	// substr	��һ���ַ����л�ȡ�Ӵ�
	basic_string substr(size_type index, size_type count = npos)
	{
		count = mystl::min(count, size_ - index);
		return basic_string(buffer_ + index, buffer_ + index + count);
	}

	// replace	�滻
	basic_string& replace(size_type pos, size_type count, const basic_string& str)
	{
		THROW_OUT_OF_RANGE_IF(pos > size_, "basic_string<Char, Traits>::replace's pos out of range");
		return replace_cstr(buffer_ + pos, count, str.buffer_, str.size_);
	}
	basic_string& replace(const_iterator first, const_iterator last, const basic_string& str)
	{
		MYSTL_DEBUG(begin() <= first && last <= end() && first <= last);
		return replace_cstr(first, static_cast<size_type>(last - first), str.buffer_, str.size_);
	}

	basic_string& replace(size_type pos, size_type count, const_pointer str)
	{
		THROW_OUT_OF_RANGE_IF(pos > size_, "basic_string<Char, Traits>::replace's pos out of range");
		return replace_cstr(buffer_ + pos, count, str, char_traits::length(str));
	}
	basic_string& replace(const_iterator first, const_iterator last, const_pointer str)
	{
		MYSTL_DEBUG(begin() <= first && last <= end() && first <= last);
		return replace_cstr(first, static_cast<size_type>(last - first), str, char_traits::length(str));
	}

	basic_string& replace(size_type pos, size_type count, const_pointer str, size_type count2)
	{
		THROW_OUT_OF_RANGE_IF(pos > size_, "basic_string<Char, Traits>::replace's pos out of range");
		return replace_cstr(buffer_ + pos, count, str, count2);
	}
	basic_string& replace(const_iterator first, const_iterator last, const_pointer str, size_type count)
	{
		MYSTL_DEBUG(begin() <= first && last <= end() && first <= last);
		return replace_cstr(first, static_cast<size_type>(last - first), str, count);

	}

	basic_string& replace(size_type pos, size_type count, size_type count2, value_type ch)
	{
		THROW_OUT_OF_RANGE_IF(pos > size_, "basic_string<Char, Traits>::replace's pos out of range");
		return replace_fill(buffer_ + pos, count, count2, ch);
	}
	basic_string& replace(const_iterator first, const_iterator last, size_type count, value_type ch)
	{
		MYSTL_DEBUG(begin() <= first && last <= end() && first <= last);
		return replace_fill(first, static_cast<size_type>(last - first), count, ch);
	}

	basic_string& replace(size_type pos1, size_type count1, const basic_string& str,
		size_type pos2, size_type count2 = npos)
	{
		THROW_OUT_OF_RANGE_IF(pos1 > size_ || pos2 > str.size_,
			"basic_string<Char, Traits>::replace's pos out of range");
		return replace_cstr(buffer_ + pos1, count1, str.buffer_ + pos2, count2);
	}

	template <class Iter, typename std::enable_if<
		mystl::is_input_iterator<Iter>::value, int>::type = 0>
		basic_string& replace(const_iterator first, const_iterator last, Iter first2, Iter last2)
	{
		MYSTL_DEBUG(begin() <= first && last <= end() && first <= last);
		return replace_copy(first, last, first2, last2);
	}

	// reverse	ԭ�ط�ת
	void reverse() noexcept;

	// swap		����
	void swap(basic_string& rhs) noexcept;

	// ������ز���

 // find
	size_type find(value_type ch, size_type pos = 0)                             const noexcept;
	size_type find(const_pointer str, size_type pos = 0)                         const noexcept;
	size_type find(const_pointer str, size_type pos, size_type count)            const noexcept;
	size_type find(const basic_string& str, size_type pos = 0)                   const noexcept;

	// rfind
	size_type rfind(value_type ch, size_type pos = npos)                         const noexcept;
	size_type rfind(const_pointer str, size_type pos = npos)                     const noexcept;
	size_type rfind(const_pointer str, size_type pos, size_type count)           const noexcept;
	size_type rfind(const basic_string& str, size_type pos = npos)               const noexcept;

	// find_first_of
	size_type find_first_of(value_type ch, size_type pos = 0)                    const noexcept;
	size_type find_first_of(const_pointer s, size_type pos = 0)                  const noexcept;
	size_type find_first_of(const_pointer s, size_type pos, size_type count)     const noexcept;
	size_type find_first_of(const basic_string& str, size_type pos = 0)          const noexcept;

	// find_first_not_of
	size_type find_first_not_of(value_type ch, size_type pos = 0)                const noexcept;
	size_type find_first_not_of(const_pointer s, size_type pos = 0)              const noexcept;
	size_type find_first_not_of(const_pointer s, size_type pos, size_type count) const noexcept;
	size_type find_first_not_of(const basic_string& str, size_type pos = 0)      const noexcept;

	// find_last_of
	size_type find_last_of(value_type ch, size_type pos = 0)                     const noexcept;
	size_type find_last_of(const_pointer s, size_type pos = 0)                   const noexcept;
	size_type find_last_of(const_pointer s, size_type pos, size_type count)      const noexcept;
	size_type find_last_of(const basic_string& str, size_type pos = 0)           const noexcept;

	// find_last_not_of
	size_type find_last_not_of(value_type ch, size_type pos = 0)                 const noexcept;
	size_type find_last_not_of(const_pointer s, size_type pos = 0)               const noexcept;
	size_type find_last_not_of(const_pointer s, size_type pos, size_type count)  const noexcept;
	size_type find_last_not_of(const basic_string& str, size_type pos = 0)       const noexcept;

	// count	ͳ���ַ�����
	size_type count(value_type ch, size_type pos = 0) const noexcept;

public:
	// ���� operator+= 
	basic_string& operator+=(const basic_string& str)
	{
		return append(str);
	}
	basic_string& operator+=(value_type ch)
	{
		return append(1, ch);
	}
	basic_string& operator+=(const_pointer str)
	{
		return append(str, str + char_traits::length(str));
	}

	// ���� operator >> / operatror <<
	friend std::istream& operator >> (std::istream& is, basic_string& str)
	{
		value_type* buf = new value_type[4096];
		is >> buf;
		basic_string tmp(buf);
		str = std::move(tmp);
		delete[]buf;
		return is;
	}

	friend std::ostream& operator << (std::ostream& os, const basic_string& str)
	{
		for (size_type i = 0; i < str.size_; ++i)
			os << *(str.buffer_ + i);
		return os;
	}

private:
	// helper functions ��������

	// init / destroy 
	void          try_init() noexcept;

	void          fill_init(size_type n, value_type ch);

	template <class Iter>
	void          copy_init(Iter first, Iter last, mystl::input_iterator_tag);
	template <class Iter>
	void          copy_init(Iter first, Iter last, mystl::forward_iterator_tag);

	void          init_from(const_pointer src, size_type pos, size_type n);

	void          destroy_buffer();

	// get raw pointer
	const_pointer to_raw_pointer() const;

	// shrink_to_fit
	void          reinsert(size_type size);

	// append
	template <class Iter>
	basic_string& append_range(Iter first, Iter last);

	// compare
	int compare_cstr(const_pointer s1, size_type n1, const_pointer s2, size_type n2) const;

	// replace
	basic_string& replace_cstr(const_iterator first, size_type count1, const_pointer str, size_type count2);
	basic_string& replace_fill(const_iterator first, size_type count1, size_type count2, value_type ch);
	template <class Iter>
	basic_string& replace_copy(const_iterator first, const_iterator last, Iter first2, Iter last2);

	// reallocate
	void          reallocate(size_type need);
	iterator      reallocate_and_fill(iterator pos, size_type n, value_type ch);
	iterator      reallocate_and_copy(iterator pos, const_iterator first, const_iterator last);

};	//class  basic_string

/*****************************************************************************************/

// ���Ƹ�ֵ������
template <class CharType, class CharTraits>
basic_string<CharType, CharTraits>&
basic_string<CharType, CharTraits>::
operator=(const basic_string& rhs)
{
	if (this != &rhs)
	{
		basic_string tmp(rhs);
		swap(tmp);		//��*this����
	}
	return *this;
}

// �ƶ���ֵ������
template <class CharType, class CharTraits>
basic_string<CharType, CharTraits>&
basic_string<CharType, CharTraits>::
operator=(basic_string&& rhs) noexcept
{
	destroy_buffer();
	buffer_ = rhs.buffer_;
	size_ = rhs.size_;
	cap_ = rhs.cap_;
	rhs.buffer_ = nullptr;
	rhs.size_ = 0;
	rhs.cap_ = 0;
	return *this;
}

// ��һ���ַ�����ֵ
template <class CharType, class CharTraits>
basic_string<CharType, CharTraits>&
basic_string<CharType, CharTraits>::
operator=(const_pointer str)
{
	const size_type len = char_traits::length(str);
	if (cap_ < len)
	{
		auto new_buffer = data_allocator::allocate(len + 1);	//�����ڴ�
		data_allocator::deallocate(buffer_);
		buffer_ = new_buffer;									//�ַ�����ֵ
		cap_ = len + 1;
	}
	char_traits::copy(buffer_, str, len);
	size_ = len;
	return *this;
}

// ��һ���ַ���ֵ
template <class CharType, class CharTraits>
basic_string<CharType, CharTraits>&
basic_string<CharType, CharTraits>::
operator=(value_type ch)
{
	if (cap_ < 1)
	{
		auto new_buffer = data_allocator::allocate(2);
		data_allocator::deallocate(buffer_);
		buffer_ = new_buffer;
		cap_ = 2;
	}
	*buffer_ = ch;
	size_ = 1;
	return *this;
}

// Ԥ������ռ�
template <class CharType, class CharTraits>
void basic_string<CharType, CharTraits>::
reserve(size_type n)
{
	if (cap_ < n)
	{
		THROW_LENGTH_ERROR_IF(n > max_size(), "n can not larger than max_size()"
			"in basic_string<Char,Traits>::reserve(n)");
		auto new_buffer = data_allocator::allocate(n);
		char_traits::move(new_buffer, buffer_, size_);
		buffer_ = new_buffer;
		cap_ = n;
	}
}

// ���ٲ��õĿռ�
template <class CharType, class CharTraits>
void basic_string<CharType, CharTraits>::
shrink_to_fit()
{
	if (size_ != cap_)
	{
		reinsert(size_);
	}
}

// �� pos ������һ��Ԫ��
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::iterator
basic_string<CharType, CharTraits>::
insert(const_iterator pos, value_type ch)
{
	iterator r = const_cast<iterator>(pos);
	if (size_ == cap_)
	{
		return reallocate_and_fill(r, 1, ch);
	}
	char_traits::move(r + 1, r, end() - r);
	++size_;
	*r = ch;
	return r;
}

// �� pos ������ n ��Ԫ��
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::iterator
basic_string<CharType, CharTraits>::
insert(const_iterator pos, size_type count, value_type ch)
{
	iterator r = const_cast<iterator>(pos);
	if (count == 0)
		return r;
	if (cap_ - size_ < count)
	{
		return reallocate_and_fill(r, count, ch);
	}
	if (pos == end())
	{
		char_traits::fill(end(), ch, count);
		size_ += count;
		return r;
	}
	char_traits::move(r + count, r, count);
	char_traits::fill(r, ch, count);
	size_ += count;
	return r;
}

// �� pos ������ [first, last) �ڵ�Ԫ��
template <class CharType, class CharTraits>
template <class Iter>
typename basic_string<CharType, CharTraits>::iterator
basic_string<CharType, CharTraits>::
insert(const_iterator pos, Iter first, Iter last)
{
	iterator r = const_cast<iterator>(pos);
	const size_type len = mystl::distance(first, last);
	if (len == 0)
		return r;
	if (cap_ - size_ < len)
	{
		return reallocate_and_copy(r, first, last);
	}
	if (pos == end())
	{
		mystl::uninitialized_copy(first, last, end());
		size_ += len;
		return r;
	}
	char_traits::move(r + len, r, len);
	mystl::uninitialized_copy(first, last, r);
	size_ += len;
	return r;
}

// ��ĩβ���� count �� ch
template <class CharType, class CharTraits>
basic_string<CharType, CharTraits>&
basic_string<CharType, CharTraits>::
append(size_type count, value_type ch)
{
	THROW_LENGTH_ERROR_IF(size_ > max_size() - count,
		"basic_string<Char, Tratis>'s size too big");
	if (cap_ - size_ < count)
	{
		reallocate(count);
	}
	char_traits::fill(buffer_ + size_, ch, count);
	size_ += count;
	return *this;
}

// ��ĩβ���� [str[pos] str[pos+count]) һ��
template <class CharType, class CharTraits>
basic_string<CharType, CharTraits>&
basic_string<CharType, CharTraits>::
append(const basic_string& str, size_type pos, size_type count)
{
	THROW_LENGTH_ERROR_IF(size_ > max_size() - count,
		"basic_string<Char, Tratis>'s size too big");
	if (count == 0)
		return *this;
	if (cap_ - size_ < count)
	{
		reallocate(count);
	}
	char_traits::copy(buffer_ + size_, str.buffer_ + pos, count);
	size_ += count;
	return *this;
}

// ��ĩβ���� [s, s+count) һ��
template <class CharType, class CharTraits>
basic_string<CharType, CharTraits>&
basic_string<CharType, CharTraits>::
append(const_pointer s, size_type count)
{
	THROW_LENGTH_ERROR_IF(size_ > max_size() - count,
		"basic_string<Char, Tratis>'s size too big");
	if (cap_ - size_ < count)
	{
		reallocate(count);
	}
	char_traits::copy(buffer_ + size_, s, count);
	size_ += count;
	return *this;
}

// ɾ�� pos ����Ԫ��
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::iterator
basic_string<CharType, CharTraits>::
erase(const_iterator pos)
{
	MYSTL_DEBUG(pos != end());
	iterator r = const_cast<iterator>(pos);
	char_traits::move(r, pos + 1, end() - pos - 1);
	--size_;
	return r;
}

// ɾ�� [first, last) ��Ԫ��
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::iterator
basic_string<CharType, CharTraits>::
erase(const_iterator first, const_iterator last)
{
	if (first == begin() && last == end())
	{
		clear();
		return end();
	}
	const size_type n = end() - last;
	iterator r = const_cast<iterator>(first);
	char_traits::move(r, last, n);
	size_ -= (last - first);
	return r;
}

// ����������С
template <class CharType, class CharTraits>
void basic_string<CharType, CharTraits>::
resize(size_type count, value_type ch)
{
	if (count < size_)
	{
		erase(buffer_ + count, buffer_ + size_);
	}
	else
	{
		append(count - size_, ch);
	}
}

// �Ƚ����� basic_string��С�ڷ��� -1�����ڷ��� 1�����ڷ��� 0
template <class CharType, class CharTraits>
int basic_string<CharType, CharTraits>::
compare(const basic_string& other) const
{
	return compare_cstr(buffer_, size_, other.buffer_, other.size_);
}

// �� pos1 �±꿪ʼ�� count1 ���ַ�����һ�� basic_string �Ƚ�
template <class CharType, class CharTraits>
int basic_string<CharType, CharTraits>::
compare(size_type pos1, size_type count1, const basic_string& other) const
{
	auto n1 = mystl::min(count1, size_ - pos1);
	return compare_cstr(buffer_ + pos1, n1, other.buffer_, other.size_);
}

// �� pos1 �±꿪ʼ�� count1 ���ַ�����һ�� basic_string �±� pos2 ��ʼ�� count2 ���ַ��Ƚ�
template <class CharType, class CharTraits>
int basic_string<CharType, CharTraits>::
compare(size_type pos1, size_type count1, const basic_string& other,
	size_type pos2, size_type count2) const
{
	auto n1 = mystl::min(count1, size_ - pos1);
	auto n2 = mystl::min(count2, other.size_ - pos2);
	return compare_cstr(buffer_, n1, other.buffer_, n2);
}

// ��һ���ַ����Ƚ�
template <class CharType, class CharTraits>
int basic_string<CharType, CharTraits>::
compare(const_pointer s) const
{
	auto n2 = char_traits::length(s);
	return compare_cstr(buffer_, size_, s, n2);
}

// ���±� pos1 ��ʼ�� count1 ���ַ�����һ���ַ����Ƚ�
template <class CharType, class CharTraits>
int basic_string<CharType, CharTraits>::
compare(size_type pos1, size_type count1, const_pointer s) const
{
	auto n1 = mystl::min(count1, size_ - pos1);
	auto n2 = char_traits::length(s);
	return compare_cstr(buffer_, n1, s, n2);
}

// ���±� pos1 ��ʼ�� count1 ���ַ�����һ���ַ�����ǰ count2 ���ַ��Ƚ�
template <class CharType, class CharTraits>
int basic_string<CharType, CharTraits>::
compare(size_type pos1, size_type count1, const_pointer s, size_type count2) const
{
	auto n1 = mystl::min(count1, size_ - pos1);
	return compare_cstr(buffer_, n1, s, count2);
}

// ��ת basic_string
template <class CharType, class CharTraits>
void basic_string<CharType, CharTraits>::
reverse() noexcept
{
	for (auto i = begin(), j = end(); i < j;)
	{
		mystl::iter_swap(i++, --j);
	}
}

// �������� basic_string
template <class CharType, class CharTraits>
void basic_string<CharType, CharTraits>::
swap(basic_string& rhs) noexcept
{
	if (this != &rhs)
	{
		mystl::swap(buffer_, rhs.buffer_);
		mystl::swap(size_, rhs.size_);
		mystl::swap(cap_, rhs.cap_);
	}
}

// ���±� pos ��ʼ�����ַ�Ϊ ch ��Ԫ�أ����ҵ��������±꣬���򷵻� npos
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::size_type
basic_string<CharType, CharTraits>::
find(value_type ch, size_type pos) const noexcept
{
	for (auto i = pos; i < size_; ++i)
	{
		if (*(buffer_ + i) == ch)
			return i;
	}
	return npos;
}

// ���±� pos ��ʼ�����ַ��� str�����ҵ�������ʼλ�õ��±꣬���򷵻� npos
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::size_type
basic_string<CharType, CharTraits>::
find(const_pointer str, size_type pos) const noexcept
{
	const auto len = char_traits::length(str);
	if (len == 0)
		return pos;
	if (size_ - pos < len)
		return npos;
	const auto left = size_ - len;
	for (auto i = pos; i <= left; ++i)
	{
		if (*(buffer_ + i) == *str)
		{
			size_type j = 1;
			for (; j < len; ++j)
			{
				if (*(buffer_ + i + j) != *(str + j))
					break;
			}
			if (j == len)
				return i;
		}
	}
	return npos;
}

// ���±� pos ��ʼ�����ַ��� str ��ǰ count ���ַ������ҵ�������ʼλ�õ��±꣬���򷵻� npos
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::size_type
basic_string<CharType, CharTraits>::
find(const_pointer str, size_type pos, size_type count) const noexcept
{
	if (count == 0)
		return pos;
	if (size_ - pos < count)
		return npos;
	const auto left = size_ - count;
	for (auto i = pos; i <= left; ++i)
	{
		if (*(buffer_ + i) == *str)
		{
			size_type j = 1;
			for (; j < count; ++j)
			{
				if (*(buffer_ + i + j) != *(str + j))
					break;
			}
			if (j == count)
				return i;
		}
	}
	return npos;
}

// ���±� pos ��ʼ�����ַ��� str�����ҵ�������ʼλ�õ��±꣬���򷵻� npos
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::size_type
basic_string<CharType, CharTraits>::
find(const basic_string& str, size_type pos) const noexcept
{
	const size_type count = str.size_;
	if (count == 0)
		return pos;
	if (size_ - pos < count)
		return npos;
	const auto left = size_ - count;
	for (auto i = pos; i <= left; ++i)
	{
		if (*(buffer_ + i) == str.front())
		{
			size_type j = 1;
			for (; j < count; ++j)
			{
				if (*(buffer_ + i + j) != str[j])
					break;
			}
			if (j == count)
				return i;
		}
	}
	return npos;
}

// ���±� pos ��ʼ�������ֵΪ ch ��Ԫ�أ��� find ����
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::size_type
basic_string<CharType, CharTraits>::
rfind(value_type ch, size_type pos) const noexcept
{
	if (pos >= size_)
		pos = size_ - 1;
	for (auto i = pos; i != 0; --i)
	{
		if (*(buffer_ + i) == ch)
			return i;
	}
	return front() == ch ? 0 : npos;
}

// ���±� pos ��ʼ��������ַ��� str���� find ����
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::size_type
basic_string<CharType, CharTraits>::
rfind(const_pointer str, size_type pos) const noexcept
{
	if (pos >= size_)
		pos = size_ - 1;
	const size_type len = char_traits::length(str);
	switch (len)
	{
	case 0:
		return pos;
	case 1:
	{
		for (auto i = pos; i != 0; --i)
		{
			if (*(buffer_ + i) == *str)
				return i;
		}
		return front() == *str ? 0 : npos;
	}
	default:
	{ // len >= 2
		for (auto i = pos; i >= len - 1; --i)
		{
			if (*(buffer_ + i) == *(str + len - 1))
			{
				size_type j = 1;
				for (; j < len; ++j)
				{
					if (*(buffer_ + i - j) != *(str + len - j - 1))
						break;
				}
				if (j == len)
					return i - len + 1;
			}
		}
		break;
	}
	}
	return npos;
}

// ���±� pos ��ʼ��������ַ��� str ǰ count ���ַ����� find ����
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::size_type
basic_string<CharType, CharTraits>::
rfind(const_pointer str, size_type pos, size_type count) const noexcept
{
	if (count == 0)
		return pos;
	if (pos >= size_)
		pos = size_ - 1;
	if (pos < count - 1)
		return npos;
	for (auto i = pos; i >= count - 1; --i)
	{
		if (*(buffer_ + i) == *(str + count - 1))
		{
			size_type j = 1;
			for (; j < count; ++j)
			{
				if (*(buffer_ + i - j) != *(str + count - j - 1))
					break;
			}
			if (j == count)
				return i - count + 1;
		}
	}
	return npos;
}

// ���±� pos ��ʼ��������ַ��� str���� find ����
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::size_type
basic_string<CharType, CharTraits>::
rfind(const basic_string& str, size_type pos) const noexcept
{
	const size_type count = str.size_;
	if (pos >= size_)
		pos = size_ - 1;
	if (count == 0)
		return pos;
	if (pos < count - 1)
		return npos;
	for (auto i = pos; i >= count - 1; --i)
	{
		if (*(buffer_ + i) == str[count - 1])
		{
			size_type j = 1;
			for (; j < count; ++j)
			{
				if (*(buffer_ + i - j) != str[count - j - 1])
					break;
			}
			if (j == count)
				return i - count + 1;
		}
	}
	return npos;
}

// ���±� pos ��ʼ���� ch ���ֵĵ�һ��λ��
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::size_type
basic_string<CharType, CharTraits>::
find_first_of(value_type ch, size_type pos) const noexcept
{
	for (auto i = pos; i < size_; ++i)
	{
		if (*(buffer_ + i) == ch)
			return i;
	}
	return npos;
}

// ���±� pos ��ʼ�����ַ��� s ���е�һ���ַ����ֵĵ�һ��λ��
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::size_type
basic_string<CharType, CharTraits>::
find_first_of(const_pointer s, size_type pos) const noexcept
{
	const size_type len = char_traits::length(s);
	for (auto i = pos; i < size_; ++i)
	{
		value_type ch = *(buffer_ + i);
		for (size_type j = 0; j < len; ++j)
		{
			if (ch == *(s + j))
				return i;
		}
	}
	return npos;
}

// ���±� pos ��ʼ�����ַ��� s 
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::size_type
basic_string<CharType, CharTraits>::
find_first_of(const_pointer s, size_type pos, size_type count) const noexcept
{
	for (auto i = pos; i < size_; ++i)
	{
		value_type ch = *(buffer_ + i);
		for (size_type j = 0; j < count; ++j)
		{
			if (ch == *(s + j))
				return i;
		}
	}
	return npos;
}

// ���±� pos ��ʼ�����ַ��� str ����һ���ַ����ֵĵ�һ��λ��
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::size_type
basic_string<CharType, CharTraits>::
find_first_of(const basic_string& str, size_type pos) const noexcept
{
	for (auto i = pos; i < size_; ++i)
	{
		value_type ch = *(buffer_ + i);
		for (size_type j = 0; j < str.size_; ++j)
		{
			if (ch == str[j])
				return i;
		}
	}
	return npos;
}

// ���±� pos ��ʼ������ ch ����ȵĵ�һ��λ��
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::size_type
basic_string<CharType, CharTraits>::
find_first_not_of(value_type ch, size_type pos) const noexcept
{
	for (auto i = pos; i < size_; ++i)
	{
		if (*(buffer_ + i) != ch)
			return i;
	}
	return npos;
}

// ���±� pos ��ʼ�������ַ��� s ����һ���ַ�����ȵĵ�һ��λ��
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::size_type
basic_string<CharType, CharTraits>::
find_first_not_of(const_pointer s, size_type pos) const noexcept
{
	const size_type len = char_traits::length(s);
	for (auto i = pos; i < size_; ++i)
	{
		value_type ch = *(buffer_ + i);
		for (size_type j = 0; j < len; ++j)
		{
			if (ch != *(s + j))
				return i;
		}
	}
	return npos;
}

// ���±� pos ��ʼ�������ַ��� s ǰ count ���ַ��в���ȵĵ�һ��λ��
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::size_type
basic_string<CharType, CharTraits>::
find_first_not_of(const_pointer s, size_type pos, size_type count) const noexcept
{
	for (auto i = pos; i < size_; ++i)
	{
		value_type ch = *(buffer_ + i);
		for (size_type j = 0; j < count; ++j)
		{
			if (ch != *(s + j))
				return i;
		}
	}
	return npos;
}

// ���±� pos ��ʼ�������ַ��� str ���ַ��в���ȵĵ�һ��λ��
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::size_type
basic_string<CharType, CharTraits>::
find_first_not_of(const basic_string& str, size_type pos) const noexcept
{
	for (auto i = pos; i < size_; ++i)
	{
		value_type ch = *(buffer_ + i);
		for (size_type j = 0; j < str.size_; ++j)
		{
			if (ch != str[j])
				return i;
		}
	}
	return npos;
}

// ���±� pos ��ʼ������ ch ��ȵ����һ��λ��
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::size_type
basic_string<CharType, CharTraits>::
find_last_of(value_type ch, size_type pos) const noexcept
{
	for (auto i = size_ - 1; i >= pos; --i)
	{
		if (*(buffer_ + i) == ch)
			return i;
	}
	return npos;
}

// ���±� pos ��ʼ�������ַ��� s ����һ���ַ���ȵ����һ��λ��
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::size_type
basic_string<CharType, CharTraits>::
find_last_of(const_pointer s, size_type pos) const noexcept
{
	const size_type len = char_traits::length(s);
	for (auto i = size_ - 1; i >= pos; --i)
	{
		value_type ch = *(buffer_ + i);
		for (size_type j = 0; j < len; ++j)
		{
			if (ch == *(s + j))
				return i;
		}
	}
	return npos;
}

// ���±� pos ��ʼ�������ַ��� s ǰ count ���ַ�����ȵ����һ��λ��
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::size_type
basic_string<CharType, CharTraits>::
find_last_of(const_pointer s, size_type pos, size_type count) const noexcept
{
	for (auto i = size_ - 1; i >= pos; --i)
	{
		value_type ch = *(buffer_ + i);
		for (size_type j = 0; j < count; ++j)
		{
			if (ch == *(s + j))
				return i;
		}
	}
	return npos;
}

// ���±� pos ��ʼ�������ַ��� str �ַ�����ȵ����һ��λ��
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::size_type
basic_string<CharType, CharTraits>::
find_last_of(const basic_string& str, size_type pos) const noexcept
{
	for (auto i = size_ - 1; i >= pos; --i)
	{
		value_type ch = *(buffer_ + i);
		for (size_type j = 0; j < str.size_; ++j)
		{
			if (ch == str[j])
				return i;
		}
	}
	return npos;
}

// ���±� pos ��ʼ������ ch �ַ�����ȵ����һ��λ��
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::size_type
basic_string<CharType, CharTraits>::
find_last_not_of(value_type ch, size_type pos) const noexcept
{
	for (auto i = size_ - 1; i >= pos; --i)
	{
		if (*(buffer_ + i) != ch)
			return i;
	}
	return npos;
}

// ���±� pos ��ʼ�������ַ��� s ���ַ��в���ȵ����һ��λ��
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::size_type
basic_string<CharType, CharTraits>::
find_last_not_of(const_pointer s, size_type pos) const noexcept
{
	const size_type len = char_traits::length(s);
	for (auto i = size_ - 1; i >= pos; --i)
	{
		value_type ch = *(buffer_ + i);
		for (size_type j = 0; j < len; ++j)
		{
			if (ch != *(s + j))
				return i;
		}
	}
	return npos;
}

// ���±� pos ��ʼ�������ַ��� s ǰ count ���ַ��в���ȵ����һ��λ��
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::size_type
basic_string<CharType, CharTraits>::
find_last_not_of(const_pointer s, size_type pos, size_type count) const noexcept
{
	for (auto i = size_ - 1; i >= pos; --i)
	{
		value_type ch = *(buffer_ + i);
		for (size_type j = 0; j < count; ++j)
		{
			if (ch != *(s + j))
				return i;
		}
	}
	return npos;
}

// ���±� pos ��ʼ�������ַ��� str �ַ��в���ȵ����һ��λ��
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::size_type
basic_string<CharType, CharTraits>::
find_last_not_of(const basic_string& str, size_type pos) const noexcept
{
	for (auto i = size_ - 1; i >= pos; --i)
	{
		value_type ch = *(buffer_ + i);
		for (size_type j = 0; j < str.size_; ++j)
		{
			if (ch != str[j])
				return i;
		}
	}
	return npos;
}

// ���ش��±� pos ��ʼ�ַ�Ϊ ch ��Ԫ�س��ֵĴ���
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::size_type
basic_string<CharType, CharTraits>::
count(value_type ch, size_type pos) const noexcept
{
	size_type n = 0;
	for (auto i = pos; i < size_; ++i)
	{
		if (*(buffer_ + i) == ch)
			++n;
	}
	return n;
}


/*****************************************************************************************/
// helper function

// ���Գ�ʼ��һ�� buffer��������ʧ������ԣ������׳��쳣
template <class CharType, class CharTraits>
void basic_string<CharType, CharTraits>::
try_init() noexcept
{
	try
	{
		buffer_ = data_allocator::allocate(static_cast<size_type>(STRING_INIT_SIZE));
		size_ = 0;
		cap_ = 0;
	}
	catch (...)
	{
		buffer_ = nullptr;
		size_ = 0;
		cap_ = 0;
		// no throw
	}
}

// fill_init ����
template <class CharType, class CharTraits>
void basic_string<CharType, CharTraits>::
fill_init(size_type n, value_type ch)
{
	const auto init_size = mystl::max(static_cast<size_type>(STRING_INIT_SIZE), n + 1);
	buffer_ = data_allocator::allocate(init_size);
	char_traits::fill(buffer_, ch, n);
	size_ = n;
	cap_ = init_size;
}

// copy_init ����
template <class CharType, class CharTraits>
template <class Iter>
void basic_string<CharType, CharTraits>::
copy_init(Iter first, Iter last, mystl::input_iterator_tag)
{
	size_type n = mystl::distance(first, last);
	const auto init_size = mystl::max(static_cast<size_type>(STRING_INIT_SIZE), n + 1);
	try
	{
		buffer_ = data_allocator::allocate(init_size);
		size_ = n;
		cap_ = init_size;
	}
	catch (...)
	{
		buffer_ = nullptr;
		size_ = 0;
		cap_ = 0;
		throw;
	}
	for (; n > 0; --n, ++first)
		append(*first);
}

template <class CharType, class CharTraits>
template <class Iter>
void basic_string<CharType, CharTraits>::
copy_init(Iter first, Iter last, mystl::forward_iterator_tag)
{
	const size_type n = mystl::distance(first, last);
	const auto init_size = mystl::max(static_cast<size_type>(STRING_INIT_SIZE), n + 1);
	try
	{
		buffer_ = data_allocator::allocate(init_size);
		size_ = n;
		cap_ = init_size;
		mystl::uninitialized_copy(first, last, buffer_);
	}
	catch (...)
	{
		buffer_ = nullptr;
		size_ = 0;
		cap_ = 0;
		throw;
	}
}

// init_from ����
template <class CharType, class CharTraits>
void basic_string<CharType, CharTraits>::
init_from(const_pointer src, size_type pos, size_type count)
{
	const auto init_size = mystl::max(static_cast<size_type>(STRING_INIT_SIZE), count + 1);
	buffer_ = data_allocator::allocate(init_size);
	char_traits::copy(buffer_, src + pos, count);
	size_ = count;
	cap_ = init_size;
}

// destroy_buffer ����
template <class CharType, class CharTraits>
void basic_string<CharType, CharTraits>::
destroy_buffer()
{
	if (buffer_ != nullptr)
	{
		data_allocator::deallocate(buffer_, cap_);
		buffer_ = nullptr;
		size_ = 0;
		cap_ = 0;
	}
}

// to_raw_pointer ����
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::const_pointer
basic_string<CharType, CharTraits>::
to_raw_pointer() const
{
	*(buffer_ + size_) = value_type();
	return buffer_;
}

// reinsert ����
template <class CharType, class CharTraits>
void basic_string<CharType, CharTraits>::
reinsert(size_type size)
{
	auto new_buffer = data_allocator::allocate(size);
	try
	{
		char_traits::move(new_buffer, buffer_, size);
	}
	catch (...)
	{
		data_allocator::deallocate(new_buffer);
	}
	buffer_ = new_buffer;
	size_ = size;
	cap_ = size;
}

// append_range��ĩβ׷��һ�� [first, last) �ڵ��ַ�
template <class CharType, class CharTraits>
template <class Iter>
basic_string<CharType, CharTraits>&
basic_string<CharType, CharTraits>::
append_range(Iter first, Iter last)
{
	const size_type n = mystl::distance(first, last);
	THROW_LENGTH_ERROR_IF(size_ > max_size() - n,
		"basic_string<Char, Tratis>'s size too big");
	if (cap_ - size_ < n)
	{
		reallocate(n);
	}
	mystl::uninitialized_copy_n(first, n, buffer_ + size_);
	size_ += n;
	return *this;
}

//�Ƚ��ַ���
template <class CharType, class CharTraits>
int basic_string<CharType, CharTraits>::
compare_cstr(const_pointer s1, size_type n1, const_pointer s2, size_type n2) const
{
	auto rlen = mystl::min(n1, n2);
	auto res = char_traits::compare(s1, s2, rlen);
	if (res != 0) return res;
	if (n1 < n2) return -1;
	if (n1 > n2) return 1;
	return 0;
}

// �� first ��ʼ�� count1 ���ַ��滻�� str ��ʼ�� count2 ���ַ�
template <class CharType, class CharTraits>
basic_string<CharType, CharTraits>&
basic_string<CharType, CharTraits>::
replace_cstr(const_iterator first, size_type count1, const_pointer str, size_type count2)
{
	if (static_cast<size_type>(cend() - first) < count1)
	{
		count1 = cend() - first;
	}
	if (count1 < count2)
	{
		const size_type add = count2 - count1;
		THROW_LENGTH_ERROR_IF(size_ > max_size() - add,
			"basic_string<Char, Traits>'s size too big");
		if (size_ > cap_ - add)
		{
			reallocate(add);
		}
		pointer r = const_cast<pointer>(first);
		char_traits::move(r + count2, first + count1, end() - (first + count1));
		char_traits::copy(r, str, count2);
		size_ += add;
	}
	else
	{
		pointer r = const_cast<pointer>(first);
		char_traits::move(r + count2, first + count1, end() - (first + count1));
		char_traits::copy(r, str, count2);
		size_ -= (count1 - count2);
	}
	return *this;
}

// �� first ��ʼ�� count1 ���ַ��滻�� count2 �� ch �ַ�
template <class CharType, class CharTraits>
basic_string<CharType, CharTraits>&
basic_string<CharType, CharTraits>::
replace_fill(const_iterator first, size_type count1, size_type count2, value_type ch)
{
	if (static_cast<size_type>(cend() - first) < count1)
	{
		count1 = cend() - first;
	}
	if (count1 < count2)
	{
		const size_type add = count2 - count1;
		THROW_LENGTH_ERROR_IF(size_ > max_size() - add,
			"basic_string<Char, Traits>'s size too big");
		if (size_ > cap_ - add)
		{
			reallocate(add);
		}
		pointer r = const_cast<pointer>(first);
		char_traits::move(r + count2, first + count1, end() - (first + count1));
		char_traits::fill(r, ch, count2);
		size_ += add;
	}
	else
	{
		pointer r = const_cast<pointer>(first);
		char_traits::move(r + count2, first + count1, end() - (first + count1));
		char_traits::fill(r, ch, count2);
		size_ -= (count1 - count2);
	}
	return *this;
}

// �� [first, last) ���ַ��滻�� [first2, last2)
template <class CharType, class CharTraits>
template <class Iter>
basic_string<CharType, CharTraits>&
basic_string<CharType, CharTraits>::
replace_copy(const_iterator first, const_iterator last, Iter first2, Iter last2)
{
	size_type len1 = last - first;
	size_type len2 = last2 - first2;
	if (len1 < len2)
	{
		const size_type add = len2 - len1;
		THROW_LENGTH_ERROR_IF(size_ > max_size() - add,
			"basic_string<Char, Traits>'s size too big");
		if (size_ > cap_ - add)
		{
			reallocate(add);
		}
		pointer r = const_cast<pointer>(first);
		char_traits::move(r + len2, first + len1, end() - (first + len1));
		char_traits::copy(r, first2, len2);
		size_ += add;
	}
	else
	{
		pointer r = const_cast<pointer>(first);
		char_traits::move(r + len2, first + len1, end() - (first + len1));
		char_traits::copy(r, first2, len2);
		size_ -= (len1 - len2);
	}
	return *this;
}

// reallocate ����
template <class CharType, class CharTraits>
void basic_string<CharType, CharTraits>::
reallocate(size_type need)
{
	const auto new_cap = mystl::max(cap_ + need, cap_ + (cap_ >> 1));
	auto new_buffer = data_allocator::allocate(new_cap);
	char_traits::move(new_buffer, buffer_, size_);
	data_allocator::deallocate(buffer_);
	buffer_ = new_buffer;
	cap_ = new_cap;
}

// reallocate_and_fill ����
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::iterator
basic_string<CharType, CharTraits>::
reallocate_and_fill(iterator pos, size_type n, value_type ch)
{
	const auto r = pos - buffer_;
	const auto old_cap = cap_;
	const auto new_cap = mystl::max(old_cap + n, old_cap + (old_cap >> 1));
	auto new_buffer = data_allocator::allocate(new_cap);
	auto e1 = char_traits::move(new_buffer, buffer_, r) + r;
	auto e2 = char_traits::fill(e1, ch, n) + n;
	char_traits::move(e2, buffer_ + r, size_ - r);
	data_allocator::deallocate(buffer_, old_cap);
	buffer_ = new_buffer;
	size_ += n;
	cap_ = new_cap;
	return buffer_ + r;
}

// reallocate_and_copy ����
template <class CharType, class CharTraits>
typename basic_string<CharType, CharTraits>::iterator
basic_string<CharType, CharTraits>::
reallocate_and_copy(iterator pos, const_iterator first, const_iterator last)
{
	const auto r = pos - buffer_;
	const auto old_cap = cap_;
	const size_type n = mystl::distance(first, last);
	const auto new_cap = mystl::max(old_cap + n, old_cap + (old_cap >> 1));
	auto new_buffer = data_allocator::allocate(new_cap);
	auto e1 = char_traits::move(new_buffer, buffer_, r) + r;
	auto e2 = mystl::uninitialized_copy_n(first, n, e1) + n;
	char_traits::move(e2, buffer_ + r, size_ - r);
	data_allocator::deallocate(buffer_, old_cap);
	buffer_ = new_buffer;
	size_ += n;
	cap_ = new_cap;
	return buffer_ + r;
}


/*****************************************************************************************/
// ����ȫ�ֲ�����

// ���� operator+
template <class CharType, class CharTraits>
basic_string<CharType, CharTraits>
operator+(const basic_string<CharType, CharTraits>& lhs,
	const basic_string<CharType, CharTraits>& rhs)
{
	basic_string<CharType, CharTraits> tmp(lhs);
	tmp.append(rhs);
	return tmp;
}

template <class CharType, class CharTraits>
basic_string<CharType, CharTraits>
operator+(const CharType* lhs, const basic_string<CharType, CharTraits>& rhs)
{
	basic_string<CharType, CharTraits> tmp(lhs);
	tmp.append(rhs);
	return tmp;
}

template <class CharType, class CharTraits>
basic_string<CharType, CharTraits>
operator+(CharType ch, const basic_string<CharType, CharTraits>& rhs)
{
	basic_string<CharType, CharTraits> tmp(1, ch);
	tmp.append(rhs);
	return tmp;
}

template <class CharType, class CharTraits>
basic_string<CharType, CharTraits>
operator+(const basic_string<CharType, CharTraits>& lhs, const CharType* rhs)
{
	basic_string<CharType, CharTraits> tmp(lhs);
	tmp.append(rhs);
	return tmp;
}

template <class CharType, class CharTraits>
basic_string<CharType, CharTraits>
operator+(const basic_string<CharType, CharTraits>& lhs, CharType ch)
{
	basic_string<CharType, CharTraits> tmp(lhs);
	tmp.append(1, ch);
	return tmp;
}

template <class CharType, class CharTraits>
basic_string<CharType, CharTraits>
operator+(basic_string<CharType, CharTraits>&& lhs,
	const basic_string<CharType, CharTraits>& rhs)
{
	basic_string<CharType, CharTraits> tmp(mystl::move(lhs));
	tmp.append(rhs);
	return tmp;
}

template <class CharType, class CharTraits>
basic_string<CharType, CharTraits>
operator+(const basic_string<CharType, CharTraits>& lhs,
	basic_string<CharType, CharTraits>&& rhs)
{
	basic_string<CharType, CharTraits> tmp(mystl::move(rhs));
	tmp.insert(tmp.begin(), lhs.begin(), lhs.end());
	return tmp;
}

template <class CharType, class CharTraits>
basic_string<CharType, CharTraits>
operator+(basic_string<CharType, CharTraits>&& lhs,
	basic_string<CharType, CharTraits>&& rhs)
{
	basic_string<CharType, CharTraits> tmp(mystl::move(lhs));
	tmp.append(rhs);
	return tmp;
}

template <class CharType, class CharTraits>
basic_string<CharType, CharTraits>
operator+(const CharType* lhs, basic_string<CharType, CharTraits>&& rhs)
{
	basic_string<CharType, CharTraits> tmp(mystl::move(rhs));
	tmp.insert(tmp.begin(), lhs, lhs + char_traits<CharType>::length(lhs));
	return tmp;
}

template <class CharType, class CharTraits>
basic_string<CharType, CharTraits>
operator+(CharType ch, basic_string<CharType, CharTraits>&& rhs)
{
	basic_string<CharType, CharTraits> tmp(mystl::move(rhs));
	tmp.insert(tmp.begin(), ch);
	return tmp;
}

template <class CharType, class CharTraits>
basic_string<CharType, CharTraits>
operator+(basic_string<CharType, CharTraits>&& lhs, const CharType* rhs)
{
	basic_string<CharType, CharTraits> tmp(mystl::move(lhs));
	tmp.append(rhs);
	return tmp;
}

template <class CharType, class CharTraits>
basic_string<CharType, CharTraits>
operator+(basic_string<CharType, CharTraits>&& lhs, CharType ch)
{
	basic_string<CharType, CharTraits> tmp(mystl::move(lhs));
	tmp.append(1, ch);
	return tmp;
}

// ���رȽϲ�����
template <class CharType, class CharTraits>
bool operator==(const basic_string<CharType, CharTraits>& lhs,
	const basic_string<CharType, CharTraits>& rhs)
{
	return lhs.size() == rhs.size() && lhs.compare(rhs) == 0;
}

template <class CharType, class CharTraits>
bool operator!=(const basic_string<CharType, CharTraits>& lhs,
	const basic_string<CharType, CharTraits>& rhs)
{
	return lhs.size() != rhs.size() || lhs.compare(rhs) != 0;
}

template <class CharType, class CharTraits>
bool operator<(const basic_string<CharType, CharTraits>& lhs,
	const basic_string<CharType, CharTraits>& rhs)
{
	return lhs.compare(rhs) < 0;
}

template <class CharType, class CharTraits>
bool operator<=(const basic_string<CharType, CharTraits>& lhs,
	const basic_string<CharType, CharTraits>& rhs)
{
	return lhs.compare(rhs) <= 0;
}

template <class CharType, class CharTraits>
bool operator>(const basic_string<CharType, CharTraits>& lhs,
	const basic_string<CharType, CharTraits>& rhs)
{
	return lhs.compare(rhs) > 0;
}

template <class CharType, class CharTraits>
bool operator>=(const basic_string<CharType, CharTraits>& lhs,
	const basic_string<CharType, CharTraits>& rhs)
{
	return lhs.compare(rhs) >= 0;
}

// ���� mystl �� swap
template <class CharType, class CharTraits>
void swap(basic_string<CharType, CharTraits>& lhs,
	basic_string<CharType, CharTraits>& rhs) noexcept
{
	lhs.swap(rhs);
}

// �ػ� mystl::hash
template <class CharType, class CharTraits>
struct hash<basic_string<CharType, CharTraits>>
{
	size_t operator()(const basic_string<CharType, CharTraits>& str)
	{
		return bitwise_hash((const unsigned char*)str.c_str(),
			str.size() * sizeof(CharType));
	}
};


}	//�����ռ������



#endif // !MYSTL_BASIC_STRING_H_
