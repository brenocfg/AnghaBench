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
struct TYPE_4__ {int crtc_w; int crtc_h; int rotation; TYPE_1__* plane; } ;
struct intel_plane_state {TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DRM_MODE_ROTATE_0 ; 
 scalar_t__ HAS_CUR_FBC (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_cursor_size_ok (struct intel_plane_state const*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool i9xx_cursor_size_ok(const struct intel_plane_state *plane_state)
{
	struct drm_i915_private *dev_priv =
		to_i915(plane_state->base.plane->dev);
	int width = plane_state->base.crtc_w;
	int height = plane_state->base.crtc_h;

	if (!intel_cursor_size_ok(plane_state))
		return false;

	/* Cursor width is limited to a few power-of-two sizes */
	switch (width) {
	case 256:
	case 128:
	case 64:
		break;
	default:
		return false;
	}

	/*
	 * IVB+ have CUR_FBC_CTL which allows an arbitrary cursor
	 * height from 8 lines up to the cursor width, when the
	 * cursor is not rotated. Everything else requires square
	 * cursors.
	 */
	if (HAS_CUR_FBC(dev_priv) &&
	    plane_state->base.rotation & DRM_MODE_ROTATE_0) {
		if (height < 8 || height > width)
			return false;
	} else {
		if (height != width)
			return false;
	}

	return true;
}