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
typedef  int pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  pgd_offset_k (unsigned long) ; 
 int /*<<< orphan*/  pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ ,unsigned long) ; 
 int* pte_offset_map (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pte_present (int) ; 

int va_kernel_present(unsigned long addr)
{
	pmd_t *pmd;
	pte_t *ptep, pte;

	pmd = pmd_offset(pgd_offset_k(addr), addr);
	if (!pmd_none(*pmd)) {
		ptep = pte_offset_map(pmd, addr);
		pte = *ptep;
		if (pte_present(pte))
			return pte;
	}
	return 0;
}