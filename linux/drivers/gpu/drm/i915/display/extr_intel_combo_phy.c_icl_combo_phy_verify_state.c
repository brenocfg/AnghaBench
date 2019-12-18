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
 int /*<<< orphan*/  CL_POWER_DOWN_ENABLE ; 
 int /*<<< orphan*/  ICL_PORT_CL_DW5 (int) ; 
 int /*<<< orphan*/  ICL_PORT_COMP_DW8 (int) ; 
 int /*<<< orphan*/  IREFGEN ; 
 int PHY_A ; 
 int check_phy_reg (struct drm_i915_private*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cnl_verify_procmon_ref_values (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  icl_combo_phy_enabled (struct drm_i915_private*,int) ; 

__attribute__((used)) static bool icl_combo_phy_verify_state(struct drm_i915_private *dev_priv,
				       enum phy phy)
{
	bool ret;

	if (!icl_combo_phy_enabled(dev_priv, phy))
		return false;

	ret = cnl_verify_procmon_ref_values(dev_priv, phy);

	if (phy == PHY_A)
		ret &= check_phy_reg(dev_priv, phy, ICL_PORT_COMP_DW8(phy),
				     IREFGEN, IREFGEN);

	ret &= check_phy_reg(dev_priv, phy, ICL_PORT_CL_DW5(phy),
			     CL_POWER_DOWN_ENABLE, CL_POWER_DOWN_ENABLE);

	return ret;
}