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
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int I915_READ (int /*<<< orphan*/ ) ; 
 int VLV_GTLC_MEDIA_CTX_EXISTS ; 
 int VLV_GTLC_RENDER_CTX_EXISTS ; 
 int /*<<< orphan*/  VLV_GTLC_WAKE_CTRL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int vlv_allow_gt_wake (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  vlv_check_no_gt_access (struct drm_i915_private*) ; 
 int vlv_force_gfx_clock (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  vlv_save_gunit_s0ix_state (struct drm_i915_private*) ; 
 int /*<<< orphan*/  vlv_wait_for_gt_wells (struct drm_i915_private*,int) ; 

__attribute__((used)) static int vlv_suspend_complete(struct drm_i915_private *dev_priv)
{
	u32 mask;
	int err;

	/*
	 * Bspec defines the following GT well on flags as debug only, so
	 * don't treat them as hard failures.
	 */
	vlv_wait_for_gt_wells(dev_priv, false);

	mask = VLV_GTLC_RENDER_CTX_EXISTS | VLV_GTLC_MEDIA_CTX_EXISTS;
	WARN_ON((I915_READ(VLV_GTLC_WAKE_CTRL) & mask) != mask);

	vlv_check_no_gt_access(dev_priv);

	err = vlv_force_gfx_clock(dev_priv, true);
	if (err)
		goto err1;

	err = vlv_allow_gt_wake(dev_priv, false);
	if (err)
		goto err2;

	vlv_save_gunit_s0ix_state(dev_priv);

	err = vlv_force_gfx_clock(dev_priv, false);
	if (err)
		goto err2;

	return 0;

err2:
	/* For safety always re-enable waking and disable gfx clock forcing */
	vlv_allow_gt_wake(dev_priv, true);
err1:
	vlv_force_gfx_clock(dev_priv, false);

	return err;
}