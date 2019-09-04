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
struct drm_plane_state {int /*<<< orphan*/  crtc; int /*<<< orphan*/  state; struct drm_framebuffer* fb; } ;
struct drm_plane {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_crtc_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_PLANE_HELPER_NO_SCALING ; 
 scalar_t__ IS_ERR (struct drm_crtc_state*) ; 
 int PTR_ERR (struct drm_crtc_state*) ; 
 struct drm_crtc_state* drm_atomic_get_crtc_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drm_atomic_helper_check_plane_state (struct drm_plane_state*,struct drm_crtc_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int mtk_plane_atomic_check(struct drm_plane *plane,
				  struct drm_plane_state *state)
{
	struct drm_framebuffer *fb = state->fb;
	struct drm_crtc_state *crtc_state;

	if (!fb)
		return 0;

	if (!state->crtc)
		return 0;

	crtc_state = drm_atomic_get_crtc_state(state->state, state->crtc);
	if (IS_ERR(crtc_state))
		return PTR_ERR(crtc_state);

	return drm_atomic_helper_check_plane_state(state, crtc_state,
						   DRM_PLANE_HELPER_NO_SCALING,
						   DRM_PLANE_HELPER_NO_SCALING,
						   true, true);
}