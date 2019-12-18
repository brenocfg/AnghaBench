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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct e1000_hw {scalar_t__ dsp_config_state; int /*<<< orphan*/  ffe_config_state; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ FFE_IDLE_ERR_COUNT_TIMEOUT_100 ; 
 scalar_t__ FFE_IDLE_ERR_COUNT_TIMEOUT_20 ; 
 scalar_t__ IGP01E1000_PHY_CHANNEL_NUM ; 
 int /*<<< orphan*/  IGP01E1000_PHY_DSP_FFE ; 
 scalar_t__ IGP01E1000_PHY_DSP_FFE_CM_CP ; 
 scalar_t__ IGP01E1000_PHY_EDAC_MU_INDEX ; 
 int /*<<< orphan*/  PHY_1000T_STATUS ; 
 scalar_t__ SR_1000T_IDLE_ERROR_CNT ; 
 scalar_t__ SR_1000T_PHY_EXCESSIVE_IDLE_ERR_COUNT ; 
 int /*<<< orphan*/ * dsp_reg_array ; 
 scalar_t__ e1000_dsp_config_activated ; 
 scalar_t__ e1000_dsp_config_enabled ; 
 int /*<<< orphan*/  e1000_ffe_config_active ; 
 scalar_t__ e1000_get_cable_length (struct e1000_hw*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ e1000_igp_cable_length_50 ; 
 scalar_t__ e1000_read_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ e1000_write_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static s32 e1000_1000Mb_check_cable_length(struct e1000_hw *hw)
{
	u16 min_length, max_length;
	u16 phy_data, i;
	s32 ret_val;

	ret_val = e1000_get_cable_length(hw, &min_length, &max_length);
	if (ret_val)
		return ret_val;

	if (hw->dsp_config_state != e1000_dsp_config_enabled)
		return 0;

	if (min_length >= e1000_igp_cable_length_50) {
		for (i = 0; i < IGP01E1000_PHY_CHANNEL_NUM; i++) {
			ret_val = e1000_read_phy_reg(hw, dsp_reg_array[i],
						     &phy_data);
			if (ret_val)
				return ret_val;

			phy_data &= ~IGP01E1000_PHY_EDAC_MU_INDEX;

			ret_val = e1000_write_phy_reg(hw, dsp_reg_array[i],
						      phy_data);
			if (ret_val)
				return ret_val;
		}
		hw->dsp_config_state = e1000_dsp_config_activated;
	} else {
		u16 ffe_idle_err_timeout = FFE_IDLE_ERR_COUNT_TIMEOUT_20;
		u32 idle_errs = 0;

		/* clear previous idle error counts */
		ret_val = e1000_read_phy_reg(hw, PHY_1000T_STATUS, &phy_data);
		if (ret_val)
			return ret_val;

		for (i = 0; i < ffe_idle_err_timeout; i++) {
			udelay(1000);
			ret_val = e1000_read_phy_reg(hw, PHY_1000T_STATUS,
						     &phy_data);
			if (ret_val)
				return ret_val;

			idle_errs += (phy_data & SR_1000T_IDLE_ERROR_CNT);
			if (idle_errs > SR_1000T_PHY_EXCESSIVE_IDLE_ERR_COUNT) {
				hw->ffe_config_state = e1000_ffe_config_active;

				ret_val = e1000_write_phy_reg(hw,
							      IGP01E1000_PHY_DSP_FFE,
							      IGP01E1000_PHY_DSP_FFE_CM_CP);
				if (ret_val)
					return ret_val;
				break;
			}

			if (idle_errs)
				ffe_idle_err_timeout =
					    FFE_IDLE_ERR_COUNT_TIMEOUT_100;
		}
	}

	return 0;
}