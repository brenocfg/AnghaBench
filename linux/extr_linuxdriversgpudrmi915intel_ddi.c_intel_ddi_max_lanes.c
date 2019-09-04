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
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int port; TYPE_1__ base; } ;
struct intel_digital_port {int saved_port_bits; TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int DDI_A_4_LANES ; 
 int /*<<< orphan*/  DDI_BUF_CTL (int) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int PORT_A ; 
 int PORT_E ; 
 scalar_t__ intel_ddi_a_force_4_lanes (struct intel_digital_port*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
intel_ddi_max_lanes(struct intel_digital_port *intel_dport)
{
	struct drm_i915_private *dev_priv = to_i915(intel_dport->base.base.dev);
	enum port port = intel_dport->base.port;
	int max_lanes = 4;

	if (INTEL_GEN(dev_priv) >= 11)
		return max_lanes;

	if (port == PORT_A || port == PORT_E) {
		if (I915_READ(DDI_BUF_CTL(PORT_A)) & DDI_A_4_LANES)
			max_lanes = port == PORT_A ? 4 : 0;
		else
			/* Both A and E share 2 lanes */
			max_lanes = 2;
	}

	/*
	 * Some BIOS might fail to set this bit on port A if eDP
	 * wasn't lit up at boot.  Force this bit set when needed
	 * so we use the proper lane count for our calculations.
	 */
	if (intel_ddi_a_force_4_lanes(intel_dport)) {
		DRM_DEBUG_KMS("Forcing DDI_A_4_LANES for port A\n");
		intel_dport->saved_port_bits |= DDI_A_4_LANES;
		max_lanes = 4;
	}

	return max_lanes;
}