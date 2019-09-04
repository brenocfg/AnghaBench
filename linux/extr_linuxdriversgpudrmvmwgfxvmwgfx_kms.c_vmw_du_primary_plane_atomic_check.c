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
struct vmw_private {int num_implicit; int /*<<< orphan*/  global_kms_state_mutex; struct vmw_framebuffer* implicit_fb; } ;
struct vmw_framebuffer {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct vmw_display_unit {scalar_t__ active_implicit; TYPE_1__ connector; } ;
struct vmw_connector_state {scalar_t__ is_implicit; } ;
struct drm_plane_state {struct drm_crtc* crtc; int /*<<< orphan*/  state; struct drm_framebuffer* fb; } ;
struct drm_plane {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_PLANE_HELPER_NO_SCALING ; 
 int EINVAL ; 
 struct drm_crtc_state* drm_atomic_get_new_crtc_state (int /*<<< orphan*/ ,struct drm_crtc*) ; 
 int drm_atomic_helper_check_plane_state (struct drm_plane_state*,struct drm_crtc_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vmw_connector_state* vmw_connector_state_to_vcs (int /*<<< orphan*/ ) ; 
 struct vmw_display_unit* vmw_crtc_to_du (struct drm_crtc*) ; 
 struct vmw_framebuffer* vmw_framebuffer_to_vfb (struct drm_framebuffer*) ; 
 struct vmw_private* vmw_priv (int /*<<< orphan*/ ) ; 

int vmw_du_primary_plane_atomic_check(struct drm_plane *plane,
				      struct drm_plane_state *state)
{
	struct drm_crtc_state *crtc_state = NULL;
	struct drm_framebuffer *new_fb = state->fb;
	int ret;

	if (state->crtc)
		crtc_state = drm_atomic_get_new_crtc_state(state->state, state->crtc);

	ret = drm_atomic_helper_check_plane_state(state, crtc_state,
						  DRM_PLANE_HELPER_NO_SCALING,
						  DRM_PLANE_HELPER_NO_SCALING,
						  false, true);

	if (!ret && new_fb) {
		struct drm_crtc *crtc = state->crtc;
		struct vmw_connector_state *vcs;
		struct vmw_display_unit *du = vmw_crtc_to_du(crtc);
		struct vmw_private *dev_priv = vmw_priv(crtc->dev);
		struct vmw_framebuffer *vfb = vmw_framebuffer_to_vfb(new_fb);

		vcs = vmw_connector_state_to_vcs(du->connector.state);

		/* Only one active implicit framebuffer at a time. */
		mutex_lock(&dev_priv->global_kms_state_mutex);
		if (vcs->is_implicit && dev_priv->implicit_fb &&
		    !(dev_priv->num_implicit == 1 && du->active_implicit)
		    && dev_priv->implicit_fb != vfb) {
			DRM_ERROR("Multiple implicit framebuffers "
				  "not supported.\n");
			ret = -EINVAL;
		}
		mutex_unlock(&dev_priv->global_kms_state_mutex);
	}


	return ret;
}