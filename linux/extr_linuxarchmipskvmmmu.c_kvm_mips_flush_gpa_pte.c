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
 int PTRS_PER_PTE ; 
 int /*<<< orphan*/  __pte (int /*<<< orphan*/ ) ; 
 int __pte_offset (unsigned long) ; 
 int /*<<< orphan*/  pte_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool kvm_mips_flush_gpa_pte(pte_t *pte, unsigned long start_gpa,
				   unsigned long end_gpa)
{
	int i_min = __pte_offset(start_gpa);
	int i_max = __pte_offset(end_gpa);
	bool safe_to_remove = (i_min == 0 && i_max == PTRS_PER_PTE - 1);
	int i;

	for (i = i_min; i <= i_max; ++i) {
		if (!pte_present(pte[i]))
			continue;

		set_pte(pte + i, __pte(0));
	}
	return safe_to_remove;
}