#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct intel_dp {int dummy; } ;
struct intel_crtc_state {int /*<<< orphan*/  has_psr; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  debug; } ;
struct TYPE_3__ {int dp; } ;
struct drm_i915_private {TYPE_2__ psr; TYPE_1__ drrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_PSR (struct drm_i915_private*) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 scalar_t__ WARN_ON (int) ; 
 struct drm_i915_private* dp_to_i915 (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_psr_enable_locked (struct drm_i915_private*,struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psr_global_enabled (int /*<<< orphan*/ ) ; 

void intel_psr_enable(struct intel_dp *intel_dp,
		      const struct intel_crtc_state *crtc_state)
{
	struct drm_i915_private *dev_priv = dp_to_i915(intel_dp);

	if (!crtc_state->has_psr)
		return;

	if (WARN_ON(!CAN_PSR(dev_priv)))
		return;

	WARN_ON(dev_priv->drrs.dp);

	mutex_lock(&dev_priv->psr.lock);

	if (!psr_global_enabled(dev_priv->psr.debug)) {
		DRM_DEBUG_KMS("PSR disabled by flag\n");
		goto unlock;
	}

	intel_psr_enable_locked(dev_priv, crtc_state);

unlock:
	mutex_unlock(&dev_priv->psr.lock);
}