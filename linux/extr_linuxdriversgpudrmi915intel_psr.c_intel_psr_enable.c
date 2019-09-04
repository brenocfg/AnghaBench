#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct intel_dp {int dummy; } ;
struct TYPE_5__ {struct drm_device* dev; } ;
struct TYPE_6__ {TYPE_1__ base; } ;
struct intel_digital_port {TYPE_2__ base; } ;
struct intel_crtc_state {int /*<<< orphan*/  has_psr2; int /*<<< orphan*/  has_psr; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; struct intel_dp* enabled; scalar_t__ busy_frontbuffer_bits; int /*<<< orphan*/  psr2_enabled; } ;
struct TYPE_7__ {int dp; } ;
struct drm_i915_private {TYPE_4__ psr; TYPE_3__ drrs; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_PSR (struct drm_i915_private*) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 scalar_t__ WARN_ON (int) ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_psr_activate (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_psr_enable_sink (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_psr_enable_source (struct intel_dp*,struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  intel_psr_setup_vsc (struct intel_dp*,struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

void intel_psr_enable(struct intel_dp *intel_dp,
		      const struct intel_crtc_state *crtc_state)
{
	struct intel_digital_port *intel_dig_port = dp_to_dig_port(intel_dp);
	struct drm_device *dev = intel_dig_port->base.base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);

	if (!crtc_state->has_psr)
		return;

	if (WARN_ON(!CAN_PSR(dev_priv)))
		return;

	WARN_ON(dev_priv->drrs.dp);
	mutex_lock(&dev_priv->psr.lock);
	if (dev_priv->psr.enabled) {
		DRM_DEBUG_KMS("PSR already in use\n");
		goto unlock;
	}

	dev_priv->psr.psr2_enabled = crtc_state->has_psr2;
	dev_priv->psr.busy_frontbuffer_bits = 0;

	intel_psr_setup_vsc(intel_dp, crtc_state);
	intel_psr_enable_sink(intel_dp);
	intel_psr_enable_source(intel_dp, crtc_state);
	dev_priv->psr.enabled = intel_dp;

	intel_psr_activate(intel_dp);

unlock:
	mutex_unlock(&dev_priv->psr.lock);
}