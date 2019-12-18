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
struct i915_pmu {int /*<<< orphan*/  node; } ;
typedef  enum cpuhp_state { ____Placeholder_cpuhp_state } cpuhp_state ;

/* Variables and functions */
 int /*<<< orphan*/  CPUHP_AP_ONLINE_DYN ; 
 int /*<<< orphan*/  cpuhp_remove_multi_state (int) ; 
 int cpuhp_setup_state_multi (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cpuhp_slot ; 
 int cpuhp_state_add_instance (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_pmu_cpu_offline ; 
 int /*<<< orphan*/  i915_pmu_cpu_online ; 

__attribute__((used)) static int i915_pmu_register_cpuhp_state(struct i915_pmu *pmu)
{
	enum cpuhp_state slot;
	int ret;

	ret = cpuhp_setup_state_multi(CPUHP_AP_ONLINE_DYN,
				      "perf/x86/intel/i915:online",
				      i915_pmu_cpu_online,
				      i915_pmu_cpu_offline);
	if (ret < 0)
		return ret;

	slot = ret;
	ret = cpuhp_state_add_instance(slot, &pmu->node);
	if (ret) {
		cpuhp_remove_multi_state(slot);
		return ret;
	}

	cpuhp_slot = slot;
	return 0;
}