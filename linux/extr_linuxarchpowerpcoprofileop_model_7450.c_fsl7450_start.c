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
struct op_counter_config {scalar_t__ enabled; } ;

/* Variables and functions */
 int MSR_PMM ; 
 int /*<<< orphan*/  classic_ctr_write (int,int /*<<< orphan*/ ) ; 
 int mfmsr () ; 
 int /*<<< orphan*/  mtmsr (int) ; 
 int num_pmcs ; 
 int oprofile_running ; 
 int /*<<< orphan*/  pmc_start_ctrs () ; 
 int /*<<< orphan*/ * reset_value ; 

__attribute__((used)) static int fsl7450_start(struct op_counter_config *ctr)
{
	int i;

	mtmsr(mfmsr() | MSR_PMM);

	for (i = 0; i < num_pmcs; ++i) {
		if (ctr[i].enabled)
			classic_ctr_write(i, reset_value[i]);
		else
			classic_ctr_write(i, 0);
	}

	/* Clear the freeze bit, and enable the interrupt.
	 * The counters won't actually start until the rfi clears
	 * the PMM bit */
	pmc_start_ctrs();

	oprofile_running = 1;

	return 0;
}