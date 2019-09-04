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
struct TYPE_4__ {struct drm_device* dev; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
struct intel_digital_port {TYPE_2__ base; } ;
struct intel_crtc_state {int /*<<< orphan*/  has_psr; } ;
struct TYPE_6__ {int /*<<< orphan*/  work; int /*<<< orphan*/  lock; } ;
struct drm_i915_private {TYPE_3__ psr; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_PSR (struct drm_i915_private*) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_psr_disable_locked (struct intel_dp*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

void intel_psr_disable(struct intel_dp *intel_dp,
		       const struct intel_crtc_state *old_crtc_state)
{
	struct intel_digital_port *intel_dig_port = dp_to_dig_port(intel_dp);
	struct drm_device *dev = intel_dig_port->base.base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);

	if (!old_crtc_state->has_psr)
		return;

	if (WARN_ON(!CAN_PSR(dev_priv)))
		return;

	mutex_lock(&dev_priv->psr.lock);
	intel_psr_disable_locked(intel_dp);
	mutex_unlock(&dev_priv->psr.lock);
	cancel_work_sync(&dev_priv->psr.work);
}