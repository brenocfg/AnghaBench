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
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  pud_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ pud_page_vaddr (int /*<<< orphan*/ ) ; 
 scalar_t__ try_to_free_pmd_page (int /*<<< orphan*/ *) ; 
 scalar_t__ unmap_pte_range (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 

__attribute__((used)) static void __unmap_pmd_range(pud_t *pud, pmd_t *pmd,
			      unsigned long start, unsigned long end)
{
	if (unmap_pte_range(pmd, start, end))
		if (try_to_free_pmd_page((pmd_t *)pud_page_vaddr(*pud)))
			pud_clear(pud);
}