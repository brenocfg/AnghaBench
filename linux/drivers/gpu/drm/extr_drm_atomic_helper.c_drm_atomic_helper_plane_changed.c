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
struct drm_plane_state {scalar_t__ crtc; } ;
struct drm_plane {int dummy; } ;
struct drm_crtc_state {int planes_changed; } ;
struct drm_atomic_state {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 struct drm_crtc_state* drm_atomic_get_new_crtc_state (struct drm_atomic_state*,scalar_t__) ; 

__attribute__((used)) static void
drm_atomic_helper_plane_changed(struct drm_atomic_state *state,
				struct drm_plane_state *old_plane_state,
				struct drm_plane_state *plane_state,
				struct drm_plane *plane)
{
	struct drm_crtc_state *crtc_state;

	if (old_plane_state->crtc) {
		crtc_state = drm_atomic_get_new_crtc_state(state,
							   old_plane_state->crtc);

		if (WARN_ON(!crtc_state))
			return;

		crtc_state->planes_changed = true;
	}

	if (plane_state->crtc) {
		crtc_state = drm_atomic_get_new_crtc_state(state, plane_state->crtc);

		if (WARN_ON(!crtc_state))
			return;

		crtc_state->planes_changed = true;
	}
}