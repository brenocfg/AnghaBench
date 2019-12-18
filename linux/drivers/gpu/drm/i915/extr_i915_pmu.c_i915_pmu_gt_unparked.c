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
struct i915_pmu {int /*<<< orphan*/  lock; TYPE_1__ base; } ;
struct drm_i915_private {struct i915_pmu pmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  __i915_pmu_maybe_start_timer (struct i915_pmu*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void i915_pmu_gt_unparked(struct drm_i915_private *i915)
{
	struct i915_pmu *pmu = &i915->pmu;

	if (!pmu->base.event_init)
		return;

	spin_lock_irq(&pmu->lock);
	/*
	 * Re-enable sampling timer when GPU goes active.
	 */
	__i915_pmu_maybe_start_timer(pmu);
	spin_unlock_irq(&pmu->lock);
}