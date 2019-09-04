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

/* Variables and functions */
 int /*<<< orphan*/  PMRN_PMGC0 ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  mfpmr (int /*<<< orphan*/ ) ; 
 scalar_t__ oprofile_running ; 
 int /*<<< orphan*/  pmc_stop_ctrs () ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static void fsl_emb_stop(void)
{
	/* freeze counters */
	pmc_stop_ctrs();

	oprofile_running = 0;

	pr_debug("stop on cpu %d, pmgc0 %x\n", smp_processor_id(),
			mfpmr(PMRN_PMGC0));

	mb();
}