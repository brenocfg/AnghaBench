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
struct drm_plane_state {int /*<<< orphan*/  src_h; int /*<<< orphan*/  src_w; int /*<<< orphan*/  src_y; int /*<<< orphan*/  src_x; int /*<<< orphan*/  crtc_h; int /*<<< orphan*/  crtc_w; int /*<<< orphan*/  crtc_y; int /*<<< orphan*/  crtc_x; int /*<<< orphan*/  fb; int /*<<< orphan*/  crtc; } ;
struct drm_plane {struct drm_plane_state* state; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int mdp4_plane_mode_set (struct drm_plane*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mdp4_plane_atomic_update(struct drm_plane *plane,
				     struct drm_plane_state *old_state)
{
	struct drm_plane_state *state = plane->state;
	int ret;

	ret = mdp4_plane_mode_set(plane,
			state->crtc, state->fb,
			state->crtc_x, state->crtc_y,
			state->crtc_w, state->crtc_h,
			state->src_x,  state->src_y,
			state->src_w, state->src_h);
	/* atomic_check should have ensured that this doesn't fail */
	WARN_ON(ret < 0);
}