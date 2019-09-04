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
 int DIGITAL_PORTA_HOTPLUG_ENABLE ; 
 int DIGITAL_PORTA_PULSE_DURATION_2ms ; 
 int DIGITAL_PORTA_PULSE_DURATION_MASK ; 
 int /*<<< orphan*/  DIGITAL_PORT_HOTPLUG_CNTRL ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ilk_hpd_detection_setup(struct drm_i915_private *dev_priv)
{
	u32 hotplug;

	/*
	 * Enable digital hotplug on the CPU, and configure the DP short pulse
	 * duration to 2ms (which is the minimum in the Display Port spec)
	 * The pulse duration bits are reserved on HSW+.
	 */
	hotplug = I915_READ(DIGITAL_PORT_HOTPLUG_CNTRL);
	hotplug &= ~DIGITAL_PORTA_PULSE_DURATION_MASK;
	hotplug |= DIGITAL_PORTA_HOTPLUG_ENABLE |
		   DIGITAL_PORTA_PULSE_DURATION_2ms;
	I915_WRITE(DIGITAL_PORT_HOTPLUG_CNTRL, hotplug);
}