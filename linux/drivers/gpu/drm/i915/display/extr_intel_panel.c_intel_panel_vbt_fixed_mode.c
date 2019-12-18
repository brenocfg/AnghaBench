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
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct drm_display_info {int /*<<< orphan*/  height_mm; int /*<<< orphan*/  width_mm; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; TYPE_2__ base; struct drm_display_info display_info; int /*<<< orphan*/  dev; } ;
struct intel_connector {TYPE_3__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  lfp_lvds_vbt_mode; } ;
struct drm_i915_private {TYPE_1__ vbt; int /*<<< orphan*/  drm; } ;
struct drm_display_mode {int /*<<< orphan*/  height_mm; int /*<<< orphan*/  width_mm; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_MODE_TYPE_PREFERRED ; 
 int /*<<< orphan*/  drm_mode_debug_printmodeline (struct drm_display_mode*) ; 
 struct drm_display_mode* drm_mode_duplicate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

struct drm_display_mode *
intel_panel_vbt_fixed_mode(struct intel_connector *connector)
{
	struct drm_i915_private *dev_priv = to_i915(connector->base.dev);
	struct drm_display_info *info = &connector->base.display_info;
	struct drm_display_mode *fixed_mode;

	if (!dev_priv->vbt.lfp_lvds_vbt_mode)
		return NULL;

	fixed_mode = drm_mode_duplicate(&dev_priv->drm,
					dev_priv->vbt.lfp_lvds_vbt_mode);
	if (!fixed_mode)
		return NULL;

	fixed_mode->type |= DRM_MODE_TYPE_PREFERRED;

	DRM_DEBUG_KMS("[CONNECTOR:%d:%s] using mode from VBT: ",
		      connector->base.base.id, connector->base.name);
	drm_mode_debug_printmodeline(fixed_mode);

	info->width_mm = fixed_mode->width_mm;
	info->height_mm = fixed_mode->height_mm;

	return fixed_mode;
}