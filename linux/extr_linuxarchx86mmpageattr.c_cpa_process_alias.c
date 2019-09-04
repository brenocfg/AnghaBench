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
struct page {int dummy; } ;
struct cpa_data {int pfn; int flags; size_t curpage; unsigned long* vaddr; struct page** pages; } ;

/* Variables and functions */
 int CPA_ARRAY ; 
 int CPA_PAGES_ARRAY ; 
 scalar_t__ PAGE_OFFSET ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PageHighMem (struct page*) ; 
 int __change_page_attr_set_clr (struct cpa_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ __va (int) ; 
 int max_pfn_mapped ; 
 scalar_t__ page_address (struct page*) ; 
 int /*<<< orphan*/  pfn_range_is_mapped (int,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  within (unsigned long,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int cpa_process_alias(struct cpa_data *cpa)
{
	struct cpa_data alias_cpa;
	unsigned long laddr = (unsigned long)__va(cpa->pfn << PAGE_SHIFT);
	unsigned long vaddr;
	int ret;

	if (!pfn_range_is_mapped(cpa->pfn, cpa->pfn + 1))
		return 0;

	/*
	 * No need to redo, when the primary call touched the direct
	 * mapping already:
	 */
	if (cpa->flags & CPA_PAGES_ARRAY) {
		struct page *page = cpa->pages[cpa->curpage];
		if (unlikely(PageHighMem(page)))
			return 0;
		vaddr = (unsigned long)page_address(page);
	} else if (cpa->flags & CPA_ARRAY)
		vaddr = cpa->vaddr[cpa->curpage];
	else
		vaddr = *cpa->vaddr;

	if (!(within(vaddr, PAGE_OFFSET,
		    PAGE_OFFSET + (max_pfn_mapped << PAGE_SHIFT)))) {

		alias_cpa = *cpa;
		alias_cpa.vaddr = &laddr;
		alias_cpa.flags &= ~(CPA_PAGES_ARRAY | CPA_ARRAY);

		ret = __change_page_attr_set_clr(&alias_cpa, 0);
		if (ret)
			return ret;
	}

#ifdef CONFIG_X86_64
	/*
	 * If the primary call didn't touch the high mapping already
	 * and the physical address is inside the kernel map, we need
	 * to touch the high mapped kernel as well:
	 */
	if (!within(vaddr, (unsigned long)_text, _brk_end) &&
	    __cpa_pfn_in_highmap(cpa->pfn)) {
		unsigned long temp_cpa_vaddr = (cpa->pfn << PAGE_SHIFT) +
					       __START_KERNEL_map - phys_base;
		alias_cpa = *cpa;
		alias_cpa.vaddr = &temp_cpa_vaddr;
		alias_cpa.flags &= ~(CPA_PAGES_ARRAY | CPA_ARRAY);

		/*
		 * The high mapping range is imprecise, so ignore the
		 * return value.
		 */
		__change_page_attr_set_clr(&alias_cpa, 0);
	}
#endif

	return 0;
}