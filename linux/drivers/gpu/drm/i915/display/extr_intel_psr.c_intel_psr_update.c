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
struct intel_dp {int dummy; } ;
struct intel_crtc_state {scalar_t__ crc_enabled; scalar_t__ has_psr; } ;
struct i915_psr {int enabled; int psr2_enabled; int /*<<< orphan*/  lock; int /*<<< orphan*/  work; int /*<<< orphan*/  busy_frontbuffer_bits; int /*<<< orphan*/  active; int /*<<< orphan*/  debug; int /*<<< orphan*/  dp; } ;
struct drm_i915_private {struct i915_psr psr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_PSR (struct drm_i915_private*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 struct intel_dp* READ_ONCE (int /*<<< orphan*/ ) ; 
 struct drm_i915_private* dp_to_i915 (struct intel_dp*) ; 
 int intel_psr2_enabled (struct drm_i915_private*,struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  intel_psr_disable_locked (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_psr_enable_locked (struct drm_i915_private*,struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psr_force_hw_tracking_exit (struct drm_i915_private*) ; 
 scalar_t__ psr_global_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void intel_psr_update(struct intel_dp *intel_dp,
		      const struct intel_crtc_state *crtc_state)
{
	struct drm_i915_private *dev_priv = dp_to_i915(intel_dp);
	struct i915_psr *psr = &dev_priv->psr;
	bool enable, psr2_enable;

	if (!CAN_PSR(dev_priv) || READ_ONCE(psr->dp) != intel_dp)
		return;

	mutex_lock(&dev_priv->psr.lock);

	enable = crtc_state->has_psr && psr_global_enabled(psr->debug);
	psr2_enable = intel_psr2_enabled(dev_priv, crtc_state);

	if (enable == psr->enabled && psr2_enable == psr->psr2_enabled) {
		/* Force a PSR exit when enabling CRC to avoid CRC timeouts */
		if (crtc_state->crc_enabled && psr->enabled)
			psr_force_hw_tracking_exit(dev_priv);
		else if (INTEL_GEN(dev_priv) < 9 && psr->enabled) {
			/*
			 * Activate PSR again after a force exit when enabling
			 * CRC in older gens
			 */
			if (!dev_priv->psr.active &&
			    !dev_priv->psr.busy_frontbuffer_bits)
				schedule_work(&dev_priv->psr.work);
		}

		goto unlock;
	}

	if (psr->enabled)
		intel_psr_disable_locked(intel_dp);

	if (enable)
		intel_psr_enable_locked(dev_priv, crtc_state);

unlock:
	mutex_unlock(&dev_priv->psr.lock);
}