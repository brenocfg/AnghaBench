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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {scalar_t__ color_encoding; scalar_t__ color_range; struct drm_framebuffer* fb; TYPE_2__* plane; } ;
struct intel_plane_state {TYPE_3__ base; } ;
struct intel_crtc_state {int dummy; } ;
struct drm_i915_private {int dummy; } ;
struct drm_framebuffer {TYPE_1__* format; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {scalar_t__ is_yuv; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 scalar_t__ DRM_COLOR_YCBCR_BT709 ; 
 scalar_t__ DRM_COLOR_YCBCR_FULL_RANGE ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PLANE_COLOR_CSC_MODE_YUV601_TO_RGB709 ; 
 int /*<<< orphan*/  PLANE_COLOR_CSC_MODE_YUV709_TO_RGB709 ; 
 int /*<<< orphan*/  PLANE_COLOR_PIPE_CSC_ENABLE ; 
 int /*<<< orphan*/  PLANE_COLOR_PIPE_GAMMA_ENABLE ; 
 int /*<<< orphan*/  PLANE_COLOR_PLANE_GAMMA_DISABLE ; 
 int /*<<< orphan*/  PLANE_COLOR_YUV_RANGE_CORRECTION_DISABLE ; 
 int /*<<< orphan*/  glk_plane_color_ctl_alpha (int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

u32 glk_plane_color_ctl(const struct intel_crtc_state *crtc_state,
			const struct intel_plane_state *plane_state)
{
	struct drm_i915_private *dev_priv =
		to_i915(plane_state->base.plane->dev);
	const struct drm_framebuffer *fb = plane_state->base.fb;
	u32 plane_color_ctl = 0;

	if (INTEL_GEN(dev_priv) < 11) {
		plane_color_ctl |= PLANE_COLOR_PIPE_GAMMA_ENABLE;
		plane_color_ctl |= PLANE_COLOR_PIPE_CSC_ENABLE;
	}
	plane_color_ctl |= PLANE_COLOR_PLANE_GAMMA_DISABLE;
	plane_color_ctl |= glk_plane_color_ctl_alpha(fb->format->format);

	if (fb->format->is_yuv) {
		if (plane_state->base.color_encoding == DRM_COLOR_YCBCR_BT709)
			plane_color_ctl |= PLANE_COLOR_CSC_MODE_YUV709_TO_RGB709;
		else
			plane_color_ctl |= PLANE_COLOR_CSC_MODE_YUV601_TO_RGB709;

		if (plane_state->base.color_range == DRM_COLOR_YCBCR_FULL_RANGE)
			plane_color_ctl |= PLANE_COLOR_YUV_RANGE_CORRECTION_DISABLE;
	}

	return plane_color_ctl;
}