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
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 unsigned long PMD_MASK ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int _PAGE_VALID ; 
 struct page* compound_head (struct page*) ; 
 int /*<<< orphan*/  page_cache_add_speculative (struct page*,int) ; 
 struct page* pmd_page (int /*<<< orphan*/ ) ; 
 int pmd_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int gup_huge_pmd(pmd_t *pmdp, pmd_t pmd, unsigned long addr,
			unsigned long end, int write, struct page **pages,
			int *nr)
{
	struct page *head, *page;
	int refs;

	if (!(pmd_val(pmd) & _PAGE_VALID))
		return 0;

	if (write && !pmd_write(pmd))
		return 0;

	refs = 0;
	page = pmd_page(pmd) + ((addr & ~PMD_MASK) >> PAGE_SHIFT);
	head = compound_head(page);
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

	if (unlikely(pmd_val(pmd) != pmd_val(*pmdp))) {
		*nr -= refs;
		while (refs--)
			put_page(head);
		return 0;
	}

	return 1;
}