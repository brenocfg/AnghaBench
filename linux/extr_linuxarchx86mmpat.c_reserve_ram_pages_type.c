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
typedef  int u64 ;
struct page {int dummy; } ;
typedef  enum page_cache_mode { ____Placeholder_page_cache_mode } page_cache_mode ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int _PAGE_CACHE_MODE_UC ; 
 int _PAGE_CACHE_MODE_UC_MINUS ; 
 int _PAGE_CACHE_MODE_WB ; 
 int _PAGE_CACHE_MODE_WP ; 
 int get_page_memtype (struct page*) ; 
 struct page* pfn_to_page (int) ; 
 int /*<<< orphan*/  pr_info (char*,int,int,int,int) ; 
 int /*<<< orphan*/  set_page_memtype (struct page*,int) ; 

__attribute__((used)) static int reserve_ram_pages_type(u64 start, u64 end,
				  enum page_cache_mode req_type,
				  enum page_cache_mode *new_type)
{
	struct page *page;
	u64 pfn;

	if (req_type == _PAGE_CACHE_MODE_WP) {
		if (new_type)
			*new_type = _PAGE_CACHE_MODE_UC_MINUS;
		return -EINVAL;
	}

	if (req_type == _PAGE_CACHE_MODE_UC) {
		/* We do not support strong UC */
		WARN_ON_ONCE(1);
		req_type = _PAGE_CACHE_MODE_UC_MINUS;
	}

	for (pfn = (start >> PAGE_SHIFT); pfn < (end >> PAGE_SHIFT); ++pfn) {
		enum page_cache_mode type;

		page = pfn_to_page(pfn);
		type = get_page_memtype(page);
		if (type != _PAGE_CACHE_MODE_WB) {
			pr_info("x86/PAT: reserve_ram_pages_type failed [mem %#010Lx-%#010Lx], track 0x%x, req 0x%x\n",
				start, end - 1, type, req_type);
			if (new_type)
				*new_type = type;

			return -EBUSY;
		}
	}

	if (new_type)
		*new_type = req_type;

	for (pfn = (start >> PAGE_SHIFT); pfn < (end >> PAGE_SHIFT); ++pfn) {
		page = pfn_to_page(pfn);
		set_page_memtype(page, req_type);
	}
	return 0;
}