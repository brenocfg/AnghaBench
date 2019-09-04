#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct e1000_phy_info {int autoneg_advertised; int autoneg_mask; } ;
struct TYPE_2__ {int current_mode; } ;
struct e1000_hw {TYPE_1__ fc; struct e1000_phy_info phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int ADVERTISE_1000FULL ; 
 int ADVERTISE_1000HALF ; 
 int ADVERTISE_1000_FULL ; 
 int ADVERTISE_1000_HALF ; 
 int ADVERTISE_100FULL ; 
 int ADVERTISE_100HALF ; 
 int ADVERTISE_100_FULL ; 
 int ADVERTISE_100_HALF ; 
 int ADVERTISE_10FULL ; 
 int ADVERTISE_10HALF ; 
 int ADVERTISE_10_FULL ; 
 int ADVERTISE_10_HALF ; 
 int ADVERTISE_PAUSE_ASYM ; 
 int ADVERTISE_PAUSE_CAP ; 
 scalar_t__ E1000_ERR_CONFIG ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_CTRL1000 ; 
#define  e1000_fc_full 131 
#define  e1000_fc_none 130 
#define  e1000_fc_rx_pause 129 
#define  e1000_fc_tx_pause 128 
 scalar_t__ e1e_rphy (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ e1e_wphy (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  e_dbg (char*,...) ; 

__attribute__((used)) static s32 e1000_phy_setup_autoneg(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 mii_autoneg_adv_reg;
	u16 mii_1000t_ctrl_reg = 0;

	phy->autoneg_advertised &= phy->autoneg_mask;

	/* Read the MII Auto-Neg Advertisement Register (Address 4). */
	ret_val = e1e_rphy(hw, MII_ADVERTISE, &mii_autoneg_adv_reg);
	if (ret_val)
		return ret_val;

	if (phy->autoneg_mask & ADVERTISE_1000_FULL) {
		/* Read the MII 1000Base-T Control Register (Address 9). */
		ret_val = e1e_rphy(hw, MII_CTRL1000, &mii_1000t_ctrl_reg);
		if (ret_val)
			return ret_val;
	}

	/* Need to parse both autoneg_advertised and fc and set up
	 * the appropriate PHY registers.  First we will parse for
	 * autoneg_advertised software override.  Since we can advertise
	 * a plethora of combinations, we need to check each bit
	 * individually.
	 */

	/* First we clear all the 10/100 mb speed bits in the Auto-Neg
	 * Advertisement Register (Address 4) and the 1000 mb speed bits in
	 * the  1000Base-T Control Register (Address 9).
	 */
	mii_autoneg_adv_reg &= ~(ADVERTISE_100FULL |
				 ADVERTISE_100HALF |
				 ADVERTISE_10FULL | ADVERTISE_10HALF);
	mii_1000t_ctrl_reg &= ~(ADVERTISE_1000HALF | ADVERTISE_1000FULL);

	e_dbg("autoneg_advertised %x\n", phy->autoneg_advertised);

	/* Do we want to advertise 10 Mb Half Duplex? */
	if (phy->autoneg_advertised & ADVERTISE_10_HALF) {
		e_dbg("Advertise 10mb Half duplex\n");
		mii_autoneg_adv_reg |= ADVERTISE_10HALF;
	}

	/* Do we want to advertise 10 Mb Full Duplex? */
	if (phy->autoneg_advertised & ADVERTISE_10_FULL) {
		e_dbg("Advertise 10mb Full duplex\n");
		mii_autoneg_adv_reg |= ADVERTISE_10FULL;
	}

	/* Do we want to advertise 100 Mb Half Duplex? */
	if (phy->autoneg_advertised & ADVERTISE_100_HALF) {
		e_dbg("Advertise 100mb Half duplex\n");
		mii_autoneg_adv_reg |= ADVERTISE_100HALF;
	}

	/* Do we want to advertise 100 Mb Full Duplex? */
	if (phy->autoneg_advertised & ADVERTISE_100_FULL) {
		e_dbg("Advertise 100mb Full duplex\n");
		mii_autoneg_adv_reg |= ADVERTISE_100FULL;
	}

	/* We do not allow the Phy to advertise 1000 Mb Half Duplex */
	if (phy->autoneg_advertised & ADVERTISE_1000_HALF)
		e_dbg("Advertise 1000mb Half duplex request denied!\n");

	/* Do we want to advertise 1000 Mb Full Duplex? */
	if (phy->autoneg_advertised & ADVERTISE_1000_FULL) {
		e_dbg("Advertise 1000mb Full duplex\n");
		mii_1000t_ctrl_reg |= ADVERTISE_1000FULL;
	}

	/* Check for a software override of the flow control settings, and
	 * setup the PHY advertisement registers accordingly.  If
	 * auto-negotiation is enabled, then software will have to set the
	 * "PAUSE" bits to the correct value in the Auto-Negotiation
	 * Advertisement Register (MII_ADVERTISE) and re-start auto-
	 * negotiation.
	 *
	 * The possible values of the "fc" parameter are:
	 *      0:  Flow control is completely disabled
	 *      1:  Rx flow control is enabled (we can receive pause frames
	 *          but not send pause frames).
	 *      2:  Tx flow control is enabled (we can send pause frames
	 *          but we do not support receiving pause frames).
	 *      3:  Both Rx and Tx flow control (symmetric) are enabled.
	 *  other:  No software override.  The flow control configuration
	 *          in the EEPROM is used.
	 */
	switch (hw->fc.current_mode) {
	case e1000_fc_none:
		/* Flow control (Rx & Tx) is completely disabled by a
		 * software over-ride.
		 */
		mii_autoneg_adv_reg &=
		    ~(ADVERTISE_PAUSE_ASYM | ADVERTISE_PAUSE_CAP);
		break;
	case e1000_fc_rx_pause:
		/* Rx Flow control is enabled, and Tx Flow control is
		 * disabled, by a software over-ride.
		 *
		 * Since there really isn't a way to advertise that we are
		 * capable of Rx Pause ONLY, we will advertise that we
		 * support both symmetric and asymmetric Rx PAUSE.  Later
		 * (in e1000e_config_fc_after_link_up) we will disable the
		 * hw's ability to send PAUSE frames.
		 */
		mii_autoneg_adv_reg |=
		    (ADVERTISE_PAUSE_ASYM | ADVERTISE_PAUSE_CAP);
		break;
	case e1000_fc_tx_pause:
		/* Tx Flow control is enabled, and Rx Flow control is
		 * disabled, by a software over-ride.
		 */
		mii_autoneg_adv_reg |= ADVERTISE_PAUSE_ASYM;
		mii_autoneg_adv_reg &= ~ADVERTISE_PAUSE_CAP;
		break;
	case e1000_fc_full:
		/* Flow control (both Rx and Tx) is enabled by a software
		 * over-ride.
		 */
		mii_autoneg_adv_reg |=
		    (ADVERTISE_PAUSE_ASYM | ADVERTISE_PAUSE_CAP);
		break;
	default:
		e_dbg("Flow control param set incorrectly\n");
		return -E1000_ERR_CONFIG;
	}

	ret_val = e1e_wphy(hw, MII_ADVERTISE, mii_autoneg_adv_reg);
	if (ret_val)
		return ret_val;

	e_dbg("Auto-Neg Advertising %x\n", mii_autoneg_adv_reg);

	if (phy->autoneg_mask & ADVERTISE_1000_FULL)
		ret_val = e1e_wphy(hw, MII_CTRL1000, mii_1000t_ctrl_reg);

	return ret_val;
}