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
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int _PAGE_KERNEL_TABLE ; 
 int __pa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __pmd (int) ; 
 scalar_t__ get_safe_page (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static pte_t *resume_one_page_table_init(pmd_t *pmd)
{
	if (pmd_none(*pmd)) {
		pte_t *page_table = (pte_t *)get_safe_page(GFP_ATOMIC);
		if (!page_table)
			return NULL;

		set_pmd(pmd, __pmd(__pa(page_table) | _PAGE_KERNEL_TABLE));

		BUG_ON(page_table != pte_offset_kernel(pmd, 0));

		return page_table;
	}

	return pte_offset_kernel(pmd, 0);
}