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
struct i915_power_well {TYPE_2__* desc; } ;
struct drm_i915_private {int chv_phy_control; int* chv_phy_assert; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {scalar_t__ (* is_enabled ) (struct drm_i915_private*,struct i915_power_well*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CHV_DISP_PW_DPIO_CMN_D ; 
 int /*<<< orphan*/  DISPLAY_PHY_CONTROL ; 
 int /*<<< orphan*/  DPIO_CH0 ; 
 int /*<<< orphan*/  DPIO_CH1 ; 
 size_t DPIO_PHY0 ; 
 size_t DPIO_PHY1 ; 
 int /*<<< orphan*/  DPIO_PHY_STATUS ; 
 int /*<<< orphan*/  DPLL (int /*<<< orphan*/ ) ; 
 int DPLL_PORTB_READY_MASK ; 
 int DPLL_PORTC_READY_MASK ; 
 int DPLL_PORTD_READY_MASK ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PHY_CH_DEEP_PSR ; 
 int PHY_CH_POWER_DOWN_OVRD (unsigned int,size_t,int /*<<< orphan*/ ) ; 
 int PHY_CH_POWER_DOWN_OVRD_EN (size_t,int /*<<< orphan*/ ) ; 
 int PHY_CH_POWER_MODE (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int PHY_COM_LANE_RESET_DEASSERT (size_t) ; 
 int /*<<< orphan*/  PHY_LDO_DELAY_600NS ; 
 int PHY_LDO_SEQ_DELAY (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  PIPE_A ; 
 int /*<<< orphan*/  VLV_DISP_PW_DPIO_CMN_BC ; 
 struct i915_power_well* lookup_power_well (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct drm_i915_private*,struct i915_power_well*) ; 
 scalar_t__ stub2 (struct drm_i915_private*,struct i915_power_well*) ; 

__attribute__((used)) static void chv_phy_control_init(struct drm_i915_private *dev_priv)
{
	struct i915_power_well *cmn_bc =
		lookup_power_well(dev_priv, VLV_DISP_PW_DPIO_CMN_BC);
	struct i915_power_well *cmn_d =
		lookup_power_well(dev_priv, CHV_DISP_PW_DPIO_CMN_D);

	/*
	 * DISPLAY_PHY_CONTROL can get corrupted if read. As a
	 * workaround never ever read DISPLAY_PHY_CONTROL, and
	 * instead maintain a shadow copy ourselves. Use the actual
	 * power well state and lane status to reconstruct the
	 * expected initial value.
	 */
	dev_priv->chv_phy_control =
		PHY_LDO_SEQ_DELAY(PHY_LDO_DELAY_600NS, DPIO_PHY0) |
		PHY_LDO_SEQ_DELAY(PHY_LDO_DELAY_600NS, DPIO_PHY1) |
		PHY_CH_POWER_MODE(PHY_CH_DEEP_PSR, DPIO_PHY0, DPIO_CH0) |
		PHY_CH_POWER_MODE(PHY_CH_DEEP_PSR, DPIO_PHY0, DPIO_CH1) |
		PHY_CH_POWER_MODE(PHY_CH_DEEP_PSR, DPIO_PHY1, DPIO_CH0);

	/*
	 * If all lanes are disabled we leave the override disabled
	 * with all power down bits cleared to match the state we
	 * would use after disabling the port. Otherwise enable the
	 * override and set the lane powerdown bits accding to the
	 * current lane status.
	 */
	if (cmn_bc->desc->ops->is_enabled(dev_priv, cmn_bc)) {
		u32 status = I915_READ(DPLL(PIPE_A));
		unsigned int mask;

		mask = status & DPLL_PORTB_READY_MASK;
		if (mask == 0xf)
			mask = 0x0;
		else
			dev_priv->chv_phy_control |=
				PHY_CH_POWER_DOWN_OVRD_EN(DPIO_PHY0, DPIO_CH0);

		dev_priv->chv_phy_control |=
			PHY_CH_POWER_DOWN_OVRD(mask, DPIO_PHY0, DPIO_CH0);

		mask = (status & DPLL_PORTC_READY_MASK) >> 4;
		if (mask == 0xf)
			mask = 0x0;
		else
			dev_priv->chv_phy_control |=
				PHY_CH_POWER_DOWN_OVRD_EN(DPIO_PHY0, DPIO_CH1);

		dev_priv->chv_phy_control |=
			PHY_CH_POWER_DOWN_OVRD(mask, DPIO_PHY0, DPIO_CH1);

		dev_priv->chv_phy_control |= PHY_COM_LANE_RESET_DEASSERT(DPIO_PHY0);

		dev_priv->chv_phy_assert[DPIO_PHY0] = false;
	} else {
		dev_priv->chv_phy_assert[DPIO_PHY0] = true;
	}

	if (cmn_d->desc->ops->is_enabled(dev_priv, cmn_d)) {
		u32 status = I915_READ(DPIO_PHY_STATUS);
		unsigned int mask;

		mask = status & DPLL_PORTD_READY_MASK;

		if (mask == 0xf)
			mask = 0x0;
		else
			dev_priv->chv_phy_control |=
				PHY_CH_POWER_DOWN_OVRD_EN(DPIO_PHY1, DPIO_CH0);

		dev_priv->chv_phy_control |=
			PHY_CH_POWER_DOWN_OVRD(mask, DPIO_PHY1, DPIO_CH0);

		dev_priv->chv_phy_control |= PHY_COM_LANE_RESET_DEASSERT(DPIO_PHY1);

		dev_priv->chv_phy_assert[DPIO_PHY1] = false;
	} else {
		dev_priv->chv_phy_assert[DPIO_PHY1] = true;
	}

	I915_WRITE(DISPLAY_PHY_CONTROL, dev_priv->chv_phy_control);

	DRM_DEBUG_KMS("Initial PHY_CONTROL=0x%08x\n",
		      dev_priv->chv_phy_control);
}