#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct intel_dp {int dummy; } ;
struct TYPE_5__ {struct drm_device* dev; } ;
struct TYPE_6__ {TYPE_2__ base; } ;
struct intel_digital_port {TYPE_3__ base; } ;
struct TYPE_4__ {int active; scalar_t__ psr2_enabled; int /*<<< orphan*/  lock; } ;
struct drm_i915_private {TYPE_1__ psr; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDP_PSR2_CTL ; 
 int EDP_PSR2_ENABLE ; 
 int /*<<< orphan*/  EDP_PSR_CTL ; 
 int EDP_PSR_ENABLE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 int /*<<< orphan*/  hsw_activate_psr1 (struct intel_dp*) ; 
 int /*<<< orphan*/  hsw_activate_psr2 (struct intel_dp*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void intel_psr_activate(struct intel_dp *intel_dp)
{
	struct intel_digital_port *intel_dig_port = dp_to_dig_port(intel_dp);
	struct drm_device *dev = intel_dig_port->base.base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);

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