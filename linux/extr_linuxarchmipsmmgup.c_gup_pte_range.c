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
 int /*<<< orphan*/  SetPageReferenced (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  gup_get_pte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfn_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_map (int /*<<< orphan*/ *,unsigned long) ; 
 struct page* pte_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_present (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_special (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_write (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gup_pte_range(pmd_t pmd, unsigned long addr, unsigned long end,
			int write, struct page **pages, int *nr)
{
	pte_t *ptep = pte_offset_map(&pmd, addr);
	do {
		pte_t pte = gup_get_pte(ptep);
		struct page *page;

		if (!pte_present(pte) ||
		    pte_special(pte) || (write && !pte_write(pte))) {
			pte_unmap(ptep);
			return 0;
		}
		VM_BUG_ON(!pfn_valid(pte_pfn(pte)));
		page = pte_page(pte);
		get_page(page);
		SetPageReferenced(page);
		pages[*nr] = page;
		(*nr)++;

	} while (ptep++, addr += PAGE_SIZE, addr != end);

	pte_unmap(ptep - 1);
	return 1;
}