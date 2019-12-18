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
struct arm_pmu {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUHP_AP_PERF_ARM_STARTING ; 
 int /*<<< orphan*/  cpu_pm_pmu_unregister (struct arm_pmu*) ; 
 int /*<<< orphan*/  cpuhp_state_remove_instance_nocalls (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpu_pmu_destroy(struct arm_pmu *cpu_pmu)
{
	cpu_pm_pmu_unregister(cpu_pmu);
	cpuhp_state_remove_instance_nocalls(CPUHP_AP_PERF_ARM_STARTING,
					    &cpu_pmu->node);
}