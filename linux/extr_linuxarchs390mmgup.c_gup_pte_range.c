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
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 unsigned long _PAGE_INVALID ; 
 unsigned long _PAGE_PROTECT ; 
 unsigned long _PAGE_SPECIAL ; 
 int /*<<< orphan*/  barrier () ; 
 struct page* compound_head (struct page*) ; 
 int /*<<< orphan*/  page_cache_get_speculative (struct page*) ; 
 int /*<<< orphan*/  pfn_valid (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_deref (int /*<<< orphan*/ ) ; 
 int pte_index (unsigned long) ; 
 struct page* pte_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_pfn (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_protnone (int /*<<< orphan*/ ) ; 
 unsigned long pte_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int gup_pte_range(pmd_t *pmdp, pmd_t pmd, unsigned long addr,
		unsigned long end, int write, struct page **pages, int *nr)
{
	struct page *head, *page;
	unsigned long mask;
	pte_t *ptep, pte;

	mask = (write ? _PAGE_PROTECT : 0) | _PAGE_INVALID | _PAGE_SPECIAL;

	ptep = ((pte_t *) pmd_deref(pmd)) + pte_index(addr);
	do {
		pte = *ptep;
		barrier();
		/* Similar to the PMD case, NUMA hinting must take slow path */
		if (pte_protnone(pte))
			return 0;
		if ((pte_val(pte) & mask) != 0)
			return 0;
		VM_BUG_ON(!pfn_valid(pte_pfn(pte)));
		page = pte_page(pte);
		head = compound_head(page);
		if (!page_cache_get_speculative(head))
			return 0;
		if (unlikely(pte_val(pte) != pte_val(*ptep))) {
			put_page(head);
			return 0;
		}
		VM_BUG_ON_PAGE(compound_head(page) != head, page);
		pages[*nr] = page;
		(*nr)++;

	} while (ptep++, addr += PAGE_SIZE, addr != end);

	return 1;
}