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
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int ICP_DDIA_HPD_ENABLE ; 
 int ICP_DDIB_HPD_ENABLE ; 
 int ICP_TC_HPD_ENABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORT_TC1 ; 
 int /*<<< orphan*/  PORT_TC2 ; 
 int /*<<< orphan*/  PORT_TC3 ; 
 int /*<<< orphan*/  PORT_TC4 ; 
 int /*<<< orphan*/  SHOTPLUG_CTL_DDI ; 
 int /*<<< orphan*/  SHOTPLUG_CTL_TC ; 

__attribute__((used)) static void icp_hpd_detection_setup(struct drm_i915_private *dev_priv)
{
	u32 hotplug;

	hotplug = I915_READ(SHOTPLUG_CTL_DDI);
	hotplug |= ICP_DDIA_HPD_ENABLE |
		   ICP_DDIB_HPD_ENABLE;
	I915_WRITE(SHOTPLUG_CTL_DDI, hotplug);

	hotplug = I915_READ(SHOTPLUG_CTL_TC);
	hotplug |= ICP_TC_HPD_ENABLE(PORT_TC1) |
		   ICP_TC_HPD_ENABLE(PORT_TC2) |
		   ICP_TC_HPD_ENABLE(PORT_TC3) |
		   ICP_TC_HPD_ENABLE(PORT_TC4);
	I915_WRITE(SHOTPLUG_CTL_TC, hotplug);
}