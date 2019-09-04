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
struct pmu_hw_events {int /*<<< orphan*/  pmu_lock; } ;
struct arm_pmu {int /*<<< orphan*/  hw_events; } ;

/* Variables and functions */
 int ARMV8_PMU_PMCR_E ; 
 int armv8pmu_pmcr_read () ; 
 int /*<<< orphan*/  armv8pmu_pmcr_write (int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pmu_hw_events* this_cpu_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void armv8pmu_start(struct arm_pmu *cpu_pmu)
{
	unsigned long flags;
	struct pmu_hw_events *events = this_cpu_ptr(cpu_pmu->hw_events);

	raw_spin_lock_irqsave(&events->pmu_lock, flags);
	/* Enable all counters */
	armv8pmu_pmcr_write(armv8pmu_pmcr_read() | ARMV8_PMU_PMCR_E);
	raw_spin_unlock_irqrestore(&events->pmu_lock, flags);
}