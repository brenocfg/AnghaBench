#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * event_init; } ;
struct TYPE_3__ {TYPE_2__ base; int /*<<< orphan*/  timer; int /*<<< orphan*/  enable; } ;
struct drm_i915_private {TYPE_1__ pmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_event_attributes (struct drm_i915_private*) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_pmu_unregister_cpuhp_state (struct drm_i915_private*) ; 
 int /*<<< orphan*/  perf_pmu_unregister (TYPE_2__*) ; 

void i915_pmu_unregister(struct drm_i915_private *i915)
{
	if (!i915->pmu.base.event_init)
		return;

	WARN_ON(i915->pmu.enable);

	hrtimer_cancel(&i915->pmu.timer);

	i915_pmu_unregister_cpuhp_state(i915);

	perf_pmu_unregister(&i915->pmu.base);
	i915->pmu.base.event_init = NULL;
	free_event_attributes(i915);
}