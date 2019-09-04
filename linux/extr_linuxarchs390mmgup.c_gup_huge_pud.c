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
typedef  int /*<<< orphan*/  pud_t ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 unsigned long PUD_MASK ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 unsigned long _REGION_ENTRY_INVALID ; 
 unsigned long _REGION_ENTRY_PROTECT ; 
 struct page* compound_head (struct page*) ; 
 int /*<<< orphan*/  page_cache_add_speculative (struct page*,int) ; 
 int /*<<< orphan*/  pfn_valid (int /*<<< orphan*/ ) ; 
 struct page* pud_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pud_pfn (int /*<<< orphan*/ ) ; 
 unsigned long pud_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int gup_huge_pud(pud_t *pudp, pud_t pud, unsigned long addr,
		unsigned long end, int write, struct page **pages, int *nr)
{
	struct page *head, *page;
	unsigned long mask;
	int refs;

	mask = (write ? _REGION_ENTRY_PROTECT : 0) | _REGION_ENTRY_INVALID;
	if ((pud_val(pud) & mask) != 0)
		return 0;
	VM_BUG_ON(!pfn_valid(pud_pfn(pud)));

	refs = 0;
	head = pud_page(pud);
	page = head + ((addr & ~PUD_MASK) >> PAGE_SHIFT);
	do {
		VM_BUG_ON_PAGE(compound_head(page) != head, page);
		pages[*nr] = page;
		(*nr)++;
		page++;
		refs++;
	} while (addr += PAGE_SIZE, addr != end);

	if (!page_cache_add_speculative(head, refs)) {
		*nr -= refs;
		return 0;
	}

	if (unlikely(pud_val(pud) != pud_val(*pudp))) {
		*nr -= refs;
		while (refs--)
			put_page(head);
		return 0;
	}

	return 1;
}