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
struct TYPE_2__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_1__ drm; int /*<<< orphan*/  gpu_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_ENGINES ; 
 int ENODEV ; 
 int /*<<< orphan*/  FORCEWAKE_ALL ; 
 int /*<<< orphan*/  GEM_TRACE (char*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_contexts_lost (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_unset_wedged (struct drm_i915_private*) ; 
 scalar_t__ i915_terminally_wedged (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_engines_sanitize (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_gpu_reset (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_has_gpu_reset (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void i915_gem_sanitize(struct drm_i915_private *i915)
{
	int err;

	GEM_TRACE("\n");

	mutex_lock(&i915->drm.struct_mutex);

	intel_runtime_pm_get(i915);
	intel_uncore_forcewake_get(i915, FORCEWAKE_ALL);

	/*
	 * As we have just resumed the machine and woken the device up from
	 * deep PCI sleep (presumably D3_cold), assume the HW has been reset
	 * back to defaults, recovering from whatever wedged state we left it
	 * in and so worth trying to use the device once more.
	 */
	if (i915_terminally_wedged(&i915->gpu_error))
		i915_gem_unset_wedged(i915);

	/*
	 * If we inherit context state from the BIOS or earlier occupants
	 * of the GPU, the GPU may be in an inconsistent state when we
	 * try to take over. The only way to remove the earlier state
	 * is by resetting. However, resetting on earlier gen is tricky as
	 * it may impact the display and we are uncertain about the stability
	 * of the reset, so this could be applied to even earlier gen.
	 */
	err = -ENODEV;
	if (INTEL_GEN(i915) >= 5 && intel_has_gpu_reset(i915))
		err = WARN_ON(intel_gpu_reset(i915, ALL_ENGINES));
	if (!err)
		intel_engines_sanitize(i915);

	intel_uncore_forcewake_put(i915, FORCEWAKE_ALL);
	intel_runtime_pm_put(i915);

	i915_gem_contexts_lost(i915);
	mutex_unlock(&i915->drm.struct_mutex);
}