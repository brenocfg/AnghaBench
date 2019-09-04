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
 int PTRS_PER_PMD ; 
 int __pmd_offset (unsigned long) ; 
 scalar_t__ kvm_mips_flush_gva_pte (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pmd_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmd_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pte_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool kvm_mips_flush_gva_pmd(pmd_t *pmd, unsigned long start_gva,
				   unsigned long end_gva)
{
	pte_t *pte;
	unsigned long end = ~0ul;
	int i_min = __pmd_offset(start_gva);
	int i_max = __pmd_offset(end_gva);
	bool safe_to_remove = (i_min == 0 && i_max == PTRS_PER_PMD - 1);
	int i;

	for (i = i_min; i <= i_max; ++i, start_gva = 0) {
		if (!pmd_present(pmd[i]))
			continue;

		pte = pte_offset(pmd + i, 0);
		if (i == i_max)
			end = end_gva;

		if (kvm_mips_flush_gva_pte(pte, start_gva, end)) {
			pmd_clear(pmd + i);
			pte_free_kernel(NULL, pte);
		} else {
			safe_to_remove = false;
		}
	}
	return safe_to_remove;
}