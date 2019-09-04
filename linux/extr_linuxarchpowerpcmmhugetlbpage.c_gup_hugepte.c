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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 struct page* compound_head (struct page*) ; 
 int /*<<< orphan*/  page_cache_add_speculative (struct page*,int) ; 
 int /*<<< orphan*/  pfn_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_access_permitted (int /*<<< orphan*/ ,int) ; 
 struct page* pte_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_pfn (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 scalar_t__ unlikely (int) ; 

int gup_hugepte(pte_t *ptep, unsigned long sz, unsigned long addr,
		unsigned long end, int write, struct page **pages, int *nr)
{
	unsigned long pte_end;
	struct page *head, *page;
	pte_t pte;
	int refs;

	pte_end = (addr + sz) & ~(sz-1);
	if (pte_end < end)
		end = pte_end;

	pte = READ_ONCE(*ptep);

	if (!pte_access_permitted(pte, write))
		return 0;

	/* hugepages are never "special" */
	VM_BUG_ON(!pfn_valid(pte_pfn(pte)));

	refs = 0;
	head = pte_page(pte);

	page = head + ((addr & (sz-1)) >> PAGE_SHIFT);
	do {
		VM_BUG_ON(compound_head(page) != head);
		pages[*nr] = page;
		(*nr)++;
		page++;
		refs++;
	} while (addr += PAGE_SIZE, addr != end);

	if (!page_cache_add_speculative(head, refs)) {
		*nr -= refs;
		return 0;
	}

	if (unlikely(pte_val(pte) != pte_val(*ptep))) {
		/* Could be optimized better */
		*nr -= refs;
		while (refs--)
			put_page(head);
		return 0;
	}

	return 1;
}