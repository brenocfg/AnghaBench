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
struct pt_regs {int dummy; } ;
struct op_counter_config {scalar_t__ enabled; } ;

/* Variables and functions */
 int MSR_PMM ; 
 int /*<<< orphan*/  SPRN_SIAR ; 
 int classic_ctr_read (int) ; 
 int /*<<< orphan*/  classic_ctr_write (int,int /*<<< orphan*/ ) ; 
 int is_kernel_addr (unsigned long) ; 
 int mfmsr () ; 
 unsigned long mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtmsr (int) ; 
 int num_pmcs ; 
 int /*<<< orphan*/  oprofile_add_ext_sample (unsigned long,struct pt_regs*,int,int) ; 
 scalar_t__ oprofile_running ; 
 int /*<<< orphan*/  pmc_start_ctrs () ; 
 int /*<<< orphan*/ * reset_value ; 

__attribute__((used)) static void fsl7450_handle_interrupt(struct pt_regs *regs,
				    struct op_counter_config *ctr)
{
	unsigned long pc;
	int is_kernel;
	int val;
	int i;

	/* set the PMM bit (see comment below) */
	mtmsr(mfmsr() | MSR_PMM);

	pc = mfspr(SPRN_SIAR);
	is_kernel = is_kernel_addr(pc);

	for (i = 0; i < num_pmcs; ++i) {
		val = classic_ctr_read(i);
		if (val < 0) {
			if (oprofile_running && ctr[i].enabled) {
				oprofile_add_ext_sample(pc, regs, i, is_kernel);
				classic_ctr_write(i, reset_value[i]);
			} else {
				classic_ctr_write(i, 0);
			}
		}
	}

	/* The freeze bit was set by the interrupt. */
	/* Clear the freeze bit, and reenable the interrupt.
	 * The counters won't actually start until the rfi clears
	 * the PM/M bit */
	pmc_start_ctrs();
}