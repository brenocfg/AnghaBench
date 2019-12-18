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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_init_clock_gating (struct drm_i915_private*) ; 
 int vlv_allow_gt_wake (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  vlv_check_no_gt_access (struct drm_i915_private*) ; 
 int vlv_force_gfx_clock (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  vlv_restore_gunit_s0ix_state (struct drm_i915_private*) ; 

__attribute__((used)) static int vlv_resume_prepare(struct drm_i915_private *dev_priv,
				bool rpm_resume)
{
	int err;
	int ret;

	/*
	 * If any of the steps fail just try to continue, that's the best we
	 * can do at this point. Return the first error code (which will also
	 * leave RPM permanently disabled).
	 */
	ret = vlv_force_gfx_clock(dev_priv, true);

	vlv_restore_gunit_s0ix_state(dev_priv);

	err = vlv_allow_gt_wake(dev_priv, true);
	if (!ret)
		ret = err;

	err = vlv_force_gfx_clock(dev_priv, false);
	if (!ret)
		ret = err;

	vlv_check_no_gt_access(dev_priv);

	if (rpm_resume)
		intel_init_clock_gating(dev_priv);

	return ret;
}