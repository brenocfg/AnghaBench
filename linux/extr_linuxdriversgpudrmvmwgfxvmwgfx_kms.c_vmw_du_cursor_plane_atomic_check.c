#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  image; } ;
struct vmw_surface {TYPE_1__ snooper; } ;
struct drm_rect {int dummy; } ;
struct drm_plane_state {int crtc_w; int crtc_h; int /*<<< orphan*/  visible; int /*<<< orphan*/  crtc; struct drm_framebuffer* fb; } ;
struct drm_plane {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  bo; } ;
struct TYPE_5__ {struct vmw_surface* surface; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_MODE_ROTATE_0 ; 
 int /*<<< orphan*/  DRM_PLANE_HELPER_NO_SCALING ; 
 int EINVAL ; 
 int drm_plane_helper_check_update (struct drm_plane*,int /*<<< orphan*/ ,struct drm_framebuffer*,struct drm_rect*,struct drm_rect*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 struct drm_rect drm_plane_state_dest (struct drm_plane_state*) ; 
 struct drm_rect drm_plane_state_src (struct drm_plane_state*) ; 
 TYPE_3__* vmw_framebuffer_to_vfb (struct drm_framebuffer*) ; 
 TYPE_2__* vmw_framebuffer_to_vfbs (struct drm_framebuffer*) ; 

int vmw_du_cursor_plane_atomic_check(struct drm_plane *plane,
				     struct drm_plane_state *new_state)
{
	int ret = 0;
	struct vmw_surface *surface = NULL;
	struct drm_framebuffer *fb = new_state->fb;

	struct drm_rect src = drm_plane_state_src(new_state);
	struct drm_rect dest = drm_plane_state_dest(new_state);

	/* Turning off */
	if (!fb)
		return ret;

	ret = drm_plane_helper_check_update(plane, new_state->crtc, fb,
					    &src, &dest,
					    DRM_MODE_ROTATE_0,
					    DRM_PLANE_HELPER_NO_SCALING,
					    DRM_PLANE_HELPER_NO_SCALING,
					    true, true, &new_state->visible);
	if (!ret)
		return ret;

	/* A lot of the code assumes this */
	if (new_state->crtc_w != 64 || new_state->crtc_h != 64) {
		DRM_ERROR("Invalid cursor dimensions (%d, %d)\n",
			  new_state->crtc_w, new_state->crtc_h);
		ret = -EINVAL;
	}

	if (!vmw_framebuffer_to_vfb(fb)->bo)
		surface = vmw_framebuffer_to_vfbs(fb)->surface;

	if (surface && !surface->snooper.image) {
		DRM_ERROR("surface not suitable for cursor\n");
		ret = -EINVAL;
	}

	return ret;
}