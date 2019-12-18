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
struct intel_dp {int /*<<< orphan*/  aux; } ;
struct TYPE_2__ {int enabled; scalar_t__ psr2_enabled; int /*<<< orphan*/  lock; } ;
struct drm_i915_private {TYPE_1__ psr; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_PSR_EN_CFG ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  EDP_PSR2_STATUS ; 
 int /*<<< orphan*/  EDP_PSR2_STATUS_STATE_MASK ; 
 int /*<<< orphan*/  EDP_PSR_STATUS ; 
 int /*<<< orphan*/  EDP_PSR_STATUS_STATE_MASK ; 
 struct drm_i915_private* dp_to_i915 (struct intel_dp*) ; 
 int /*<<< orphan*/  drm_dp_dpcd_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_de_wait_for_clear (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_psr_exit (struct drm_i915_private*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void intel_psr_disable_locked(struct intel_dp *intel_dp)
{
	struct drm_i915_private *dev_priv = dp_to_i915(intel_dp);
	i915_reg_t psr_status;
	u32 psr_status_mask;

	lockdep_assert_held(&dev_priv->psr.lock);

	if (!dev_priv->psr.enabled)
		return;

	DRM_DEBUG_KMS("Disabling PSR%s\n",
		      dev_priv->psr.psr2_enabled ? "2" : "1");

	intel_psr_exit(dev_priv);

	if (dev_priv->psr.psr2_enabled) {
		psr_status = EDP_PSR2_STATUS;
		psr_status_mask = EDP_PSR2_STATUS_STATE_MASK;
	} else {
		psr_status = EDP_PSR_STATUS;
		psr_status_mask = EDP_PSR_STATUS_STATE_MASK;
	}

	/* Wait till PSR is idle */
	if (intel_de_wait_for_clear(dev_priv, psr_status,
				    psr_status_mask, 2000))
		DRM_ERROR("Timed out waiting PSR idle state\n");

	/* Disable PSR on Sink */
	drm_dp_dpcd_writeb(&intel_dp->aux, DP_PSR_EN_CFG, 0);

	dev_priv->psr.enabled = false;
}