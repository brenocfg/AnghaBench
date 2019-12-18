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
struct i915_power_well {TYPE_1__* desc; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* disable ) (struct drm_i915_private*,struct i915_power_well*) ;int /*<<< orphan*/  (* enable ) (struct drm_i915_private*,struct i915_power_well*) ;scalar_t__ (* is_enabled ) (struct drm_i915_private*,struct i915_power_well*) ;} ;
struct TYPE_3__ {TYPE_2__* ops; } ;

/* Variables and functions */
 int DPIO_CMNRST ; 
 int /*<<< orphan*/  DPIO_CTL ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLV_DISP_PW_DISP2D ; 
 int /*<<< orphan*/  VLV_DISP_PW_DPIO_CMN_BC ; 
 struct i915_power_well* lookup_power_well (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct drm_i915_private*,struct i915_power_well*) ; 
 scalar_t__ stub2 (struct drm_i915_private*,struct i915_power_well*) ; 
 int /*<<< orphan*/  stub3 (struct drm_i915_private*,struct i915_power_well*) ; 
 int /*<<< orphan*/  stub4 (struct drm_i915_private*,struct i915_power_well*) ; 

__attribute__((used)) static void vlv_cmnlane_wa(struct drm_i915_private *dev_priv)
{
	struct i915_power_well *cmn =
		lookup_power_well(dev_priv, VLV_DISP_PW_DPIO_CMN_BC);
	struct i915_power_well *disp2d =
		lookup_power_well(dev_priv, VLV_DISP_PW_DISP2D);

	/* If the display might be already active skip this */
	if (cmn->desc->ops->is_enabled(dev_priv, cmn) &&
	    disp2d->desc->ops->is_enabled(dev_priv, disp2d) &&
	    I915_READ(DPIO_CTL) & DPIO_CMNRST)
		return;

	DRM_DEBUG_KMS("toggling display PHY side reset\n");

	/* cmnlane needs DPLL registers */
	disp2d->desc->ops->enable(dev_priv, disp2d);

	/*
	 * From VLV2A0_DP_eDP_HDMI_DPIO_driver_vbios_notes_11.docx:
	 * Need to assert and de-assert PHY SB reset by gating the
	 * common lane power, then un-gating it.
	 * Simply ungating isn't enough to reset the PHY enough to get
	 * ports and lanes running.
	 */
	cmn->desc->ops->disable(dev_priv, cmn);
}