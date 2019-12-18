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
typedef  int /*<<< orphan*/  u32 ;
struct drm_i915_private {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  disable_power_well; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_STATE_EN_DC9 ; 
 int /*<<< orphan*/  DC_STATE_EN_UPTO_DC5 ; 
 int /*<<< orphan*/  DC_STATE_EN_UPTO_DC6 ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int INTEL_GEN (struct drm_i915_private const*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private const*,int) ; 
 scalar_t__ IS_GEN9_BC (struct drm_i915_private const*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private const*) ; 
 TYPE_1__ i915_modparams ; 

__attribute__((used)) static u32 get_allowed_dc_mask(const struct drm_i915_private *dev_priv,
			       int enable_dc)
{
	u32 mask;
	int requested_dc;
	int max_dc;

	if (INTEL_GEN(dev_priv) >= 11) {
		max_dc = 2;
		/*
		 * DC9 has a separate HW flow from the rest of the DC states,
		 * not depending on the DMC firmware. It's needed by system
		 * suspend/resume, so allow it unconditionally.
		 */
		mask = DC_STATE_EN_DC9;
	} else if (IS_GEN(dev_priv, 10) || IS_GEN9_BC(dev_priv)) {
		max_dc = 2;
		mask = 0;
	} else if (IS_GEN9_LP(dev_priv)) {
		max_dc = 1;
		mask = DC_STATE_EN_DC9;
	} else {
		max_dc = 0;
		mask = 0;
	}

	if (!i915_modparams.disable_power_well)
		max_dc = 0;

	if (enable_dc >= 0 && enable_dc <= max_dc) {
		requested_dc = enable_dc;
	} else if (enable_dc == -1) {
		requested_dc = max_dc;
	} else if (enable_dc > max_dc && enable_dc <= 2) {
		DRM_DEBUG_KMS("Adjusting requested max DC state (%d->%d)\n",
			      enable_dc, max_dc);
		requested_dc = max_dc;
	} else {
		DRM_ERROR("Unexpected value for enable_dc (%d)\n", enable_dc);
		requested_dc = max_dc;
	}

	if (requested_dc > 1)
		mask |= DC_STATE_EN_UPTO_DC6;
	if (requested_dc > 0)
		mask |= DC_STATE_EN_UPTO_DC5;

	DRM_DEBUG_KMS("Allowed DC state mask %02x\n", mask);

	return mask;
}