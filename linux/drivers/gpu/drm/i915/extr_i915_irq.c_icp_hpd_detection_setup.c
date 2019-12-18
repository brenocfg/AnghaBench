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
 int /*<<< orphan*/  SHOTPLUG_CTL_DDI ; 
 int /*<<< orphan*/  SHOTPLUG_CTL_TC ; 

__attribute__((used)) static void icp_hpd_detection_setup(struct drm_i915_private *dev_priv,
				    u32 ddi_hotplug_enable_mask,
				    u32 tc_hotplug_enable_mask)
{
	u32 hotplug;

	hotplug = I915_READ(SHOTPLUG_CTL_DDI);
	hotplug |= ddi_hotplug_enable_mask;
	I915_WRITE(SHOTPLUG_CTL_DDI, hotplug);

	if (tc_hotplug_enable_mask) {
		hotplug = I915_READ(SHOTPLUG_CTL_TC);
		hotplug |= tc_hotplug_enable_mask;
		I915_WRITE(SHOTPLUG_CTL_TC, hotplug);
	}
}