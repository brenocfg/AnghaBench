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
struct TYPE_2__ {int /*<<< orphan*/ * event_init; } ;
struct i915_pmu {TYPE_1__ base; int /*<<< orphan*/  timer; int /*<<< orphan*/  enable; } ;
struct drm_i915_private {struct i915_pmu pmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_event_attributes (struct i915_pmu*) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_pmu_unregister_cpuhp_state (struct i915_pmu*) ; 
 int /*<<< orphan*/  perf_pmu_unregister (TYPE_1__*) ; 

void i915_pmu_unregister(struct drm_i915_private *i915)
{
	struct i915_pmu *pmu = &i915->pmu;

	if (!pmu->base.event_init)
		return;

	WARN_ON(pmu->enable);

	hrtimer_cancel(&pmu->timer);

	i915_pmu_unregister_cpuhp_state(pmu);

	perf_pmu_unregister(&pmu->base);
	pmu->base.event_init = NULL;
	free_event_attributes(pmu);
}