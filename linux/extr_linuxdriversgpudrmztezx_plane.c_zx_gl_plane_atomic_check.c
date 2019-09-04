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
struct drm_plane_state {struct drm_crtc* crtc; int /*<<< orphan*/  state; struct drm_framebuffer* fb; } ;
struct drm_plane {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_crtc_state {int /*<<< orphan*/  enable; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_PLANE_HELPER_NO_SCALING ; 
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 struct drm_crtc_state* drm_atomic_get_existing_crtc_state (int /*<<< orphan*/ ,struct drm_crtc*) ; 
 int drm_atomic_helper_check_plane_state (struct drm_plane_state*,struct drm_crtc_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int zx_gl_plane_atomic_check(struct drm_plane *plane,
				    struct drm_plane_state *plane_state)
{
	struct drm_framebuffer *fb = plane_state->fb;
	struct drm_crtc *crtc = plane_state->crtc;
	struct drm_crtc_state *crtc_state;

	if (!crtc || !fb)
		return 0;

	crtc_state = drm_atomic_get_existing_crtc_state(plane_state->state,
							crtc);
	if (WARN_ON(!crtc_state))
		return -EINVAL;

	/* nothing to check when disabling or disabled */
	if (!crtc_state->enable)
		return 0;

	/* plane must be enabled */
	if (!plane_state->crtc)
		return -EINVAL;

	return drm_atomic_helper_check_plane_state(plane_state, crtc_state,
						   DRM_PLANE_HELPER_NO_SCALING,
						   DRM_PLANE_HELPER_NO_SCALING,
						   false, true);
}