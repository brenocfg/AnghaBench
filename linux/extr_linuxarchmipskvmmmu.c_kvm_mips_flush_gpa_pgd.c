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
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int PTRS_PER_PGD ; 
 scalar_t__ kvm_mips_flush_gpa_pud (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pgd_clear (int /*<<< orphan*/ *) ; 
 int pgd_index (unsigned long) ; 
 int /*<<< orphan*/  pgd_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pud_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool kvm_mips_flush_gpa_pgd(pgd_t *pgd, unsigned long start_gpa,
				   unsigned long end_gpa)
{
	pud_t *pud;
	unsigned long end = ~0ul;
	int i_min = pgd_index(start_gpa);
	int i_max = pgd_index(end_gpa);
	bool safe_to_remove = (i_min == 0 && i_max == PTRS_PER_PGD - 1);
	int i;

	for (i = i_min; i <= i_max; ++i, start_gpa = 0) {
		if (!pgd_present(pgd[i]))
			continue;

		pud = pud_offset(pgd + i, 0);
		if (i == i_max)
			end = end_gpa;

		if (kvm_mips_flush_gpa_pud(pud, start_gpa, end)) {
			pgd_clear(pgd + i);
			pud_free(NULL, pud);
		} else {
			safe_to_remove = false;
		}
	}
	return safe_to_remove;
}