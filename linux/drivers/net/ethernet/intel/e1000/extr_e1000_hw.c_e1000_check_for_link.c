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
struct e1000_hw {scalar_t__ media_type; scalar_t__ mac_type; int get_link_status; scalar_t__ forced_speed_duplex; int tbi_compatibility_on; scalar_t__ tbi_compatibility_en; int /*<<< orphan*/  autoneg; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int E1000_CTRL_SWDPIN1 ; 
 scalar_t__ E1000_ERR_CONFIG ; 
 int E1000_ICS_LSC ; 
 int E1000_RCTL_SBP ; 
 int E1000_STATUS_LU ; 
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  ICR ; 
 int /*<<< orphan*/  ICS ; 
 int /*<<< orphan*/  IMC ; 
 int /*<<< orphan*/  IMS ; 
 int IMS_ENABLE_MASK ; 
 int MII_SR_LINK_STATUS ; 
 int /*<<< orphan*/  PHY_STATUS ; 
 int /*<<< orphan*/  RCTL ; 
 int /*<<< orphan*/  RXCW ; 
 int SPEED_1000 ; 
 int /*<<< orphan*/  STATUS ; 
 scalar_t__ e1000_10_full ; 
 scalar_t__ e1000_10_half ; 
 scalar_t__ e1000_82543 ; 
 scalar_t__ e1000_82544 ; 
 scalar_t__ e1000_ce4100 ; 
 int /*<<< orphan*/  e1000_check_downshift (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_check_for_serdes_link_generic (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_config_collision_dist (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_config_dsp_after_link_change (struct e1000_hw*,int) ; 
 scalar_t__ e1000_config_fc_after_link_up (struct e1000_hw*) ; 
 scalar_t__ e1000_config_mac_to_phy (struct e1000_hw*) ; 
 scalar_t__ e1000_get_speed_and_duplex (struct e1000_hw*,int*,int*) ; 
 scalar_t__ e1000_media_type_copper ; 
 scalar_t__ e1000_media_type_fiber ; 
 scalar_t__ e1000_media_type_internal_serdes ; 
 scalar_t__ e1000_polarity_reversal_workaround (struct e1000_hw*) ; 
 scalar_t__ e1000_read_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 

s32 e1000_check_for_link(struct e1000_hw *hw)
{
	u32 rxcw = 0;
	u32 ctrl;
	u32 status;
	u32 rctl;
	u32 icr;
	u32 signal = 0;
	s32 ret_val;
	u16 phy_data;

	ctrl = er32(CTRL);
	status = er32(STATUS);

	/* On adapters with a MAC newer than 82544, SW Definable pin 1 will be
	 * set when the optics detect a signal. On older adapters, it will be
	 * cleared when there is a signal.  This applies to fiber media only.
	 */
	if ((hw->media_type == e1000_media_type_fiber) ||
	    (hw->media_type == e1000_media_type_internal_serdes)) {
		rxcw = er32(RXCW);

		if (hw->media_type == e1000_media_type_fiber) {
			signal =
			    (hw->mac_type >
			     e1000_82544) ? E1000_CTRL_SWDPIN1 : 0;
			if (status & E1000_STATUS_LU)
				hw->get_link_status = false;
		}
	}

	/* If we have a copper PHY then we only want to go out to the PHY
	 * registers to see if Auto-Neg has completed and/or if our link
	 * status has changed.  The get_link_status flag will be set if we
	 * receive a Link Status Change interrupt or we have Rx Sequence
	 * Errors.
	 */
	if ((hw->media_type == e1000_media_type_copper) && hw->get_link_status) {
		/* First we want to see if the MII Status Register reports
		 * link.  If so, then we want to get the current speed/duplex
		 * of the PHY.
		 * Read the register twice since the link bit is sticky.
		 */
		ret_val = e1000_read_phy_reg(hw, PHY_STATUS, &phy_data);
		if (ret_val)
			return ret_val;
		ret_val = e1000_read_phy_reg(hw, PHY_STATUS, &phy_data);
		if (ret_val)
			return ret_val;

		if (phy_data & MII_SR_LINK_STATUS) {
			hw->get_link_status = false;
			/* Check if there was DownShift, must be checked
			 * immediately after link-up
			 */
			e1000_check_downshift(hw);

			/* If we are on 82544 or 82543 silicon and speed/duplex
			 * are forced to 10H or 10F, then we will implement the
			 * polarity reversal workaround.  We disable interrupts
			 * first, and upon returning, place the devices
			 * interrupt state to its previous value except for the
			 * link status change interrupt which will
			 * happen due to the execution of this workaround.
			 */

			if ((hw->mac_type == e1000_82544 ||
			     hw->mac_type == e1000_82543) &&
			    (!hw->autoneg) &&
			    (hw->forced_speed_duplex == e1000_10_full ||
			     hw->forced_speed_duplex == e1000_10_half)) {
				ew32(IMC, 0xffffffff);
				ret_val =
				    e1000_polarity_reversal_workaround(hw);
				icr = er32(ICR);
				ew32(ICS, (icr & ~E1000_ICS_LSC));
				ew32(IMS, IMS_ENABLE_MASK);
			}

		} else {
			/* No link detected */
			e1000_config_dsp_after_link_change(hw, false);
			return 0;
		}

		/* If we are forcing speed/duplex, then we simply return since
		 * we have already determined whether we have link or not.
		 */
		if (!hw->autoneg)
			return -E1000_ERR_CONFIG;

		/* optimize the dsp settings for the igp phy */
		e1000_config_dsp_after_link_change(hw, true);

		/* We have a M88E1000 PHY and Auto-Neg is enabled.  If we
		 * have Si on board that is 82544 or newer, Auto
		 * Speed Detection takes care of MAC speed/duplex
		 * configuration.  So we only need to configure Collision
		 * Distance in the MAC.  Otherwise, we need to force
		 * speed/duplex on the MAC to the current PHY speed/duplex
		 * settings.
		 */
		if ((hw->mac_type >= e1000_82544) &&
		    (hw->mac_type != e1000_ce4100))
			e1000_config_collision_dist(hw);
		else {
			ret_val = e1000_config_mac_to_phy(hw);
			if (ret_val) {
				e_dbg
				    ("Error configuring MAC to PHY settings\n");
				return ret_val;
			}
		}

		/* Configure Flow Control now that Auto-Neg has completed.
		 * First, we need to restore the desired flow control settings
		 * because we may have had to re-autoneg with a different link
		 * partner.
		 */
		ret_val = e1000_config_fc_after_link_up(hw);
		if (ret_val) {
			e_dbg("Error configuring flow control\n");
			return ret_val;
		}

		/* At this point we know that we are on copper and we have
		 * auto-negotiated link.  These are conditions for checking the
		 * link partner capability register.  We use the link speed to
		 * determine if TBI compatibility needs to be turned on or off.
		 * If the link is not at gigabit speed, then TBI compatibility
		 * is not needed.  If we are at gigabit speed, we turn on TBI
		 * compatibility.
		 */
		if (hw->tbi_compatibility_en) {
			u16 speed, duplex;

			ret_val =
			    e1000_get_speed_and_duplex(hw, &speed, &duplex);

			if (ret_val) {
				e_dbg
				    ("Error getting link speed and duplex\n");
				return ret_val;
			}
			if (speed != SPEED_1000) {
				/* If link speed is not set to gigabit speed, we
				 * do not need to enable TBI compatibility.
				 */
				if (hw->tbi_compatibility_on) {
					/* If we previously were in the mode,
					 * turn it off.
					 */
					rctl = er32(RCTL);
					rctl &= ~E1000_RCTL_SBP;
					ew32(RCTL, rctl);
					hw->tbi_compatibility_on = false;
				}
			} else {
				/* If TBI compatibility is was previously off,
				 * turn it on. For compatibility with a TBI link
				 * partner, we will store bad packets. Some
				 * frames have an additional byte on the end and
				 * will look like CRC errors to to the hardware.
				 */
				if (!hw->tbi_compatibility_on) {
					hw->tbi_compatibility_on = true;
					rctl = er32(RCTL);
					rctl |= E1000_RCTL_SBP;
					ew32(RCTL, rctl);
				}
			}
		}
	}

	if ((hw->media_type == e1000_media_type_fiber) ||
	    (hw->media_type == e1000_media_type_internal_serdes))
		e1000_check_for_serdes_link_generic(hw);

	return E1000_SUCCESS;
}