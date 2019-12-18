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
struct intel_dp {int dummy; } ;
struct TYPE_2__ {int active; scalar_t__ psr2_enabled; int /*<<< orphan*/  lock; } ;
struct drm_i915_private {TYPE_1__ psr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDP_PSR2_CTL ; 
 int EDP_PSR2_ENABLE ; 
 int /*<<< orphan*/  EDP_PSR_CTL ; 
 int EDP_PSR_ENABLE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct drm_i915_private* dp_to_i915 (struct intel_dp*) ; 
 int /*<<< orphan*/  hsw_activate_psr1 (struct intel_dp*) ; 
 int /*<<< orphan*/  hsw_activate_psr2 (struct intel_dp*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void intel_psr_activate(struct intel_dp *intel_dp)
{
	struct drm_i915_private *dev_priv = dp_to_i915(intel_dp);

	if (INTEL_GEN(dev_priv) >= 9)
		WARN_ON(I915_READ(EDP_PSR2_CTL) & EDP_PSR2_ENABLE);
	WARN_ON(I915_READ(EDP_PSR_CTL) & EDP_PSR_ENABLE);
	WARN_ON(dev_priv->psr.active);
	lockdep_assert_held(&dev_priv->psr.lock);

	/* psr1 and psr2 are mutually exclusive.*/
	if (dev_priv->psr.psr2_enabled)
		hsw_activate_psr2(intel_dp);
	else
		hsw_activate_psr1(intel_dp);

	dev_priv->psr.active = true;
}