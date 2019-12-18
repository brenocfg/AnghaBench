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
struct TYPE_2__ {int /*<<< orphan*/  event_init; } ;
struct i915_pmu {int /*<<< orphan*/  lock; int /*<<< orphan*/  timer_enabled; TYPE_1__ base; } ;
struct drm_i915_private {struct i915_pmu pmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  pmu_needs_timer (struct i915_pmu*,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void i915_pmu_gt_parked(struct drm_i915_private *i915)
{
	struct i915_pmu *pmu = &i915->pmu;

	if (!pmu->base.event_init)
		return;

	spin_lock_irq(&pmu->lock);
	/*
	 * Signal sampling timer to stop if only engine events are enabled and
	 * GPU went idle.
	 */
	pmu->timer_enabled = pmu_needs_timer(pmu, false);
	spin_unlock_irq(&pmu->lock);
}