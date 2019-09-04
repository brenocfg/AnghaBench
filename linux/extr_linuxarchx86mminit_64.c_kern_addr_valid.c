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
typedef  int /*<<< orphan*/  p4d_t ;

/* Variables and functions */
 long __VIRTUAL_MASK_SHIFT ; 
 scalar_t__ p4d_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * p4d_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int pfn_valid (int /*<<< orphan*/ ) ; 
 scalar_t__ pgd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset_k (unsigned long) ; 
 scalar_t__ pmd_large (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pmd_pfn (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pte_pfn (int /*<<< orphan*/ ) ; 
 scalar_t__ pud_large (int /*<<< orphan*/ ) ; 
 scalar_t__ pud_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pud_pfn (int /*<<< orphan*/ ) ; 

int kern_addr_valid(unsigned long addr)
{
	unsigned long above = ((long)addr) >> __VIRTUAL_MASK_SHIFT;
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	if (above != 0 && above != -1UL)
		return 0;

	pgd = pgd_offset_k(addr);
	if (pgd_none(*pgd))
		return 0;

	p4d = p4d_offset(pgd, addr);
	if (p4d_none(*p4d))
		return 0;

	pud = pud_offset(p4d, addr);
	if (pud_none(*pud))
		return 0;

	if (pud_large(*pud))
		return pfn_valid(pud_pfn(*pud));

	pmd = pmd_offset(pud, addr);
	if (pmd_none(*pmd))
		return 0;

	if (pmd_large(*pmd))
		return pfn_valid(pmd_pfn(*pmd));

	pte = pte_offset_kernel(pmd, addr);
	if (pte_none(*pte))
		return 0;

	return pfn_valid(pte_pfn(*pte));
}