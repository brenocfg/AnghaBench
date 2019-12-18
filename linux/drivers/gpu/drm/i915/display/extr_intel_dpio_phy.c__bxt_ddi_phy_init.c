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
struct drm_i915_private {int bxt_phy_grc; int /*<<< orphan*/  uncore; } ;
struct bxt_ddi_phy_info {int rcomp_phy; int pwron_mask; scalar_t__ reset_delay; scalar_t__ dual_channel; } ;
typedef  enum dpio_phy { ____Placeholder_dpio_phy } dpio_phy ;

/* Variables and functions */
 int /*<<< orphan*/  BXT_PHY_CTL_FAMILY (int) ; 
 int /*<<< orphan*/  BXT_PORT_CL1CM_DW0 (int) ; 
 int /*<<< orphan*/  BXT_PORT_CL1CM_DW10 (int) ; 
 int /*<<< orphan*/  BXT_PORT_CL1CM_DW28 (int) ; 
 int /*<<< orphan*/  BXT_PORT_CL1CM_DW9 (int) ; 
 int /*<<< orphan*/  BXT_PORT_CL2CM_DW6 (int) ; 
 int /*<<< orphan*/  BXT_PORT_REF_DW6 (int) ; 
 int /*<<< orphan*/  BXT_PORT_REF_DW8 (int) ; 
 int /*<<< orphan*/  BXT_P_CR_GT_DISP_PWRON ; 
 int COMMON_RESET_DIS ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int DW28_OLDO_DYN_PWR_DOWN_EN ; 
 int DW6_OLDO_DYN_PWR_DOWN_EN ; 
 int GRC_CODE_FAST_SHIFT ; 
 int GRC_CODE_SLOW_SHIFT ; 
 int GRC_DIS ; 
 int GRC_RDY_OVRD ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int IREF0RC_OFFSET_MASK ; 
 int IREF0RC_OFFSET_SHIFT ; 
 int IREF1RC_OFFSET_MASK ; 
 int IREF1RC_OFFSET_SHIFT ; 
 int OCL1_POWER_DOWN_EN ; 
 int PHY_POWER_GOOD ; 
 int PHY_RESERVED ; 
 int SUS_CLK_CONFIG ; 
 scalar_t__ bxt_ddi_phy_is_enabled (struct drm_i915_private*,int) ; 
 scalar_t__ bxt_ddi_phy_verify_state (struct drm_i915_private*,int) ; 
 void* bxt_get_grc (struct drm_i915_private*,int) ; 
 struct bxt_ddi_phy_info* bxt_get_phy_info (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  bxt_phy_wait_grc_done (struct drm_i915_private*,int) ; 
 scalar_t__ intel_wait_for_register_fw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  udelay (scalar_t__) ; 

__attribute__((used)) static void _bxt_ddi_phy_init(struct drm_i915_private *dev_priv,
			      enum dpio_phy phy)
{
	const struct bxt_ddi_phy_info *phy_info;
	u32 val;

	phy_info = bxt_get_phy_info(dev_priv, phy);

	if (bxt_ddi_phy_is_enabled(dev_priv, phy)) {
		/* Still read out the GRC value for state verification */
		if (phy_info->rcomp_phy != -1)
			dev_priv->bxt_phy_grc = bxt_get_grc(dev_priv, phy);

		if (bxt_ddi_phy_verify_state(dev_priv, phy)) {
			DRM_DEBUG_DRIVER("DDI PHY %d already enabled, "
					 "won't reprogram it\n", phy);
			return;
		}

		DRM_DEBUG_DRIVER("DDI PHY %d enabled with invalid state, "
				 "force reprogramming it\n", phy);
	}

	val = I915_READ(BXT_P_CR_GT_DISP_PWRON);
	val |= phy_info->pwron_mask;
	I915_WRITE(BXT_P_CR_GT_DISP_PWRON, val);

	/*
	 * The PHY registers start out inaccessible and respond to reads with
	 * all 1s.  Eventually they become accessible as they power up, then
	 * the reserved bit will give the default 0.  Poll on the reserved bit
	 * becoming 0 to find when the PHY is accessible.
	 * The flag should get set in 100us according to the HW team, but
	 * use 1ms due to occasional timeouts observed with that.
	 */
	if (intel_wait_for_register_fw(&dev_priv->uncore,
				       BXT_PORT_CL1CM_DW0(phy),
				       PHY_RESERVED | PHY_POWER_GOOD,
				       PHY_POWER_GOOD,
				       1))
		DRM_ERROR("timeout during PHY%d power on\n", phy);

	/* Program PLL Rcomp code offset */
	val = I915_READ(BXT_PORT_CL1CM_DW9(phy));
	val &= ~IREF0RC_OFFSET_MASK;
	val |= 0xE4 << IREF0RC_OFFSET_SHIFT;
	I915_WRITE(BXT_PORT_CL1CM_DW9(phy), val);

	val = I915_READ(BXT_PORT_CL1CM_DW10(phy));
	val &= ~IREF1RC_OFFSET_MASK;
	val |= 0xE4 << IREF1RC_OFFSET_SHIFT;
	I915_WRITE(BXT_PORT_CL1CM_DW10(phy), val);

	/* Program power gating */
	val = I915_READ(BXT_PORT_CL1CM_DW28(phy));
	val |= OCL1_POWER_DOWN_EN | DW28_OLDO_DYN_PWR_DOWN_EN |
		SUS_CLK_CONFIG;
	I915_WRITE(BXT_PORT_CL1CM_DW28(phy), val);

	if (phy_info->dual_channel) {
		val = I915_READ(BXT_PORT_CL2CM_DW6(phy));
		val |= DW6_OLDO_DYN_PWR_DOWN_EN;
		I915_WRITE(BXT_PORT_CL2CM_DW6(phy), val);
	}

	if (phy_info->rcomp_phy != -1) {
		u32 grc_code;

		bxt_phy_wait_grc_done(dev_priv, phy_info->rcomp_phy);

		/*
		 * PHY0 isn't connected to an RCOMP resistor so copy over
		 * the corresponding calibrated value from PHY1, and disable
		 * the automatic calibration on PHY0.
		 */
		val = dev_priv->bxt_phy_grc = bxt_get_grc(dev_priv,
							  phy_info->rcomp_phy);
		grc_code = val << GRC_CODE_FAST_SHIFT |
			   val << GRC_CODE_SLOW_SHIFT |
			   val;
		I915_WRITE(BXT_PORT_REF_DW6(phy), grc_code);

		val = I915_READ(BXT_PORT_REF_DW8(phy));
		val |= GRC_DIS | GRC_RDY_OVRD;
		I915_WRITE(BXT_PORT_REF_DW8(phy), val);
	}

	if (phy_info->reset_delay)
		udelay(phy_info->reset_delay);

	val = I915_READ(BXT_PHY_CTL_FAMILY(phy));
	val |= COMMON_RESET_DIS;
	I915_WRITE(BXT_PHY_CTL_FAMILY(phy), val);
}