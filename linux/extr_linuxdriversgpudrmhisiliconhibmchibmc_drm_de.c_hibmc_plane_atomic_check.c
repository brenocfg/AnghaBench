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
typedef  scalar_t__ u32 ;
struct drm_plane_state {int src_w; int src_h; scalar_t__ crtc_w; scalar_t__ crtc_h; scalar_t__ crtc_x; scalar_t__ crtc_y; int /*<<< orphan*/  state; struct drm_crtc* crtc; struct drm_framebuffer* fb; } ;
struct drm_plane {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct TYPE_2__ {scalar_t__ hdisplay; scalar_t__ vdisplay; } ;
struct drm_crtc_state {TYPE_1__ adjusted_mode; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_ATOMIC (char*) ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct drm_crtc_state*) ; 
 int PTR_ERR (struct drm_crtc_state*) ; 
 struct drm_crtc_state* drm_atomic_get_crtc_state (int /*<<< orphan*/ ,struct drm_crtc*) ; 

__attribute__((used)) static int hibmc_plane_atomic_check(struct drm_plane *plane,
				    struct drm_plane_state *state)
{
	struct drm_framebuffer *fb = state->fb;
	struct drm_crtc *crtc = state->crtc;
	struct drm_crtc_state *crtc_state;
	u32 src_w = state->src_w >> 16;
	u32 src_h = state->src_h >> 16;

	if (!crtc || !fb)
		return 0;

	crtc_state = drm_atomic_get_crtc_state(state->state, crtc);
	if (IS_ERR(crtc_state))
		return PTR_ERR(crtc_state);

	if (src_w != state->crtc_w || src_h != state->crtc_h) {
		DRM_DEBUG_ATOMIC("scale not support\n");
		return -EINVAL;
	}

	if (state->crtc_x < 0 || state->crtc_y < 0) {
		DRM_DEBUG_ATOMIC("crtc_x/y of drm_plane state is invalid\n");
		return -EINVAL;
	}

	if (state->crtc_x + state->crtc_w >
	    crtc_state->adjusted_mode.hdisplay ||
	    state->crtc_y + state->crtc_h >
	    crtc_state->adjusted_mode.vdisplay) {
		DRM_DEBUG_ATOMIC("visible portion of plane is invalid\n");
		return -EINVAL;
	}

	return 0;
}