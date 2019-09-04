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
 unsigned long PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 unsigned long PMD_MASK ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 struct page* compound_head (struct page*) ; 
 int /*<<< orphan*/  get_head_page_multiple (struct page*,int) ; 
 int /*<<< orphan*/  pfn_valid (int /*<<< orphan*/ ) ; 
 struct page* pte_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_pfn (int /*<<< orphan*/ ) ; 
 int pte_special (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_write (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gup_huge_pmd(pmd_t pmd, unsigned long addr, unsigned long end,
			int write, struct page **pages, int *nr)
{
	pte_t pte = *(pte_t *)&pmd;
	struct page *head, *page;
	int refs;

	if (write && !pte_write(pte))
		return 0;
	/* hugepages are never "special" */
	VM_BUG_ON(pte_special(pte));
	VM_BUG_ON(!pfn_valid(pte_pfn(pte)));

	refs = 0;
	head = pte_page(pte);
	page = head + ((addr & ~PMD_MASK) >> PAGE_SHIFT);
	do {
		VM_BUG_ON(compound_head(page) != head);
		pages[*nr] = page;
		(*nr)++;
		page++;
		refs++;
	} while (addr += PAGE_SIZE, addr != end);

	get_head_page_multiple(head, refs);
	return 1;
}