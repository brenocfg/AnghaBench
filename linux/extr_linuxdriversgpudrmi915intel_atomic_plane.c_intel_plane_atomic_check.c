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
typedef  struct drm_plane_state {struct drm_crtc* crtc; struct drm_atomic_state* state; } const drm_plane_state ;
struct drm_plane {int dummy; } ;
typedef  struct drm_crtc_state const drm_crtc_state ;
struct drm_crtc {int dummy; } ;
struct drm_atomic_state {int dummy; } ;

/* Variables and functions */
 struct drm_crtc_state const* drm_atomic_get_new_crtc_state (struct drm_atomic_state*,struct drm_crtc*) ; 
 struct drm_crtc_state const* drm_atomic_get_old_crtc_state (struct drm_atomic_state*,struct drm_crtc*) ; 
 struct drm_plane_state const* drm_atomic_get_old_plane_state (struct drm_atomic_state*,struct drm_plane*) ; 
 int intel_plane_atomic_check_with_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_intel_crtc_state (struct drm_crtc_state const*) ; 
 int /*<<< orphan*/  to_intel_plane_state (struct drm_plane_state const*) ; 

__attribute__((used)) static int intel_plane_atomic_check(struct drm_plane *plane,
				    struct drm_plane_state *new_plane_state)
{
	struct drm_atomic_state *state = new_plane_state->state;
	const struct drm_plane_state *old_plane_state =
		drm_atomic_get_old_plane_state(state, plane);
	struct drm_crtc *crtc = new_plane_state->crtc ?: old_plane_state->crtc;
	const struct drm_crtc_state *old_crtc_state;
	struct drm_crtc_state *new_crtc_state;

	if (!crtc)
		return 0;

	old_crtc_state = drm_atomic_get_old_crtc_state(state, crtc);
	new_crtc_state = drm_atomic_get_new_crtc_state(state, crtc);

	return intel_plane_atomic_check_with_state(to_intel_crtc_state(old_crtc_state),
						   to_intel_crtc_state(new_crtc_state),
						   to_intel_plane_state(old_plane_state),
						   to_intel_plane_state(new_plane_state));
}