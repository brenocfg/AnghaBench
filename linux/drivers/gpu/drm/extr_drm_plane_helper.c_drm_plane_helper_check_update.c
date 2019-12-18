#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct drm_rect {int /*<<< orphan*/  y1; int /*<<< orphan*/  x1; } ;
struct drm_plane_state {unsigned int rotation; int visible; struct drm_rect dst; struct drm_rect src; int /*<<< orphan*/  crtc_h; int /*<<< orphan*/  crtc_w; int /*<<< orphan*/  crtc_y; int /*<<< orphan*/  crtc_x; int /*<<< orphan*/  src_h; int /*<<< orphan*/  src_w; int /*<<< orphan*/  src_y; int /*<<< orphan*/  src_x; struct drm_framebuffer* fb; struct drm_crtc* crtc; struct drm_plane* plane; } ;
struct drm_plane {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_crtc_state {int /*<<< orphan*/  mode; int /*<<< orphan*/  enable; struct drm_crtc* crtc; } ;
struct drm_crtc {int /*<<< orphan*/  mode; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int drm_atomic_helper_check_plane_state (struct drm_plane_state*,struct drm_crtc_state*,int,int,int,int) ; 
 int /*<<< orphan*/  drm_rect_height (struct drm_rect*) ; 
 int /*<<< orphan*/  drm_rect_width (struct drm_rect*) ; 

__attribute__((used)) static int drm_plane_helper_check_update(struct drm_plane *plane,
					 struct drm_crtc *crtc,
					 struct drm_framebuffer *fb,
					 struct drm_rect *src,
					 struct drm_rect *dst,
					 unsigned int rotation,
					 int min_scale,
					 int max_scale,
					 bool can_position,
					 bool can_update_disabled,
					 bool *visible)
{
	struct drm_plane_state plane_state = {
		.plane = plane,
		.crtc = crtc,
		.fb = fb,
		.src_x = src->x1,
		.src_y = src->y1,
		.src_w = drm_rect_width(src),
		.src_h = drm_rect_height(src),
		.crtc_x = dst->x1,
		.crtc_y = dst->y1,
		.crtc_w = drm_rect_width(dst),
		.crtc_h = drm_rect_height(dst),
		.rotation = rotation,
		.visible = *visible,
	};
	struct drm_crtc_state crtc_state = {
		.crtc = crtc,
		.enable = crtc->enabled,
		.mode = crtc->mode,
	};
	int ret;

	ret = drm_atomic_helper_check_plane_state(&plane_state, &crtc_state,
						  min_scale, max_scale,
						  can_position,
						  can_update_disabled);
	if (ret)
		return ret;

	*src = plane_state.src;
	*dst = plane_state.dst;
	*visible = plane_state.visible;

	return 0;
}