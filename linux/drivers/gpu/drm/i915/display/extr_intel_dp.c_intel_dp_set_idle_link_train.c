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
struct intel_dp {int dummy; } ;
struct TYPE_2__ {int port; } ;
struct intel_digital_port {TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int /*<<< orphan*/  DP_TP_CTL (int) ; 
 int /*<<< orphan*/  DP_TP_CTL_LINK_TRAIN_IDLE ; 
 int /*<<< orphan*/  DP_TP_CTL_LINK_TRAIN_MASK ; 
 int /*<<< orphan*/  DP_TP_STATUS (int) ; 
 int /*<<< orphan*/  DP_TP_STATUS_IDLE_DONE ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  HAS_DDI (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PORT_A ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 struct drm_i915_private* dp_to_i915 (struct intel_dp*) ; 
 scalar_t__ intel_de_wait_for_set (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void intel_dp_set_idle_link_train(struct intel_dp *intel_dp)
{
	struct drm_i915_private *dev_priv = dp_to_i915(intel_dp);
	struct intel_digital_port *intel_dig_port = dp_to_dig_port(intel_dp);
	enum port port = intel_dig_port->base.port;
	u32 val;

	if (!HAS_DDI(dev_priv))
		return;

	val = I915_READ(DP_TP_CTL(port));
	val &= ~DP_TP_CTL_LINK_TRAIN_MASK;
	val |= DP_TP_CTL_LINK_TRAIN_IDLE;
	I915_WRITE(DP_TP_CTL(port), val);

	/*
	 * On PORT_A we can have only eDP in SST mode. There the only reason
	 * we need to set idle transmission mode is to work around a HW issue
	 * where we enable the pipe while not in idle link-training mode.
	 * In this case there is requirement to wait for a minimum number of
	 * idle patterns to be sent.
	 */
	if (port == PORT_A)
		return;

	if (intel_de_wait_for_set(dev_priv, DP_TP_STATUS(port),
				  DP_TP_STATUS_IDLE_DONE, 1))
		DRM_ERROR("Timed out waiting for DP idle patterns\n");
}