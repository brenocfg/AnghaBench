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

/* Variables and functions */
 int /*<<< orphan*/  set_pte_atomic (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __set_pmd_pte(pte_t *kpte, unsigned long address, pte_t pte)
{
	/* change init_mm */
	set_pte_atomic(kpte, pte);
#ifdef CONFIG_X86_32
	if (!SHARED_KERNEL_PMD) {
		struct page *page;

		list_for_each_entry(page, &pgd_list, lru) {
			pgd_t *pgd;
			p4d_t *p4d;
			pud_t *pud;
			pmd_t *pmd;

			pgd = (pgd_t *)page_address(page) + pgd_index(address);
			p4d = p4d_offset(pgd, address);
			pud = pud_offset(p4d, address);
			pmd = pmd_offset(pud, address);
			set_pte_atomic((pte_t *)pmd, pte);
		}
	}
#endif
}