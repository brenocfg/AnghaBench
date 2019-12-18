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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_connector {TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum drm_panel_orientation { ____Placeholder_drm_panel_orientation } drm_panel_orientation ;

/* Variables and functions */
 int DRM_MODE_PANEL_ORIENTATION_UNKNOWN ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int intel_dsi_get_panel_orientation (struct intel_connector*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 int vlv_dsi_get_hw_panel_orientation (struct intel_connector*) ; 

__attribute__((used)) static enum drm_panel_orientation
vlv_dsi_get_panel_orientation(struct intel_connector *connector)
{
	struct drm_i915_private *dev_priv = to_i915(connector->base.dev);
	enum drm_panel_orientation orientation;

	if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) {
		orientation = vlv_dsi_get_hw_panel_orientation(connector);
		if (orientation != DRM_MODE_PANEL_ORIENTATION_UNKNOWN)
			return orientation;
	}

	return intel_dsi_get_panel_orientation(connector);
}