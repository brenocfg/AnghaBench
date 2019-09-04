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
struct drm_plane_state {int visible; scalar_t__ state; struct drm_crtc* crtc; scalar_t__ fb; } ;
struct drm_plane {int dummy; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {struct drm_crtc_state* state; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct drm_crtc_state* drm_atomic_get_existing_crtc_state (scalar_t__,struct drm_crtc*) ; 
 int drm_atomic_helper_check_plane_state (struct drm_plane_state*,struct drm_crtc_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

int armada_drm_plane_atomic_check(struct drm_plane *plane,
	struct drm_plane_state *state)
{
	if (state->fb && !WARN_ON(!state->crtc)) {
		struct drm_crtc *crtc = state->crtc;
		struct drm_crtc_state *crtc_state;

		if (state->state)
			crtc_state = drm_atomic_get_existing_crtc_state(state->state, crtc);
		else
			crtc_state = crtc->state;
		return drm_atomic_helper_check_plane_state(state, crtc_state,
							   0, INT_MAX,
							   true, false);
	} else {
		state->visible = false;
	}
	return 0;
}