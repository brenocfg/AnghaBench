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
struct TYPE_6__ {int offset; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_4__ {unsigned int rotation; int /*<<< orphan*/  src; int /*<<< orphan*/  visible; struct drm_framebuffer* fb; } ;
struct intel_plane_state {TYPE_3__ aux; TYPE_1__ base; } ;
struct intel_crtc_state {int dummy; } ;
struct drm_framebuffer {scalar_t__ modifier; int width; int height; TYPE_2__* format; } ;
struct TYPE_5__ {scalar_t__ format; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 scalar_t__ DRM_FORMAT_MOD_LINEAR ; 
 scalar_t__ DRM_FORMAT_NV12 ; 
 unsigned int DRM_MODE_REFLECT_X ; 
 int /*<<< orphan*/  DRM_MODE_ROTATE_270 ; 
 int EINVAL ; 
 scalar_t__ I915_FORMAT_MOD_Y_TILED_CCS ; 
 scalar_t__ I915_FORMAT_MOD_Yf_TILED_CCS ; 
 int /*<<< orphan*/  drm_rect_rotate (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ drm_rotation_90_or_270 (unsigned int) ; 
 int skl_check_ccs_aux_surface (struct intel_plane_state*) ; 
 int skl_check_main_surface (struct intel_crtc_state const*,struct intel_plane_state*) ; 
 int skl_check_nv12_aux_surface (struct intel_plane_state*) ; 
 int skl_check_nv12_surface (struct intel_crtc_state const*,struct intel_plane_state*) ; 

int skl_check_plane_surface(const struct intel_crtc_state *crtc_state,
			    struct intel_plane_state *plane_state)
{
	const struct drm_framebuffer *fb = plane_state->base.fb;
	unsigned int rotation = plane_state->base.rotation;
	int ret;

	if (rotation & DRM_MODE_REFLECT_X &&
	    fb->modifier == DRM_FORMAT_MOD_LINEAR) {
		DRM_DEBUG_KMS("horizontal flip is not supported with linear surface formats\n");
		return -EINVAL;
	}

	if (!plane_state->base.visible)
		return 0;

	/* Rotate src coordinates to match rotated GTT view */
	if (drm_rotation_90_or_270(rotation))
		drm_rect_rotate(&plane_state->base.src,
				fb->width << 16, fb->height << 16,
				DRM_MODE_ROTATE_270);

	/*
	 * Handle the AUX surface first since
	 * the main surface setup depends on it.
	 */
	if (fb->format->format == DRM_FORMAT_NV12) {
		ret = skl_check_nv12_surface(crtc_state, plane_state);
		if (ret)
			return ret;
		ret = skl_check_nv12_aux_surface(plane_state);
		if (ret)
			return ret;
	} else if (fb->modifier == I915_FORMAT_MOD_Y_TILED_CCS ||
		   fb->modifier == I915_FORMAT_MOD_Yf_TILED_CCS) {
		ret = skl_check_ccs_aux_surface(plane_state);
		if (ret)
			return ret;
	} else {
		plane_state->aux.offset = ~0xfff;
		plane_state->aux.x = 0;
		plane_state->aux.y = 0;
	}

	ret = skl_check_main_surface(crtc_state, plane_state);
	if (ret)
		return ret;

	return 0;
}