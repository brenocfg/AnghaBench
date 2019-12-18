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
struct mdp5_pipeline {int dummy; } ;
struct mdp5_ctl {int dummy; } ;
struct drm_plane_state {struct drm_framebuffer* fb; int /*<<< orphan*/  crtc; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  crtc_y; int /*<<< orphan*/  crtc_x; int /*<<< orphan*/  src_y; int /*<<< orphan*/  src_x; } ;
struct drm_plane {struct drm_plane_state* state; } ;
struct drm_framebuffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct mdp5_ctl* mdp5_crtc_get_ctl (int /*<<< orphan*/ ) ; 
 struct mdp5_pipeline* mdp5_crtc_get_pipeline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp5_ctl_commit (struct mdp5_ctl*,struct mdp5_pipeline*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdp5_plane_get_flush (struct drm_plane*) ; 
 int mdp5_plane_mode_set (struct drm_plane*,int /*<<< orphan*/ ,struct drm_framebuffer*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ plane_enabled (struct drm_plane_state*) ; 
 int /*<<< orphan*/ * to_mdp5_plane_state (struct drm_plane_state*) ; 

__attribute__((used)) static void mdp5_plane_atomic_async_update(struct drm_plane *plane,
					   struct drm_plane_state *new_state)
{
	struct drm_framebuffer *old_fb = plane->state->fb;

	plane->state->src_x = new_state->src_x;
	plane->state->src_y = new_state->src_y;
	plane->state->crtc_x = new_state->crtc_x;
	plane->state->crtc_y = new_state->crtc_y;

	if (plane_enabled(new_state)) {
		struct mdp5_ctl *ctl;
		struct mdp5_pipeline *pipeline =
					mdp5_crtc_get_pipeline(new_state->crtc);
		int ret;

		ret = mdp5_plane_mode_set(plane, new_state->crtc, new_state->fb,
				&new_state->src, &new_state->dst);
		WARN_ON(ret < 0);

		ctl = mdp5_crtc_get_ctl(new_state->crtc);

		mdp5_ctl_commit(ctl, pipeline, mdp5_plane_get_flush(plane), true);
	}

	*to_mdp5_plane_state(plane->state) =
		*to_mdp5_plane_state(new_state);

	new_state->fb = old_fb;
}