#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_10__ {TYPE_3__* fixed_mode; } ;
struct TYPE_8__ {int /*<<< orphan*/  panel_orientation; } ;
struct TYPE_11__ {TYPE_2__ display_info; TYPE_1__* state; int /*<<< orphan*/  dev; } ;
struct intel_connector {TYPE_4__ panel; TYPE_5__ base; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  vdisplay; int /*<<< orphan*/  hdisplay; } ;
struct TYPE_7__ {int /*<<< orphan*/  scaling_mode; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_MODE_SCALE_ASPECT ; 
 int /*<<< orphan*/  DRM_MODE_SCALE_CENTER ; 
 int /*<<< orphan*/  DRM_MODE_SCALE_FULLSCREEN ; 
 int /*<<< orphan*/  HAS_GMCH (struct drm_i915_private*) ; 
 int /*<<< orphan*/  drm_connector_attach_scaling_mode_property (TYPE_5__*,int) ; 
 int /*<<< orphan*/  drm_connector_init_panel_orientation_property (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlv_dsi_get_panel_orientation (struct intel_connector*) ; 

__attribute__((used)) static void vlv_dsi_add_properties(struct intel_connector *connector)
{
	struct drm_i915_private *dev_priv = to_i915(connector->base.dev);

	if (connector->panel.fixed_mode) {
		u32 allowed_scalers;

		allowed_scalers = BIT(DRM_MODE_SCALE_ASPECT) | BIT(DRM_MODE_SCALE_FULLSCREEN);
		if (!HAS_GMCH(dev_priv))
			allowed_scalers |= BIT(DRM_MODE_SCALE_CENTER);

		drm_connector_attach_scaling_mode_property(&connector->base,
								allowed_scalers);

		connector->base.state->scaling_mode = DRM_MODE_SCALE_ASPECT;

		connector->base.display_info.panel_orientation =
			vlv_dsi_get_panel_orientation(connector);
		drm_connector_init_panel_orientation_property(
				&connector->base,
				connector->panel.fixed_mode->hdisplay,
				connector->panel.fixed_mode->vdisplay);
	}
}