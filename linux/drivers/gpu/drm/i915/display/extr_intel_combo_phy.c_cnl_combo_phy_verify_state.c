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
 int /*<<< orphan*/  CNL_PORT_CL1CM_DW5 ; 
 int PHY_A ; 
 int check_phy_reg (struct drm_i915_private*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cnl_combo_phy_enabled (struct drm_i915_private*) ; 
 int cnl_verify_procmon_ref_values (struct drm_i915_private*,int) ; 

__attribute__((used)) static bool cnl_combo_phy_verify_state(struct drm_i915_private *dev_priv)
{
	enum phy phy = PHY_A;
	bool ret;

	if (!cnl_combo_phy_enabled(dev_priv))
		return false;

	ret = cnl_verify_procmon_ref_values(dev_priv, phy);

	ret &= check_phy_reg(dev_priv, phy, CNL_PORT_CL1CM_DW5,
			     CL_POWER_DOWN_ENABLE, CL_POWER_DOWN_ENABLE);

	return ret;
}