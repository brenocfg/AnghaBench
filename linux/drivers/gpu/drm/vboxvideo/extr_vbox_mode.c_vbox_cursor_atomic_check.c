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
typedef  scalar_t__ u32 ;
struct drm_plane_state {scalar_t__ crtc_w; scalar_t__ crtc_h; int /*<<< orphan*/  fb; scalar_t__ crtc; int /*<<< orphan*/  state; } ;
struct drm_plane {int dummy; } ;
struct drm_crtc_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_PLANE_HELPER_NO_SCALING ; 
 int EINVAL ; 
 scalar_t__ VBOX_MAX_CURSOR_HEIGHT ; 
 scalar_t__ VBOX_MAX_CURSOR_WIDTH ; 
 scalar_t__ WARN_ON (int) ; 
 struct drm_crtc_state* drm_atomic_get_existing_crtc_state (int /*<<< orphan*/ ,scalar_t__) ; 
 int drm_atomic_helper_check_plane_state (struct drm_plane_state*,struct drm_crtc_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int vbox_cursor_atomic_check(struct drm_plane *plane,
				    struct drm_plane_state *new_state)
{
	struct drm_crtc_state *crtc_state = NULL;
	u32 width = new_state->crtc_w;
	u32 height = new_state->crtc_h;
	int ret;

	if (new_state->crtc) {
		crtc_state = drm_atomic_get_existing_crtc_state(
					    new_state->state, new_state->crtc);
		if (WARN_ON(!crtc_state))
			return -EINVAL;
	}

	ret = drm_atomic_helper_check_plane_state(new_state, crtc_state,
						  DRM_PLANE_HELPER_NO_SCALING,
						  DRM_PLANE_HELPER_NO_SCALING,
						  true, true);
	if (ret)
		return ret;

	if (!new_state->fb)
		return 0;

	if (width > VBOX_MAX_CURSOR_WIDTH || height > VBOX_MAX_CURSOR_HEIGHT ||
	    width == 0 || height == 0)
		return -EINVAL;

	return 0;
}