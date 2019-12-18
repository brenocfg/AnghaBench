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
struct drm_rect {int x1; int y1; int x2; int y2; } ;
struct TYPE_3__ {int /*<<< orphan*/  rotation; struct drm_rect src; struct drm_framebuffer* fb; } ;
struct intel_plane_state {TYPE_1__ base; } ;
struct drm_framebuffer {TYPE_2__* format; } ;
struct TYPE_4__ {int hsub; int vsub; int /*<<< orphan*/  is_yuv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int,int,char*) ; 
 int EINVAL ; 
 int drm_rect_height (struct drm_rect*) ; 
 int drm_rect_width (struct drm_rect*) ; 
 int drm_rotation_90_or_270 (int /*<<< orphan*/ ) ; 
 int max (int,int) ; 

int intel_plane_check_src_coordinates(struct intel_plane_state *plane_state)
{
	const struct drm_framebuffer *fb = plane_state->base.fb;
	struct drm_rect *src = &plane_state->base.src;
	u32 src_x, src_y, src_w, src_h, hsub, vsub;
	bool rotated = drm_rotation_90_or_270(plane_state->base.rotation);

	/*
	 * Hardware doesn't handle subpixel coordinates.
	 * Adjust to (macro)pixel boundary, but be careful not to
	 * increase the source viewport size, because that could
	 * push the downscaling factor out of bounds.
	 */
	src_x = src->x1 >> 16;
	src_w = drm_rect_width(src) >> 16;
	src_y = src->y1 >> 16;
	src_h = drm_rect_height(src) >> 16;

	src->x1 = src_x << 16;
	src->x2 = (src_x + src_w) << 16;
	src->y1 = src_y << 16;
	src->y2 = (src_y + src_h) << 16;

	if (!fb->format->is_yuv)
		return 0;

	/* YUV specific checks */
	if (!rotated) {
		hsub = fb->format->hsub;
		vsub = fb->format->vsub;
	} else {
		hsub = vsub = max(fb->format->hsub, fb->format->vsub);
	}

	if (src_x % hsub || src_w % hsub) {
		DRM_DEBUG_KMS("src x/w (%u, %u) must be a multiple of %u for %sYUV planes\n",
			      src_x, src_w, hsub, rotated ? "rotated " : "");
		return -EINVAL;
	}

	if (src_y % vsub || src_h % vsub) {
		DRM_DEBUG_KMS("src y/h (%u, %u) must be a multiple of %u for %sYUV planes\n",
			      src_y, src_h, vsub, rotated ? "rotated " : "");
		return -EINVAL;
	}

	return 0;
}