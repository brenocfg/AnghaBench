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

/* Variables and functions */
 scalar_t__ CPUHP_INVALID ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cpuhp_remove_multi_state (scalar_t__) ; 
 scalar_t__ cpuhp_slot ; 
 int cpuhp_state_remove_instance (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i915_pmu_unregister_cpuhp_state(struct i915_pmu *pmu)
{
	WARN_ON(cpuhp_slot == CPUHP_INVALID);
	WARN_ON(cpuhp_state_remove_instance(cpuhp_slot, &pmu->node));
	cpuhp_remove_multi_state(cpuhp_slot);
}