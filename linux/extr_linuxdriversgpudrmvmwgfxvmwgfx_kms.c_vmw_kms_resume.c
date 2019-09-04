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
struct vmw_private {int /*<<< orphan*/ * suspend_state; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int drm_atomic_helper_resume (struct drm_device*,int /*<<< orphan*/ *) ; 
 struct vmw_private* vmw_priv (struct drm_device*) ; 

int vmw_kms_resume(struct drm_device *dev)
{
	struct vmw_private *dev_priv = vmw_priv(dev);
	int ret;

	if (WARN_ON(!dev_priv->suspend_state))
		return 0;

	ret = drm_atomic_helper_resume(dev, dev_priv->suspend_state);
	dev_priv->suspend_state = NULL;

	return ret;
}