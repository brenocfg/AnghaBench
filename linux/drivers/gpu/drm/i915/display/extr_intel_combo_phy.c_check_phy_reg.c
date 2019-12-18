#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  reg; } ;
typedef  TYPE_1__ i915_reg_t ;
typedef  enum phy { ____Placeholder_phy } phy ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int I915_READ (TYPE_1__) ; 
 int /*<<< orphan*/  phy_name (int) ; 

__attribute__((used)) static bool check_phy_reg(struct drm_i915_private *dev_priv,
			  enum phy phy, i915_reg_t reg, u32 mask,
			  u32 expected_val)
{
	u32 val = I915_READ(reg);

	if ((val & mask) != expected_val) {
		DRM_DEBUG_DRIVER("Combo PHY %c reg %08x state mismatch: "
				 "current %08x mask %08x expected %08x\n",
				 phy_name(phy),
				 reg.reg, val, mask, expected_val);
		return false;
	}

	return true;
}