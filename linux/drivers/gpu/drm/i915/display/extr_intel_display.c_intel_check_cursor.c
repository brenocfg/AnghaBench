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
struct TYPE_2__ {int /*<<< orphan*/  visible; struct drm_framebuffer* fb; } ;
struct intel_plane_state {TYPE_1__ base; } ;
struct intel_crtc_state {int /*<<< orphan*/  base; } ;
struct drm_framebuffer {scalar_t__ modifier; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 scalar_t__ DRM_FORMAT_MOD_LINEAR ; 
 int /*<<< orphan*/  DRM_PLANE_HELPER_NO_SCALING ; 
 int EINVAL ; 
 int drm_atomic_helper_check_plane_state (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int intel_cursor_check_surface (struct intel_plane_state*) ; 
 int intel_plane_check_src_coordinates (struct intel_plane_state*) ; 

__attribute__((used)) static int intel_check_cursor(struct intel_crtc_state *crtc_state,
			      struct intel_plane_state *plane_state)
{
	const struct drm_framebuffer *fb = plane_state->base.fb;
	int ret;

	if (fb && fb->modifier != DRM_FORMAT_MOD_LINEAR) {
		DRM_DEBUG_KMS("cursor cannot be tiled\n");
		return -EINVAL;
	}

	ret = drm_atomic_helper_check_plane_state(&plane_state->base,
						  &crtc_state->base,
						  DRM_PLANE_HELPER_NO_SCALING,
						  DRM_PLANE_HELPER_NO_SCALING,
						  true, true);
	if (ret)
		return ret;

	ret = intel_cursor_check_surface(plane_state);
	if (ret)
		return ret;

	if (!plane_state->base.visible)
		return 0;

	ret = intel_plane_check_src_coordinates(plane_state);
	if (ret)
		return ret;

	return 0;
}