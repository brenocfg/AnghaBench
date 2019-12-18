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
#define  HPD_PORT_B 130 
#define  HPD_PORT_C 129 
#define  HPD_PORT_D 128 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int PORTB_HOTPLUG_LIVE_STATUS_G4X ; 
 int PORTC_HOTPLUG_LIVE_STATUS_G4X ; 
 int PORTD_HOTPLUG_LIVE_STATUS_G4X ; 
 int /*<<< orphan*/  PORT_HOTPLUG_STAT ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool g4x_digital_port_connected(struct intel_encoder *encoder)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	u32 bit;

	switch (encoder->hpd_pin) {
	case HPD_PORT_B:
		bit = PORTB_HOTPLUG_LIVE_STATUS_G4X;
		break;
	case HPD_PORT_C:
		bit = PORTC_HOTPLUG_LIVE_STATUS_G4X;
		break;
	case HPD_PORT_D:
		bit = PORTD_HOTPLUG_LIVE_STATUS_G4X;
		break;
	default:
		MISSING_CASE(encoder->hpd_pin);
		return false;
	}

	return I915_READ(PORT_HOTPLUG_STAT) & bit;
}