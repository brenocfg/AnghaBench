#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct i915_power_well_regs {int /*<<< orphan*/  driver; } ;
struct i915_power_well {TYPE_2__* desc; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;
typedef  enum phy { ____Placeholder_phy } phy ;
struct TYPE_3__ {int idx; struct i915_power_well_regs* regs; } ;
struct TYPE_4__ {TYPE_1__ hsw; } ;

/* Variables and functions */
 int HSW_PWR_WELL_CTL_REQ (int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ICL_AUX_ANAOVRD1 (int) ; 
 int ICL_AUX_ANAOVRD1_ENABLE ; 
 int ICL_AUX_ANAOVRD1_LDO_BYPASS ; 
 int ICL_AUX_PW_TO_PHY (int) ; 
 int ICL_LANE_ENABLE_AUX ; 
 int /*<<< orphan*/  ICL_PORT_CL_DW12 (int) ; 
 int ICL_PW_CTL_IDX_AUX_A ; 
 int ICL_PW_CTL_IDX_AUX_B ; 
 int ICL_PW_CTL_IDX_AUX_C ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_ELKHARTLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_TIGERLAKE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  hsw_wait_for_power_well_enable (struct drm_i915_private*,struct i915_power_well*) ; 
 int /*<<< orphan*/  intel_bios_is_port_edp (struct drm_i915_private*,int) ; 

__attribute__((used)) static void
icl_combo_phy_aux_power_well_enable(struct drm_i915_private *dev_priv,
				    struct i915_power_well *power_well)
{
	const struct i915_power_well_regs *regs = power_well->desc->hsw.regs;
	int pw_idx = power_well->desc->hsw.idx;
	enum phy phy = ICL_AUX_PW_TO_PHY(pw_idx);
	u32 val;
	int wa_idx_max;

	val = I915_READ(regs->driver);
	I915_WRITE(regs->driver, val | HSW_PWR_WELL_CTL_REQ(pw_idx));

	if (INTEL_GEN(dev_priv) < 12) {
		val = I915_READ(ICL_PORT_CL_DW12(phy));
		I915_WRITE(ICL_PORT_CL_DW12(phy), val | ICL_LANE_ENABLE_AUX);
	}

	hsw_wait_for_power_well_enable(dev_priv, power_well);

	/* Display WA #1178: icl, tgl */
	if (IS_TIGERLAKE(dev_priv))
		wa_idx_max = ICL_PW_CTL_IDX_AUX_C;
	else
		wa_idx_max = ICL_PW_CTL_IDX_AUX_B;

	if (!IS_ELKHARTLAKE(dev_priv) &&
	    pw_idx >= ICL_PW_CTL_IDX_AUX_A && pw_idx <= wa_idx_max &&
	    !intel_bios_is_port_edp(dev_priv, (enum port)phy)) {
		val = I915_READ(ICL_AUX_ANAOVRD1(pw_idx));
		val |= ICL_AUX_ANAOVRD1_ENABLE | ICL_AUX_ANAOVRD1_LDO_BYPASS;
		I915_WRITE(ICL_AUX_ANAOVRD1(pw_idx), val);
	}
}