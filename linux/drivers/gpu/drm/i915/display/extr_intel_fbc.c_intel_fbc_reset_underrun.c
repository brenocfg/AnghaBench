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
struct TYPE_2__ {int underrun_detected; char* no_fbc_reason; int /*<<< orphan*/  lock; int /*<<< orphan*/  underrun_work; } ;
struct drm_i915_private {TYPE_1__ fbc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int intel_fbc_reset_underrun(struct drm_i915_private *dev_priv)
{
	int ret;

	cancel_work_sync(&dev_priv->fbc.underrun_work);

	ret = mutex_lock_interruptible(&dev_priv->fbc.lock);
	if (ret)
		return ret;

	if (dev_priv->fbc.underrun_detected) {
		DRM_DEBUG_KMS("Re-allowing FBC after fifo underrun\n");
		dev_priv->fbc.no_fbc_reason = "FIFO underrun cleared";
	}

	dev_priv->fbc.underrun_detected = false;
	mutex_unlock(&dev_priv->fbc.lock);

	return 0;
}