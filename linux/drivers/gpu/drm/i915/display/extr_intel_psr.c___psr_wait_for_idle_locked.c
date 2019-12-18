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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ enabled; int /*<<< orphan*/  lock; scalar_t__ psr2_enabled; } ;
struct drm_i915_private {TYPE_1__ psr; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  EDP_PSR2_STATUS ; 
 int /*<<< orphan*/  EDP_PSR2_STATUS_STATE_MASK ; 
 int /*<<< orphan*/  EDP_PSR_STATUS ; 
 int /*<<< orphan*/  EDP_PSR_STATUS_STATE_MASK ; 
 int intel_de_wait_for_clear (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool __psr_wait_for_idle_locked(struct drm_i915_private *dev_priv)
{
	i915_reg_t reg;
	u32 mask;
	int err;

	if (!dev_priv->psr.enabled)
		return false;

	if (dev_priv->psr.psr2_enabled) {
		reg = EDP_PSR2_STATUS;
		mask = EDP_PSR2_STATUS_STATE_MASK;
	} else {
		reg = EDP_PSR_STATUS;
		mask = EDP_PSR_STATUS_STATE_MASK;
	}

	mutex_unlock(&dev_priv->psr.lock);

	err = intel_de_wait_for_clear(dev_priv, reg, mask, 50);
	if (err)
		DRM_ERROR("Timed out waiting for PSR Idle for re-enable\n");

	/* After the unlocked wait, verify that PSR is still wanted! */
	mutex_lock(&dev_priv->psr.lock);
	return err == 0 && dev_priv->psr.enabled;
}