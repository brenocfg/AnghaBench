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
struct intel_sdvo {int /*<<< orphan*/  ddc; } ;
struct TYPE_3__ {int /*<<< orphan*/ * sdvo_lvds_vbt_mode; } ;
struct drm_i915_private {TYPE_1__ vbt; } ;
struct drm_display_mode {int type; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct drm_connector {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DRM_MODE_TYPE_DRIVER ; 
 int DRM_MODE_TYPE_PREFERRED ; 
 struct drm_display_mode* drm_mode_duplicate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 struct intel_sdvo* intel_attached_sdvo (struct drm_connector*) ; 
 int /*<<< orphan*/  intel_ddc_get_modes (struct drm_connector*,int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_sdvo_get_lvds_modes(struct drm_connector *connector)
{
	struct intel_sdvo *intel_sdvo = intel_attached_sdvo(connector);
	struct drm_i915_private *dev_priv = to_i915(connector->dev);
	struct drm_display_mode *newmode;

	DRM_DEBUG_KMS("[CONNECTOR:%d:%s]\n",
		      connector->base.id, connector->name);

	/*
	 * Fetch modes from VBT. For SDVO prefer the VBT mode since some
	 * SDVO->LVDS transcoders can't cope with the EDID mode.
	 */
	if (dev_priv->vbt.sdvo_lvds_vbt_mode != NULL) {
		newmode = drm_mode_duplicate(connector->dev,
					     dev_priv->vbt.sdvo_lvds_vbt_mode);
		if (newmode != NULL) {
			/* Guarantee the mode is preferred */
			newmode->type = (DRM_MODE_TYPE_PREFERRED |
					 DRM_MODE_TYPE_DRIVER);
			drm_mode_probed_add(connector, newmode);
		}
	}

	/*
	 * Attempt to get the mode list from DDC.
	 * Assume that the preferred modes are
	 * arranged in priority order.
	 */
	intel_ddc_get_modes(connector, &intel_sdvo->ddc);
}