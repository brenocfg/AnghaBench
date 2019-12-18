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
struct drm_i915_private {int /*<<< orphan*/  runtime_pm; int /*<<< orphan*/  uncore; int /*<<< orphan*/  gt; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;

/* Variables and functions */
 int /*<<< orphan*/  FORCEWAKE_ALL ; 
 int /*<<< orphan*/  GEM_TRACE (char*) ; 
 scalar_t__ intel_gt_is_wedged (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_gt_sanitize (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  intel_gt_unset_wedged (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void i915_gem_sanitize(struct drm_i915_private *i915)
{
	intel_wakeref_t wakeref;

	GEM_TRACE("\n");

	wakeref = intel_runtime_pm_get(&i915->runtime_pm);
	intel_uncore_forcewake_get(&i915->uncore, FORCEWAKE_ALL);

	/*
	 * As we have just resumed the machine and woken the device up from
	 * deep PCI sleep (presumably D3_cold), assume the HW has been reset
	 * back to defaults, recovering from whatever wedged state we left it
	 * in and so worth trying to use the device once more.
	 */
	if (intel_gt_is_wedged(&i915->gt))
		intel_gt_unset_wedged(&i915->gt);

	/*
	 * If we inherit context state from the BIOS or earlier occupants
	 * of the GPU, the GPU may be in an inconsistent state when we
	 * try to take over. The only way to remove the earlier state
	 * is by resetting. However, resetting on earlier gen is tricky as
	 * it may impact the display and we are uncertain about the stability
	 * of the reset, so this could be applied to even earlier gen.
	 */
	intel_gt_sanitize(&i915->gt, false);

	intel_uncore_forcewake_put(&i915->uncore, FORCEWAKE_ALL);
	intel_runtime_pm_put(&i915->runtime_pm, wakeref);
}