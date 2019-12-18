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
struct vop_win_data {TYPE_1__* phy; } ;
struct vop_win {struct vop_win_data* data; } ;
struct TYPE_5__ {int x1; } ;
struct drm_plane_state {int rotation; TYPE_2__ src; int /*<<< orphan*/  visible; int /*<<< orphan*/  state; struct drm_framebuffer* fb; struct drm_crtc* crtc; } ;
struct drm_plane {int dummy; } ;
struct drm_framebuffer {TYPE_3__* format; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {int dummy; } ;
struct TYPE_6__ {scalar_t__ is_yuv; int /*<<< orphan*/  format; } ;
struct TYPE_4__ {scalar_t__ scl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int DRM_MODE_REFLECT_Y ; 
 int DRM_PLANE_HELPER_NO_SCALING ; 
 int EINVAL ; 
 int FRAC_16_16 (int,int) ; 
 scalar_t__ WARN_ON (int) ; 
 struct drm_crtc_state* drm_atomic_get_existing_crtc_state (int /*<<< orphan*/ ,struct drm_crtc*) ; 
 int drm_atomic_helper_check_plane_state (struct drm_plane_state*,struct drm_crtc_state*,int,int,int,int) ; 
 struct vop_win* to_vop_win (struct drm_plane*) ; 
 int vop_convert_format (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vop_plane_atomic_check(struct drm_plane *plane,
			   struct drm_plane_state *state)
{
	struct drm_crtc *crtc = state->crtc;
	struct drm_crtc_state *crtc_state;
	struct drm_framebuffer *fb = state->fb;
	struct vop_win *vop_win = to_vop_win(plane);
	const struct vop_win_data *win = vop_win->data;
	int ret;
	int min_scale = win->phy->scl ? FRAC_16_16(1, 8) :
					DRM_PLANE_HELPER_NO_SCALING;
	int max_scale = win->phy->scl ? FRAC_16_16(8, 1) :
					DRM_PLANE_HELPER_NO_SCALING;

	if (!crtc || !fb)
		return 0;

	crtc_state = drm_atomic_get_existing_crtc_state(state->state, crtc);
	if (WARN_ON(!crtc_state))
		return -EINVAL;

	ret = drm_atomic_helper_check_plane_state(state, crtc_state,
						  min_scale, max_scale,
						  true, true);
	if (ret)
		return ret;

	if (!state->visible)
		return 0;

	ret = vop_convert_format(fb->format->format);
	if (ret < 0)
		return ret;

	/*
	 * Src.x1 can be odd when do clip, but yuv plane start point
	 * need align with 2 pixel.
	 */
	if (fb->format->is_yuv && ((state->src.x1 >> 16) % 2)) {
		DRM_ERROR("Invalid Source: Yuv format not support odd xpos\n");
		return -EINVAL;
	}

	if (fb->format->is_yuv && state->rotation & DRM_MODE_REFLECT_Y) {
		DRM_ERROR("Invalid Source: Yuv format does not support this rotation\n");
		return -EINVAL;
	}

	return 0;
}