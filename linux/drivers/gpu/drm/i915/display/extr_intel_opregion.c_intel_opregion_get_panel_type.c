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
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  SWSCI_GBDA_PANEL_DETAILS ; 
 int /*<<< orphan*/  dmi_check_system (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_use_opregion_panel_type ; 
 int swsci (struct drm_i915_private*,int /*<<< orphan*/ ,int,int*) ; 

int
intel_opregion_get_panel_type(struct drm_i915_private *dev_priv)
{
	u32 panel_details;
	int ret;

	ret = swsci(dev_priv, SWSCI_GBDA_PANEL_DETAILS, 0x0, &panel_details);
	if (ret) {
		DRM_DEBUG_KMS("Failed to get panel details from OpRegion (%d)\n",
			      ret);
		return ret;
	}

	ret = (panel_details >> 8) & 0xff;
	if (ret > 0x10) {
		DRM_DEBUG_KMS("Invalid OpRegion panel type 0x%x\n", ret);
		return -EINVAL;
	}

	/* fall back to VBT panel type? */
	if (ret == 0x0) {
		DRM_DEBUG_KMS("No panel type in OpRegion\n");
		return -ENODEV;
	}

	/*
	 * So far we know that some machined must use it, others must not use it.
	 * There doesn't seem to be any way to determine which way to go, except
	 * via a quirk list :(
	 */
	if (!dmi_check_system(intel_use_opregion_panel_type)) {
		DRM_DEBUG_KMS("Ignoring OpRegion panel type (%d)\n", ret - 1);
		return -ENODEV;
	}

	return ret - 1;
}