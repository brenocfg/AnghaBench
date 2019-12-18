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
 int GEN11_HOTPLUG_CTL_ENABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEN11_TBT_HOTPLUG_CTL ; 
 int /*<<< orphan*/  GEN11_TC_HOTPLUG_CTL ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PORT_TC1 ; 
 int /*<<< orphan*/  PORT_TC2 ; 
 int /*<<< orphan*/  PORT_TC3 ; 
 int /*<<< orphan*/  PORT_TC4 ; 

__attribute__((used)) static void gen11_hpd_detection_setup(struct drm_i915_private *dev_priv)
{
	u32 hotplug;

	hotplug = I915_READ(GEN11_TC_HOTPLUG_CTL);
	hotplug |= GEN11_HOTPLUG_CTL_ENABLE(PORT_TC1) |
		   GEN11_HOTPLUG_CTL_ENABLE(PORT_TC2) |
		   GEN11_HOTPLUG_CTL_ENABLE(PORT_TC3) |
		   GEN11_HOTPLUG_CTL_ENABLE(PORT_TC4);
	I915_WRITE(GEN11_TC_HOTPLUG_CTL, hotplug);

	hotplug = I915_READ(GEN11_TBT_HOTPLUG_CTL);
	hotplug |= GEN11_HOTPLUG_CTL_ENABLE(PORT_TC1) |
		   GEN11_HOTPLUG_CTL_ENABLE(PORT_TC2) |
		   GEN11_HOTPLUG_CTL_ENABLE(PORT_TC3) |
		   GEN11_HOTPLUG_CTL_ENABLE(PORT_TC4);
	I915_WRITE(GEN11_TBT_HOTPLUG_CTL, hotplug);
}