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
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct intel_connector {TYPE_2__* encoder; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum i9xx_plane_id { ____Placeholder_i9xx_plane_id } i9xx_plane_id ;
struct TYPE_4__ {scalar_t__ crtc_mask; } ;

/* Variables and functions */
 scalar_t__ BIT (int /*<<< orphan*/ ) ; 
 int DISPPLANE_ROTATE_180 ; 
 int DRM_MODE_PANEL_ORIENTATION_BOTTOM_UP ; 
 int DRM_MODE_PANEL_ORIENTATION_NORMAL ; 
 int /*<<< orphan*/  DSPCNTR (int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PIPE_B ; 
 int PLANE_A ; 
 int PLANE_B ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_dsi_get_panel_orientation(struct intel_connector *connector)
{
	struct drm_i915_private *dev_priv = to_i915(connector->base.dev);
	int orientation = DRM_MODE_PANEL_ORIENTATION_NORMAL;
	enum i9xx_plane_id i9xx_plane;
	u32 val;

	if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) {
		if (connector->encoder->crtc_mask == BIT(PIPE_B))
			i9xx_plane = PLANE_B;
		else
			i9xx_plane = PLANE_A;

		val = I915_READ(DSPCNTR(i9xx_plane));
		if (val & DISPPLANE_ROTATE_180)
			orientation = DRM_MODE_PANEL_ORIENTATION_BOTTOM_UP;
	}

	return orientation;
}