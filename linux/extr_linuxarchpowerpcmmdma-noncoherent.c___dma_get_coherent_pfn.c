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
 int /*<<< orphan*/ * pgd_offset_k (unsigned long) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long pte_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 

unsigned long __dma_get_coherent_pfn(unsigned long cpu_addr)
{
	/* This should always be populated, so we don't test every
	 * level. If that fails, we'll have a nice crash which
	 * will be as good as a BUG_ON()
	 */
	pgd_t *pgd = pgd_offset_k(cpu_addr);
	pud_t *pud = pud_offset(pgd, cpu_addr);
	pmd_t *pmd = pmd_offset(pud, cpu_addr);
	pte_t *ptep = pte_offset_kernel(pmd, cpu_addr);

	if (pte_none(*ptep) || !pte_present(*ptep))
		return 0;
	return pte_pfn(*ptep);
}