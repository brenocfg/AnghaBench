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
struct drm_plane_state {int crtc_h; int crtc_w; int src_x; int src_y; int src_h; int src_w; scalar_t__ crtc_y; scalar_t__ crtc_x; struct drm_crtc* crtc; struct drm_plane* plane; } ;
struct drm_plane {int /*<<< orphan*/  fb; int /*<<< orphan*/  state; TYPE_1__* funcs; } ;
struct drm_framebuffer {int dummy; } ;
struct TYPE_4__ {int vdisplay; int hdisplay; } ;
struct drm_crtc {TYPE_2__ mode; struct drm_plane* primary; } ;
struct TYPE_3__ {struct drm_plane_state* (* atomic_duplicate_state ) (struct drm_plane*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 struct drm_plane_state* drm_atomic_helper_plane_duplicate_state (struct drm_plane*) ; 
 int /*<<< orphan*/  drm_atomic_helper_plane_reset (struct drm_plane*) ; 
 int /*<<< orphan*/  drm_atomic_set_fb_for_plane (struct drm_plane_state*,int /*<<< orphan*/ ) ; 
 int drm_plane_helper_commit (struct drm_plane*,struct drm_plane_state*,struct drm_framebuffer*) ; 
 struct drm_plane_state* stub1 (struct drm_plane*) ; 

int drm_helper_crtc_mode_set_base(struct drm_crtc *crtc, int x, int y,
				  struct drm_framebuffer *old_fb)
{
	struct drm_plane_state *plane_state;
	struct drm_plane *plane = crtc->primary;

	if (plane->funcs->atomic_duplicate_state)
		plane_state = plane->funcs->atomic_duplicate_state(plane);
	else {
		if (!plane->state)
			drm_atomic_helper_plane_reset(plane);

		plane_state = drm_atomic_helper_plane_duplicate_state(plane);
	}
	if (!plane_state)
		return -ENOMEM;
	plane_state->plane = plane;

	plane_state->crtc = crtc;
	drm_atomic_set_fb_for_plane(plane_state, crtc->primary->fb);
	plane_state->crtc_x = 0;
	plane_state->crtc_y = 0;
	plane_state->crtc_h = crtc->mode.vdisplay;
	plane_state->crtc_w = crtc->mode.hdisplay;
	plane_state->src_x = x << 16;
	plane_state->src_y = y << 16;
	plane_state->src_h = crtc->mode.vdisplay << 16;
	plane_state->src_w = crtc->mode.hdisplay << 16;

	return drm_plane_helper_commit(plane, plane_state, old_fb);
}