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
struct drm_plane_state {struct drm_framebuffer* fb; int /*<<< orphan*/ * crtc; struct drm_plane* plane; } ;
struct drm_plane {int /*<<< orphan*/  state; TYPE_1__* funcs; int /*<<< orphan*/  crtc; } ;
struct drm_modeset_acquire_ctx {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct TYPE_2__ {struct drm_plane_state* (* atomic_duplicate_state ) (struct drm_plane*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 struct drm_plane_state* drm_atomic_helper_plane_duplicate_state (struct drm_plane*) ; 
 int /*<<< orphan*/  drm_atomic_helper_plane_reset (struct drm_plane*) ; 
 int /*<<< orphan*/  drm_atomic_set_fb_for_plane (struct drm_plane_state*,int /*<<< orphan*/ *) ; 
 int drm_plane_helper_commit (struct drm_plane*,struct drm_plane_state*,struct drm_framebuffer*) ; 
 struct drm_plane_state* stub1 (struct drm_plane*) ; 

int drm_plane_helper_disable(struct drm_plane *plane,
			     struct drm_modeset_acquire_ctx *ctx)
{
	struct drm_plane_state *plane_state;
	struct drm_framebuffer *old_fb;

	/* crtc helpers love to call disable functions for already disabled hw
	 * functions. So cope with that. */
	if (!plane->crtc)
		return 0;

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

	plane_state->crtc = NULL;
	old_fb = plane_state->fb;
	drm_atomic_set_fb_for_plane(plane_state, NULL);

	return drm_plane_helper_commit(plane, plane_state, old_fb);
}