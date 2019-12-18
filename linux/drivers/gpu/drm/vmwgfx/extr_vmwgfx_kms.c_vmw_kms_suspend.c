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
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * drm_atomic_helper_suspend (struct drm_device*) ; 
 struct vmw_private* vmw_priv (struct drm_device*) ; 

int vmw_kms_suspend(struct drm_device *dev)
{
	struct vmw_private *dev_priv = vmw_priv(dev);

	dev_priv->suspend_state = drm_atomic_helper_suspend(dev);
	if (IS_ERR(dev_priv->suspend_state)) {
		int ret = PTR_ERR(dev_priv->suspend_state);

		DRM_ERROR("Failed kms suspend: %d\n", ret);
		dev_priv->suspend_state = NULL;

		return ret;
	}

	return 0;
}