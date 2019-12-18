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
typedef  int u16 ;
struct e1000_hw {scalar_t__ phy_type; scalar_t__ mac_type; scalar_t__ dsp_config_state; int mdix; int master_slave; scalar_t__ ffe_config_state; scalar_t__ autoneg_advertised; int original_master_slave; scalar_t__ autoneg; scalar_t__ phy_reset_disable; } ;
typedef  scalar_t__ s32 ;
typedef  int e1000_ms_type ;

/* Variables and functions */
 scalar_t__ ADVERTISE_1000_FULL ; 
 int CR_1000T_MS_ENABLE ; 
 int CR_1000T_MS_VALUE ; 
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  IGP01E1000_PHY_PORT_CONFIG ; 
 int /*<<< orphan*/  IGP01E1000_PHY_PORT_CTRL ; 
 int IGP01E1000_PSCFR_SMART_SPEED ; 
 int IGP01E1000_PSCR_AUTO_MDIX ; 
 int IGP01E1000_PSCR_FORCE_MDI_MDIX ; 
 int IGP_ACTIVITY_LED_ENABLE ; 
 int IGP_ACTIVITY_LED_MASK ; 
 int IGP_LED3_MODE ; 
 int /*<<< orphan*/  LEDCTL ; 
 int /*<<< orphan*/  PHY_1000T_CTRL ; 
 scalar_t__ e1000_82541 ; 
 scalar_t__ e1000_82547 ; 
 scalar_t__ e1000_dsp_config_activated ; 
 scalar_t__ e1000_dsp_config_disabled ; 
 void* e1000_dsp_config_enabled ; 
 scalar_t__ e1000_ffe_config_active ; 
 scalar_t__ e1000_ffe_config_enabled ; 
#define  e1000_ms_auto 130 
#define  e1000_ms_force_master 129 
#define  e1000_ms_force_slave 128 
 scalar_t__ e1000_phy_igp ; 
 scalar_t__ e1000_phy_reset (struct e1000_hw*) ; 
 scalar_t__ e1000_read_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ e1000_set_d3_lplu_state (struct e1000_hw*,int) ; 
 scalar_t__ e1000_write_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static s32 e1000_copper_link_igp_setup(struct e1000_hw *hw)
{
	u32 led_ctrl;
	s32 ret_val;
	u16 phy_data;

	if (hw->phy_reset_disable)
		return E1000_SUCCESS;

	ret_val = e1000_phy_reset(hw);
	if (ret_val) {
		e_dbg("Error Resetting the PHY\n");
		return ret_val;
	}

	/* Wait 15ms for MAC to configure PHY from eeprom settings */
	msleep(15);
	/* Configure activity LED after PHY reset */
	led_ctrl = er32(LEDCTL);
	led_ctrl &= IGP_ACTIVITY_LED_MASK;
	led_ctrl |= (IGP_ACTIVITY_LED_ENABLE | IGP_LED3_MODE);
	ew32(LEDCTL, led_ctrl);

	/* The NVM settings will configure LPLU in D3 for IGP2 and IGP3 PHYs */
	if (hw->phy_type == e1000_phy_igp) {
		/* disable lplu d3 during driver init */
		ret_val = e1000_set_d3_lplu_state(hw, false);
		if (ret_val) {
			e_dbg("Error Disabling LPLU D3\n");
			return ret_val;
		}
	}

	/* Configure mdi-mdix settings */
	ret_val = e1000_read_phy_reg(hw, IGP01E1000_PHY_PORT_CTRL, &phy_data);
	if (ret_val)
		return ret_val;

	if ((hw->mac_type == e1000_82541) || (hw->mac_type == e1000_82547)) {
		hw->dsp_config_state = e1000_dsp_config_disabled;
		/* Force MDI for earlier revs of the IGP PHY */
		phy_data &=
		    ~(IGP01E1000_PSCR_AUTO_MDIX |
		      IGP01E1000_PSCR_FORCE_MDI_MDIX);
		hw->mdix = 1;

	} else {
		hw->dsp_config_state = e1000_dsp_config_enabled;
		phy_data &= ~IGP01E1000_PSCR_AUTO_MDIX;

		switch (hw->mdix) {
		case 1:
			phy_data &= ~IGP01E1000_PSCR_FORCE_MDI_MDIX;
			break;
		case 2:
			phy_data |= IGP01E1000_PSCR_FORCE_MDI_MDIX;
			break;
		case 0:
		default:
			phy_data |= IGP01E1000_PSCR_AUTO_MDIX;
			break;
		}
	}
	ret_val = e1000_write_phy_reg(hw, IGP01E1000_PHY_PORT_CTRL, phy_data);
	if (ret_val)
		return ret_val;

	/* set auto-master slave resolution settings */
	if (hw->autoneg) {
		e1000_ms_type phy_ms_setting = hw->master_slave;

		if (hw->ffe_config_state == e1000_ffe_config_active)
			hw->ffe_config_state = e1000_ffe_config_enabled;

		if (hw->dsp_config_state == e1000_dsp_config_activated)
			hw->dsp_config_state = e1000_dsp_config_enabled;

		/* when autonegotiation advertisement is only 1000Mbps then we
		 * should disable SmartSpeed and enable Auto MasterSlave
		 * resolution as hardware default.
		 */
		if (hw->autoneg_advertised == ADVERTISE_1000_FULL) {
			/* Disable SmartSpeed */
			ret_val =
			    e1000_read_phy_reg(hw, IGP01E1000_PHY_PORT_CONFIG,
					       &phy_data);
			if (ret_val)
				return ret_val;
			phy_data &= ~IGP01E1000_PSCFR_SMART_SPEED;
			ret_val =
			    e1000_write_phy_reg(hw, IGP01E1000_PHY_PORT_CONFIG,
						phy_data);
			if (ret_val)
				return ret_val;
			/* Set auto Master/Slave resolution process */
			ret_val =
			    e1000_read_phy_reg(hw, PHY_1000T_CTRL, &phy_data);
			if (ret_val)
				return ret_val;
			phy_data &= ~CR_1000T_MS_ENABLE;
			ret_val =
			    e1000_write_phy_reg(hw, PHY_1000T_CTRL, phy_data);
			if (ret_val)
				return ret_val;
		}

		ret_val = e1000_read_phy_reg(hw, PHY_1000T_CTRL, &phy_data);
		if (ret_val)
			return ret_val;

		/* load defaults for future use */
		hw->original_master_slave = (phy_data & CR_1000T_MS_ENABLE) ?
		    ((phy_data & CR_1000T_MS_VALUE) ?
		     e1000_ms_force_master :
		     e1000_ms_force_slave) : e1000_ms_auto;

		switch (phy_ms_setting) {
		case e1000_ms_force_master:
			phy_data |= (CR_1000T_MS_ENABLE | CR_1000T_MS_VALUE);
			break;
		case e1000_ms_force_slave:
			phy_data |= CR_1000T_MS_ENABLE;
			phy_data &= ~(CR_1000T_MS_VALUE);
			break;
		case e1000_ms_auto:
			phy_data &= ~CR_1000T_MS_ENABLE;
		default:
			break;
		}
		ret_val = e1000_write_phy_reg(hw, PHY_1000T_CTRL, phy_data);
		if (ret_val)
			return ret_val;
	}

	return E1000_SUCCESS;
}