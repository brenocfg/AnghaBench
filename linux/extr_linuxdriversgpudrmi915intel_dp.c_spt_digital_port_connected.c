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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {int hpd_pin; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
#define  HPD_PORT_A 129 
#define  HPD_PORT_E 128 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDEISR ; 
 int SDE_PORTA_HOTPLUG_SPT ; 
 int SDE_PORTE_HOTPLUG_SPT ; 
 int cpt_digital_port_connected (struct intel_encoder*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool spt_digital_port_connected(struct intel_encoder *encoder)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	u32 bit;

	switch (encoder->hpd_pin) {
	case HPD_PORT_A:
		bit = SDE_PORTA_HOTPLUG_SPT;
		break;
	case HPD_PORT_E:
		bit = SDE_PORTE_HOTPLUG_SPT;
		break;
	default:
		return cpt_digital_port_connected(encoder);
	}

	return I915_READ(SDEISR) & bit;
}