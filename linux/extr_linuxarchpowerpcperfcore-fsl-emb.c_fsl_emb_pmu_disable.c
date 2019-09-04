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
struct pmu {int dummy; } ;
struct cpu_hw_events {int disabled; int pmcs_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMGC0_FAC ; 
 int /*<<< orphan*/  PMRN_PMGC0 ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  isync () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mtpmr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  num_events ; 
 int /*<<< orphan*/  ppc_enable_pmcs () ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fsl_emb_pmu_disable(struct pmu *pmu)
{
	struct cpu_hw_events *cpuhw;
	unsigned long flags;

	local_irq_save(flags);
	cpuhw = this_cpu_ptr(&cpu_hw_events);

	if (!cpuhw->disabled) {
		cpuhw->disabled = 1;

		/*
		 * Check if we ever enabled the PMU on this cpu.
		 */
		if (!cpuhw->pmcs_enabled) {
			ppc_enable_pmcs();
			cpuhw->pmcs_enabled = 1;
		}

		if (atomic_read(&num_events)) {
			/*
			 * Set the 'freeze all counters' bit, and disable
			 * interrupts.  The barrier is to make sure the
			 * mtpmr has been executed and the PMU has frozen
			 * the events before we return.
			 */

			mtpmr(PMRN_PMGC0, PMGC0_FAC);
			isync();
		}
	}
	local_irq_restore(flags);
}