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
struct TYPE_6__ {int x1; } ;
struct TYPE_5__ {TYPE_3__ dst; TYPE_1__* plane; } ;
struct intel_plane_state {TYPE_2__ base; } ;
struct intel_crtc_state {int pipe_src_w; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,char*,int,int,int) ; 
 int ERANGE ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 int drm_rect_width (TYPE_3__*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skl_plane_check_dst_coordinates(const struct intel_crtc_state *crtc_state,
					   const struct intel_plane_state *plane_state)
{
	struct drm_i915_private *dev_priv =
		to_i915(plane_state->base.plane->dev);
	int crtc_x = plane_state->base.dst.x1;
	int crtc_w = drm_rect_width(&plane_state->base.dst);
	int pipe_src_w = crtc_state->pipe_src_w;

	/*
	 * Display WA #1175: cnl,glk
	 * Planes other than the cursor may cause FIFO underflow and display
	 * corruption if starting less than 4 pixels from the right edge of
	 * the screen.
	 * Besides the above WA fix the similar problem, where planes other
	 * than the cursor ending less than 4 pixels from the left edge of the
	 * screen may cause FIFO underflow and display corruption.
	 */
	if ((IS_GEMINILAKE(dev_priv) || IS_CANNONLAKE(dev_priv)) &&
	    (crtc_x + crtc_w < 4 || crtc_x > pipe_src_w - 4)) {
		DRM_DEBUG_KMS("requested plane X %s position %d invalid (valid range %d-%d)\n",
			      crtc_x + crtc_w < 4 ? "end" : "start",
			      crtc_x + crtc_w < 4 ? crtc_x + crtc_w : crtc_x,
			      4, pipe_src_w - 4);
		return -ERANGE;
	}

	return 0;
}