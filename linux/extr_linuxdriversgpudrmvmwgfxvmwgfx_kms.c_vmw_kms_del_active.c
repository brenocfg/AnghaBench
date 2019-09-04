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
struct vmw_private {scalar_t__ num_implicit; int /*<<< orphan*/  global_kms_state_mutex; int /*<<< orphan*/ * implicit_fb; } ;
struct vmw_display_unit {int active_implicit; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void vmw_kms_del_active(struct vmw_private *dev_priv,
			struct vmw_display_unit *du)
{
	mutex_lock(&dev_priv->global_kms_state_mutex);
	if (du->active_implicit) {
		if (--(dev_priv->num_implicit) == 0)
			dev_priv->implicit_fb = NULL;
		du->active_implicit = false;
	}
	mutex_unlock(&dev_priv->global_kms_state_mutex);
}