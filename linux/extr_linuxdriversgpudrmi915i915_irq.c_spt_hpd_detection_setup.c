#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int CHASSIS_CLK_REQ_DURATION (int) ; 
 int CHASSIS_CLK_REQ_DURATION_MASK ; 
 scalar_t__ HAS_PCH_CNP (struct drm_i915_private*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PCH_PORT_HOTPLUG ; 
 int /*<<< orphan*/  PCH_PORT_HOTPLUG2 ; 
 int PORTA_HOTPLUG_ENABLE ; 
 int PORTB_HOTPLUG_ENABLE ; 
 int PORTC_HOTPLUG_ENABLE ; 
 int PORTD_HOTPLUG_ENABLE ; 
 int PORTE_HOTPLUG_ENABLE ; 
 int /*<<< orphan*/  SOUTH_CHICKEN1 ; 

__attribute__((used)) static void spt_hpd_detection_setup(struct drm_i915_private *dev_priv)
{
	u32 val, hotplug;

	/* Display WA #1179 WaHardHangonHotPlug: cnp */
	if (HAS_PCH_CNP(dev_priv)) {
		val = I915_READ(SOUTH_CHICKEN1);
		val &= ~CHASSIS_CLK_REQ_DURATION_MASK;
		val |= CHASSIS_CLK_REQ_DURATION(0xf);
		I915_WRITE(SOUTH_CHICKEN1, val);
	}

	/* Enable digital hotplug on the PCH */
	hotplug = I915_READ(PCH_PORT_HOTPLUG);
	hotplug |= PORTA_HOTPLUG_ENABLE |
		   PORTB_HOTPLUG_ENABLE |
		   PORTC_HOTPLUG_ENABLE |
		   PORTD_HOTPLUG_ENABLE;
	I915_WRITE(PCH_PORT_HOTPLUG, hotplug);

	hotplug = I915_READ(PCH_PORT_HOTPLUG2);
	hotplug |= PORTE_HOTPLUG_ENABLE;
	I915_WRITE(PCH_PORT_HOTPLUG2, hotplug);
}