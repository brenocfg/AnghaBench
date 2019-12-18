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
struct drm_i915_private {int dummy; } ;
typedef  enum phy { ____Placeholder_phy } phy ;

/* Variables and functions */
 int COMP_INIT ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICL_PHY_MISC (int) ; 
 int ICL_PHY_MISC_DE_IO_COMP_PWR_DOWN ; 
 int /*<<< orphan*/  ICL_PORT_COMP_DW0 (int) ; 
 scalar_t__ IS_ELKHARTLAKE (struct drm_i915_private*) ; 
 int PHY_C ; 

__attribute__((used)) static bool icl_combo_phy_enabled(struct drm_i915_private *dev_priv,
				  enum phy phy)
{
	/* The PHY C added by EHL has no PHY_MISC register */
	if (IS_ELKHARTLAKE(dev_priv) && phy == PHY_C)
		return I915_READ(ICL_PORT_COMP_DW0(phy)) & COMP_INIT;
	else
		return !(I915_READ(ICL_PHY_MISC(phy)) &
			 ICL_PHY_MISC_DE_IO_COMP_PWR_DOWN) &&
			(I915_READ(ICL_PORT_COMP_DW0(phy)) & COMP_INIT);
}