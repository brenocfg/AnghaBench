#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct drm_device* dev; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
struct intel_dsi {TYPE_2__ base; struct intel_connector* attached_connector; } ;
struct intel_connector {int /*<<< orphan*/  base; } ;
struct TYPE_6__ {int /*<<< orphan*/  lfp_lvds_vbt_mode; } ;
struct drm_i915_private {TYPE_3__ vbt; } ;
struct drm_display_mode {int /*<<< orphan*/  type; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_TYPE_PREFERRED ; 
 struct drm_display_mode* drm_mode_duplicate (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_probed_add (int /*<<< orphan*/ *,struct drm_display_mode*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

int intel_dsi_vbt_get_modes(struct intel_dsi *intel_dsi)
{
	struct intel_connector *connector = intel_dsi->attached_connector;
	struct drm_device *dev = intel_dsi->base.base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct drm_display_mode *mode;

	mode = drm_mode_duplicate(dev, dev_priv->vbt.lfp_lvds_vbt_mode);
	if (!mode)
		return 0;

	mode->type |= DRM_MODE_TYPE_PREFERRED;

	drm_mode_probed_add(&connector->base, mode);

	return 1;
}