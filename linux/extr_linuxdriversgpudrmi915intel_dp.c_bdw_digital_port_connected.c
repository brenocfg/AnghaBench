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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {scalar_t__ hpd_pin; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN8_DE_PORT_ISR ; 
 int GEN8_PORT_DP_A_HOTPLUG ; 
 scalar_t__ HPD_PORT_A ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int cpt_digital_port_connected (struct intel_encoder*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool bdw_digital_port_connected(struct intel_encoder *encoder)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);

	if (encoder->hpd_pin == HPD_PORT_A)
		return I915_READ(GEN8_DE_PORT_ISR) & GEN8_PORT_DP_A_HOTPLUG;
	else
		return cpt_digital_port_connected(encoder);
}