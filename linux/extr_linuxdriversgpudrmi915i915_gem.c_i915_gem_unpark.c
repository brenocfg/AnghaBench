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
struct TYPE_3__ {int awake; scalar_t__ epoch; int /*<<< orphan*/  retire_work; int /*<<< orphan*/  active_requests; } ;
struct TYPE_4__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_1__ gt; int /*<<< orphan*/  wq; TYPE_2__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GEM_TRACE (char*) ; 
 int /*<<< orphan*/  HZ ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  POWER_DOMAIN_GT_IRQ ; 
 int /*<<< orphan*/  gen6_rps_busy (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_pmu_gt_unparked (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_queue_hangcheck (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_update_gfx_val (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_display_power_get (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_enable_gt_powersave (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_engines_unpark (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_get_noresume (struct drm_i915_private*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_jiffies_up_relative (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void i915_gem_unpark(struct drm_i915_private *i915)
{
	GEM_TRACE("\n");

	lockdep_assert_held(&i915->drm.struct_mutex);
	GEM_BUG_ON(!i915->gt.active_requests);

	if (i915->gt.awake)
		return;

	intel_runtime_pm_get_noresume(i915);

	/*
	 * It seems that the DMC likes to transition between the DC states a lot
	 * when there are no connected displays (no active power domains) during
	 * command submission.
	 *
	 * This activity has negative impact on the performance of the chip with
	 * huge latencies observed in the interrupt handler and elsewhere.
	 *
	 * Work around it by grabbing a GT IRQ power domain whilst there is any
	 * GT activity, preventing any DC state transitions.
	 */
	intel_display_power_get(i915, POWER_DOMAIN_GT_IRQ);

	i915->gt.awake = true;
	if (unlikely(++i915->gt.epoch == 0)) /* keep 0 as invalid */
		i915->gt.epoch = 1;

	intel_enable_gt_powersave(i915);
	i915_update_gfx_val(i915);
	if (INTEL_GEN(i915) >= 6)
		gen6_rps_busy(i915);
	i915_pmu_gt_unparked(i915);

	intel_engines_unpark(i915);

	i915_queue_hangcheck(i915);

	queue_delayed_work(i915->wq,
			   &i915->gt.retire_work,
			   round_jiffies_up_relative(HZ));
}