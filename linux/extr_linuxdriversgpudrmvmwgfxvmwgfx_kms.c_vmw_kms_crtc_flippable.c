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
struct vmw_private {int num_implicit; int /*<<< orphan*/  global_kms_state_mutex; } ;
struct vmw_display_unit {int /*<<< orphan*/  is_implicit; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vmw_display_unit* vmw_crtc_to_du (struct drm_crtc*) ; 

bool vmw_kms_crtc_flippable(struct vmw_private *dev_priv,
			    struct drm_crtc *crtc)
{
	struct vmw_display_unit *du = vmw_crtc_to_du(crtc);
	bool ret;

	mutex_lock(&dev_priv->global_kms_state_mutex);
	ret = !du->is_implicit || dev_priv->num_implicit == 1;
	mutex_unlock(&dev_priv->global_kms_state_mutex);

	return ret;
}