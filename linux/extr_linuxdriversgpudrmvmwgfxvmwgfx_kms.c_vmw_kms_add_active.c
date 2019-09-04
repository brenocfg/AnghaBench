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
struct vmw_private {int /*<<< orphan*/  global_kms_state_mutex; int /*<<< orphan*/  num_implicit; struct vmw_framebuffer* implicit_fb; } ;
struct vmw_framebuffer {int dummy; } ;
struct vmw_display_unit {int active_implicit; scalar_t__ is_implicit; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void vmw_kms_add_active(struct vmw_private *dev_priv,
			struct vmw_display_unit *du,
			struct vmw_framebuffer *vfb)
{
	mutex_lock(&dev_priv->global_kms_state_mutex);
	WARN_ON_ONCE(!dev_priv->num_implicit && dev_priv->implicit_fb);

	if (!du->active_implicit && du->is_implicit) {
		dev_priv->implicit_fb = vfb;
		du->active_implicit = true;
		dev_priv->num_implicit++;
	}
	mutex_unlock(&dev_priv->global_kms_state_mutex);
}