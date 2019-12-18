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
struct drm_plane_state {scalar_t__ crtc; int /*<<< orphan*/  state; } ;
struct drm_plane {int dummy; } ;
struct drm_crtc_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_PLANE_HELPER_NO_SCALING ; 
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 struct drm_crtc_state* drm_atomic_get_existing_crtc_state (int /*<<< orphan*/ ,scalar_t__) ; 
 int drm_atomic_helper_check_plane_state (struct drm_plane_state*,struct drm_crtc_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int vbox_primary_atomic_check(struct drm_plane *plane,
				     struct drm_plane_state *new_state)
{
	struct drm_crtc_state *crtc_state = NULL;

	if (new_state->crtc) {
		crtc_state = drm_atomic_get_existing_crtc_state(
					    new_state->state, new_state->crtc);
		if (WARN_ON(!crtc_state))
			return -EINVAL;
	}

	return drm_atomic_helper_check_plane_state(new_state, crtc_state,
						   DRM_PLANE_HELPER_NO_SCALING,
						   DRM_PLANE_HELPER_NO_SCALING,
						   false, true);
}