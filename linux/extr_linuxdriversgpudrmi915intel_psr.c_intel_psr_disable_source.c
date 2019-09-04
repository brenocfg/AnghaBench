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
typedef  int /*<<< orphan*/  u32 ;
struct intel_dp {int dummy; } ;
struct TYPE_4__ {struct drm_device* dev; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
struct intel_digital_port {TYPE_2__ base; } ;
struct TYPE_6__ {int active; scalar_t__ psr2_enabled; } ;
struct drm_i915_private {TYPE_3__ psr; } ;
struct drm_device {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  EDP_PSR2_CTL ; 
 int EDP_PSR2_ENABLE ; 
 int /*<<< orphan*/  EDP_PSR2_STATUS ; 
 int /*<<< orphan*/  EDP_PSR2_STATUS_STATE_MASK ; 
 int /*<<< orphan*/  EDP_PSR_CTL ; 
 int EDP_PSR_ENABLE ; 
 int /*<<< orphan*/  EDP_PSR_STATUS ; 
 int /*<<< orphan*/  EDP_PSR_STATUS_STATE_MASK ; 
 int EDP_SU_TRACK_ENABLE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 scalar_t__ intel_wait_for_register (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void
intel_psr_disable_source(struct intel_dp *intel_dp)
{
	struct intel_digital_port *intel_dig_port = dp_to_dig_port(intel_dp);
	struct drm_device *dev = intel_dig_port->base.base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);

	if (dev_priv->psr.active) {
		i915_reg_t psr_status;
		u32 psr_status_mask;

		if (dev_priv->psr.psr2_enabled) {
			psr_status = EDP_PSR2_STATUS;
			psr_status_mask = EDP_PSR2_STATUS_STATE_MASK;

			I915_WRITE(EDP_PSR2_CTL,
				   I915_READ(EDP_PSR2_CTL) &
				   ~(EDP_PSR2_ENABLE | EDP_SU_TRACK_ENABLE));

		} else {
			psr_status = EDP_PSR_STATUS;
			psr_status_mask = EDP_PSR_STATUS_STATE_MASK;

			I915_WRITE(EDP_PSR_CTL,
				   I915_READ(EDP_PSR_CTL) & ~EDP_PSR_ENABLE);
		}

		/* Wait till PSR is idle */
		if (intel_wait_for_register(dev_priv,
					    psr_status, psr_status_mask, 0,
					    2000))
			DRM_ERROR("Timed out waiting for PSR Idle State\n");

		dev_priv->psr.active = false;
	} else {
		if (dev_priv->psr.psr2_enabled)
			WARN_ON(I915_READ(EDP_PSR2_CTL) & EDP_PSR2_ENABLE);
		else
			WARN_ON(I915_READ(EDP_PSR_CTL) & EDP_PSR_ENABLE);
	}
}