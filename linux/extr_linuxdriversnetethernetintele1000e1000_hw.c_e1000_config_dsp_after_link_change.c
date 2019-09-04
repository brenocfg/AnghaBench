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
typedef  scalar_t__ u16 ;
struct e1000_hw {scalar_t__ phy_type; scalar_t__ dsp_config_state; scalar_t__ ffe_config_state; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ E1000_SUCCESS ; 
 scalar_t__ IGP01E1000_IEEE_FORCE_GIGA ; 
 scalar_t__ IGP01E1000_IEEE_RESTART_AUTONEG ; 
 scalar_t__ IGP01E1000_PHY_CHANNEL_NUM ; 
 int IGP01E1000_PHY_DSP_FFE ; 
 scalar_t__ IGP01E1000_PHY_DSP_FFE_DEFAULT ; 
 scalar_t__ IGP01E1000_PHY_EDAC_MU_INDEX ; 
 scalar_t__ IGP01E1000_PHY_EDAC_SIGN_EXT_9_BITS ; 
 scalar_t__ SPEED_1000 ; 
 int* dsp_reg_array ; 
 scalar_t__ e1000_1000Mb_check_cable_length (struct e1000_hw*) ; 
 scalar_t__ e1000_dsp_config_activated ; 
 scalar_t__ e1000_dsp_config_enabled ; 
 scalar_t__ e1000_ffe_config_active ; 
 scalar_t__ e1000_ffe_config_enabled ; 
 scalar_t__ e1000_get_speed_and_duplex (struct e1000_hw*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ e1000_phy_igp ; 
 scalar_t__ e1000_read_phy_reg (struct e1000_hw*,int,scalar_t__*) ; 
 scalar_t__ e1000_write_phy_reg (struct e1000_hw*,int,scalar_t__) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static s32 e1000_config_dsp_after_link_change(struct e1000_hw *hw, bool link_up)
{
	s32 ret_val;
	u16 phy_data, phy_saved_data, speed, duplex, i;

	if (hw->phy_type != e1000_phy_igp)
		return E1000_SUCCESS;

	if (link_up) {
		ret_val = e1000_get_speed_and_duplex(hw, &speed, &duplex);
		if (ret_val) {
			e_dbg("Error getting link speed and duplex\n");
			return ret_val;
		}

		if (speed == SPEED_1000) {
			ret_val = e1000_1000Mb_check_cable_length(hw);
			if (ret_val)
				return ret_val;
		}
	} else {
		if (hw->dsp_config_state == e1000_dsp_config_activated) {
			/* Save off the current value of register 0x2F5B to be
			 * restored at the end of the routines.
			 */
			ret_val =
			    e1000_read_phy_reg(hw, 0x2F5B, &phy_saved_data);

			if (ret_val)
				return ret_val;

			/* Disable the PHY transmitter */
			ret_val = e1000_write_phy_reg(hw, 0x2F5B, 0x0003);

			if (ret_val)
				return ret_val;

			msleep(20);

			ret_val = e1000_write_phy_reg(hw, 0x0000,
						      IGP01E1000_IEEE_FORCE_GIGA);
			if (ret_val)
				return ret_val;
			for (i = 0; i < IGP01E1000_PHY_CHANNEL_NUM; i++) {
				ret_val =
				    e1000_read_phy_reg(hw, dsp_reg_array[i],
						       &phy_data);
				if (ret_val)
					return ret_val;

				phy_data &= ~IGP01E1000_PHY_EDAC_MU_INDEX;
				phy_data |= IGP01E1000_PHY_EDAC_SIGN_EXT_9_BITS;

				ret_val =
				    e1000_write_phy_reg(hw, dsp_reg_array[i],
							phy_data);
				if (ret_val)
					return ret_val;
			}

			ret_val = e1000_write_phy_reg(hw, 0x0000,
						      IGP01E1000_IEEE_RESTART_AUTONEG);
			if (ret_val)
				return ret_val;

			msleep(20);

			/* Now enable the transmitter */
			ret_val =
			    e1000_write_phy_reg(hw, 0x2F5B, phy_saved_data);

			if (ret_val)
				return ret_val;

			hw->dsp_config_state = e1000_dsp_config_enabled;
		}

		if (hw->ffe_config_state == e1000_ffe_config_active) {
			/* Save off the current value of register 0x2F5B to be
			 * restored at the end of the routines.
			 */
			ret_val =
			    e1000_read_phy_reg(hw, 0x2F5B, &phy_saved_data);

			if (ret_val)
				return ret_val;

			/* Disable the PHY transmitter */
			ret_val = e1000_write_phy_reg(hw, 0x2F5B, 0x0003);

			if (ret_val)
				return ret_val;

			msleep(20);

			ret_val = e1000_write_phy_reg(hw, 0x0000,
						      IGP01E1000_IEEE_FORCE_GIGA);
			if (ret_val)
				return ret_val;
			ret_val =
			    e1000_write_phy_reg(hw, IGP01E1000_PHY_DSP_FFE,
						IGP01E1000_PHY_DSP_FFE_DEFAULT);
			if (ret_val)
				return ret_val;

			ret_val = e1000_write_phy_reg(hw, 0x0000,
						      IGP01E1000_IEEE_RESTART_AUTONEG);
			if (ret_val)
				return ret_val;

			msleep(20);

			/* Now enable the transmitter */
			ret_val =
			    e1000_write_phy_reg(hw, 0x2F5B, phy_saved_data);

			if (ret_val)
				return ret_val;

			hw->ffe_config_state = e1000_ffe_config_enabled;
		}
	}
	return E1000_SUCCESS;
}