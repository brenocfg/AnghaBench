#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  enum page_cache_mode { ____Placeholder_page_cache_mode } page_cache_mode ;

/* Variables and functions */
 int /*<<< orphan*/  CPA_ARRAY ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  _PAGE_CACHE_MASK ; 
 int _PAGE_CACHE_MODE_UC_MINUS ; 
 int _PAGE_CACHE_MODE_WC ; 
 scalar_t__ __pa (unsigned long) ; 
 int /*<<< orphan*/  __pgprot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cachemode2pgprot (int) ; 
 int change_page_attr_set (unsigned long*,int,int /*<<< orphan*/ ,int) ; 
 int change_page_attr_set_clr (unsigned long*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_memtype (scalar_t__,scalar_t__) ; 
 int reserve_memtype (scalar_t__,scalar_t__,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _set_memory_array(unsigned long *addr, int addrinarray,
		enum page_cache_mode new_type)
{
	enum page_cache_mode set_type;
	int i, j;
	int ret;

	for (i = 0; i < addrinarray; i++) {
		ret = reserve_memtype(__pa(addr[i]), __pa(addr[i]) + PAGE_SIZE,
					new_type, NULL);
		if (ret)
			goto out_free;
	}

	/* If WC, set to UC- first and then WC */
	set_type = (new_type == _PAGE_CACHE_MODE_WC) ?
				_PAGE_CACHE_MODE_UC_MINUS : new_type;

	ret = change_page_attr_set(addr, addrinarray,
				   cachemode2pgprot(set_type), 1);

	if (!ret && new_type == _PAGE_CACHE_MODE_WC)
		ret = change_page_attr_set_clr(addr, addrinarray,
					       cachemode2pgprot(
						_PAGE_CACHE_MODE_WC),
					       __pgprot(_PAGE_CACHE_MASK),
					       0, CPA_ARRAY, NULL);
	if (ret)
		goto out_free;

	return 0;

out_free:
	for (j = 0; j < i; j++)
		free_memtype(__pa(addr[j]), __pa(addr[j]) + PAGE_SIZE);

	return ret;
}