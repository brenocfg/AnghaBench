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
struct i915_power_well {int id; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum i915_power_well_id { ____Placeholder_i915_power_well_id } i915_power_well_id ;

/* Variables and functions */
 int /*<<< orphan*/  HSW_PWR_WELL_CTL_BIOS (int) ; 
 int /*<<< orphan*/  HSW_PWR_WELL_CTL_DRIVER (int) ; 
 int HSW_PWR_WELL_CTL_REQ (int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hsw_power_well_sync_hw(struct drm_i915_private *dev_priv,
				   struct i915_power_well *power_well)
{
	enum i915_power_well_id id = power_well->id;
	u32 mask = HSW_PWR_WELL_CTL_REQ(id);
	u32 bios_req = I915_READ(HSW_PWR_WELL_CTL_BIOS(id));

	/* Take over the request bit if set by BIOS. */
	if (bios_req & mask) {
		u32 drv_req = I915_READ(HSW_PWR_WELL_CTL_DRIVER(id));

		if (!(drv_req & mask))
			I915_WRITE(HSW_PWR_WELL_CTL_DRIVER(id), drv_req | mask);
		I915_WRITE(HSW_PWR_WELL_CTL_BIOS(id), bios_req & ~mask);
	}
}