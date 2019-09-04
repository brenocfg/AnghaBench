#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct drm_plane_state {int crtc_x; int crtc_y; unsigned int crtc_h; unsigned int crtc_w; void* src_w; void* src_h; void* src_y; void* src_x; struct drm_crtc* crtc; struct drm_plane* plane; } ;
struct drm_plane {int /*<<< orphan*/  fb; int /*<<< orphan*/  state; TYPE_1__* funcs; } ;
struct drm_modeset_acquire_ctx {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_crtc {int dummy; } ;
struct TYPE_2__ {struct drm_plane_state* (* atomic_duplicate_state ) (struct drm_plane*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 struct drm_plane_state* drm_atomic_helper_plane_duplicate_state (struct drm_plane*) ; 
 int /*<<< orphan*/  drm_atomic_helper_plane_reset (struct drm_plane*) ; 
 int /*<<< orphan*/  drm_atomic_set_fb_for_plane (struct drm_plane_state*,struct drm_framebuffer*) ; 
 int drm_plane_helper_commit (struct drm_plane*,struct drm_plane_state*,int /*<<< orphan*/ ) ; 
 struct drm_plane_state* stub1 (struct drm_plane*) ; 

int drm_plane_helper_update(struct drm_plane *plane, struct drm_crtc *crtc,
			    struct drm_framebuffer *fb,
			    int crtc_x, int crtc_y,
			    unsigned int crtc_w, unsigned int crtc_h,
			    uint32_t src_x, uint32_t src_y,
			    uint32_t src_w, uint32_t src_h,
			    struct drm_modeset_acquire_ctx *ctx)
{
	struct drm_plane_state *plane_state;

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
	drm_atomic_set_fb_for_plane(plane_state, fb);
	plane_state->crtc_x = crtc_x;
	plane_state->crtc_y = crtc_y;
	plane_state->crtc_h = crtc_h;
	plane_state->crtc_w = crtc_w;
	plane_state->src_x = src_x;
	plane_state->src_y = src_y;
	plane_state->src_h = src_h;
	plane_state->src_w = src_w;

	return drm_plane_helper_commit(plane, plane_state, plane->fb);
}