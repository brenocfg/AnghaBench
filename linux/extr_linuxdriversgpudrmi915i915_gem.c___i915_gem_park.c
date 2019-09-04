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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int active_requests; int awake; scalar_t__ epoch; int /*<<< orphan*/  active_rings; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_1__ gt; TYPE_2__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GEM_TRACE (char*) ; 
 scalar_t__ I915_EPOCH_INVALID ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  POWER_DOMAIN_GT_IRQ ; 
 int /*<<< orphan*/  gen6_rps_idle (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_pmu_gt_parked (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_timelines_park (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_vma_parked (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_display_power_put (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_engines_park (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 __i915_gem_park(struct drm_i915_private *i915)
{
	GEM_TRACE("\n");

	lockdep_assert_held(&i915->drm.struct_mutex);
	GEM_BUG_ON(i915->gt.active_requests);
	GEM_BUG_ON(!list_empty(&i915->gt.active_rings));

	if (!i915->gt.awake)
		return I915_EPOCH_INVALID;

	GEM_BUG_ON(i915->gt.epoch == I915_EPOCH_INVALID);

	/*
	 * Be paranoid and flush a concurrent interrupt to make sure
	 * we don't reactivate any irq tasklets after parking.
	 *
	 * FIXME: Note that even though we have waited for execlists to be idle,
	 * there may still be an in-flight interrupt even though the CSB
	 * is now empty. synchronize_irq() makes sure that a residual interrupt
	 * is completed before we continue, but it doesn't prevent the HW from
	 * raising a spurious interrupt later. To complete the shield we should
	 * coordinate disabling the CS irq with flushing the interrupts.
	 */
	synchronize_irq(i915->drm.irq);

	intel_engines_park(i915);
	i915_timelines_park(i915);

	i915_pmu_gt_parked(i915);
	i915_vma_parked(i915);

	i915->gt.awake = false;

	if (INTEL_GEN(i915) >= 6)
		gen6_rps_idle(i915);

	intel_display_power_put(i915, POWER_DOMAIN_GT_IRQ);

	intel_runtime_pm_put(i915);

	return i915->gt.epoch;
}