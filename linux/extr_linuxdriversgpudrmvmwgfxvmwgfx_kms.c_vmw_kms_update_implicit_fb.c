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
struct vmw_display_unit {int /*<<< orphan*/  is_implicit; } ;
struct drm_plane {TYPE_1__* state; } ;
struct drm_crtc {struct drm_plane* primary; } ;
struct TYPE_2__ {int /*<<< orphan*/  fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vmw_display_unit* vmw_crtc_to_du (struct drm_crtc*) ; 
 struct vmw_framebuffer* vmw_framebuffer_to_vfb (int /*<<< orphan*/ ) ; 

void vmw_kms_update_implicit_fb(struct vmw_private *dev_priv,
				struct drm_crtc *crtc)
{
	struct vmw_display_unit *du = vmw_crtc_to_du(crtc);
	struct drm_plane *plane = crtc->primary;
	struct vmw_framebuffer *vfb;

	mutex_lock(&dev_priv->global_kms_state_mutex);

	if (!du->is_implicit)
		goto out_unlock;

	vfb = vmw_framebuffer_to_vfb(plane->state->fb);
	WARN_ON_ONCE(dev_priv->num_implicit != 1 &&
		     dev_priv->implicit_fb != vfb);

	dev_priv->implicit_fb = vfb;
out_unlock:
	mutex_unlock(&dev_priv->global_kms_state_mutex);
}