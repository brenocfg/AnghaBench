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
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENOMEM ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ PGTABLE_RANGE ; 
 int /*<<< orphan*/  PMD_TABLE_SIZE ; 
 int /*<<< orphan*/  PUD_TABLE_SIZE ; 
 scalar_t__ TASK_SIZE_USER64 ; 
 int /*<<< orphan*/  __pgprot (unsigned long) ; 
 void* early_alloc_pgtable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_mm ; 
 int /*<<< orphan*/  pfn_pte (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ pgd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset_k (unsigned long) ; 
 int /*<<< orphan*/  pgd_populate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pmd_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pmd_populate_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmd_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_alloc_kernel (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * pud_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pud_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pud_populate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_pte_at (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ slab_is_available () ; 
 int /*<<< orphan*/  smp_wmb () ; 

int map_kernel_page(unsigned long ea, unsigned long pa, unsigned long flags)
{
	pgd_t *pgdp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep;

	BUILD_BUG_ON(TASK_SIZE_USER64 > PGTABLE_RANGE);
	if (slab_is_available()) {
		pgdp = pgd_offset_k(ea);
		pudp = pud_alloc(&init_mm, pgdp, ea);
		if (!pudp)
			return -ENOMEM;
		pmdp = pmd_alloc(&init_mm, pudp, ea);
		if (!pmdp)
			return -ENOMEM;
		ptep = pte_alloc_kernel(pmdp, ea);
		if (!ptep)
			return -ENOMEM;
		set_pte_at(&init_mm, ea, ptep, pfn_pte(pa >> PAGE_SHIFT,
							  __pgprot(flags)));
	} else {
		pgdp = pgd_offset_k(ea);
#ifndef __PAGETABLE_PUD_FOLDED
		if (pgd_none(*pgdp)) {
			pudp = early_alloc_pgtable(PUD_TABLE_SIZE);
			BUG_ON(pudp == NULL);
			pgd_populate(&init_mm, pgdp, pudp);
		}
#endif /* !__PAGETABLE_PUD_FOLDED */
		pudp = pud_offset(pgdp, ea);
		if (pud_none(*pudp)) {
			pmdp = early_alloc_pgtable(PMD_TABLE_SIZE);
			BUG_ON(pmdp == NULL);
			pud_populate(&init_mm, pudp, pmdp);
		}
		pmdp = pmd_offset(pudp, ea);
		if (!pmd_present(*pmdp)) {
			ptep = early_alloc_pgtable(PAGE_SIZE);
			BUG_ON(ptep == NULL);
			pmd_populate_kernel(&init_mm, pmdp, ptep);
		}
		ptep = pte_offset_kernel(pmdp, ea);
		set_pte_at(&init_mm, ea, ptep, pfn_pte(pa >> PAGE_SHIFT,
							  __pgprot(flags)));
	}

	smp_wmb();
	return 0;
}