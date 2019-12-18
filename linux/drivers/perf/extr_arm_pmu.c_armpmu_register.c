#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  capabilities; } ;
struct arm_pmu {int /*<<< orphan*/  num_events; int /*<<< orphan*/  name; TYPE_1__ pmu; int /*<<< orphan*/  set_event_filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_PMU_CAP_NO_EXCLUDE ; 
 struct arm_pmu* __oprofile_cpu_pmu ; 
 int /*<<< orphan*/  cpu_pmu_destroy (struct arm_pmu*) ; 
 int cpu_pmu_init (struct arm_pmu*) ; 
 int perf_pmu_register (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int armpmu_register(struct arm_pmu *pmu)
{
	int ret;

	ret = cpu_pmu_init(pmu);
	if (ret)
		return ret;

	if (!pmu->set_event_filter)
		pmu->pmu.capabilities |= PERF_PMU_CAP_NO_EXCLUDE;

	ret = perf_pmu_register(&pmu->pmu, pmu->name, -1);
	if (ret)
		goto out_destroy;

	if (!__oprofile_cpu_pmu)
		__oprofile_cpu_pmu = pmu;

	pr_info("enabled with %s PMU driver, %d counters available\n",
		pmu->name, pmu->num_events);

	return 0;

out_destroy:
	cpu_pmu_destroy(pmu);
	return ret;
}