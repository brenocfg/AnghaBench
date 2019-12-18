#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct drm_rect {int x1; } ;
struct TYPE_5__ {struct drm_rect dst; struct drm_rect src; struct drm_framebuffer* fb; } ;
struct intel_plane_state {TYPE_3__* color_plane; TYPE_1__ base; } ;
struct drm_display_mode {int flags; } ;
struct TYPE_6__ {struct drm_display_mode adjusted_mode; } ;
struct intel_crtc_state {TYPE_2__ base; } ;
struct drm_framebuffer {TYPE_4__* format; } ;
struct TYPE_8__ {unsigned int* cpp; } ;
struct TYPE_7__ {unsigned int stride; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 int EINVAL ; 
 int drm_rect_height (struct drm_rect const*) ; 
 int drm_rect_width (struct drm_rect const*) ; 

__attribute__((used)) static int
g4x_sprite_check_scaling(struct intel_crtc_state *crtc_state,
			 struct intel_plane_state *plane_state)
{
	const struct drm_framebuffer *fb = plane_state->base.fb;
	const struct drm_rect *src = &plane_state->base.src;
	const struct drm_rect *dst = &plane_state->base.dst;
	int src_x, src_w, src_h, crtc_w, crtc_h;
	const struct drm_display_mode *adjusted_mode =
		&crtc_state->base.adjusted_mode;
	unsigned int stride = plane_state->color_plane[0].stride;
	unsigned int cpp = fb->format->cpp[0];
	unsigned int width_bytes;
	int min_width, min_height;

	crtc_w = drm_rect_width(dst);
	crtc_h = drm_rect_height(dst);

	src_x = src->x1 >> 16;
	src_w = drm_rect_width(src) >> 16;
	src_h = drm_rect_height(src) >> 16;

	if (src_w == crtc_w && src_h == crtc_h)
		return 0;

	min_width = 3;

	if (adjusted_mode->flags & DRM_MODE_FLAG_INTERLACE) {
		if (src_h & 1) {
			DRM_DEBUG_KMS("Source height must be even with interlaced modes\n");
			return -EINVAL;
		}
		min_height = 6;
	} else {
		min_height = 3;
	}

	width_bytes = ((src_x * cpp) & 63) + src_w * cpp;

	if (src_w < min_width || src_h < min_height ||
	    src_w > 2048 || src_h > 2048) {
		DRM_DEBUG_KMS("Source dimensions (%dx%d) exceed hardware limits (%dx%d - %dx%d)\n",
			      src_w, src_h, min_width, min_height, 2048, 2048);
		return -EINVAL;
	}

	if (width_bytes > 4096) {
		DRM_DEBUG_KMS("Fetch width (%d) exceeds hardware max with scaling (%u)\n",
			      width_bytes, 4096);
		return -EINVAL;
	}

	if (stride > 4096) {
		DRM_DEBUG_KMS("Stride (%u) exceeds hardware max with scaling (%u)\n",
			      stride, 4096);
		return -EINVAL;
	}

	return 0;
}