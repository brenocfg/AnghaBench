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
typedef  int u16 ;
struct TYPE_4__ {scalar_t__ (* write_reg ) (struct igc_hw*,int,int) ;scalar_t__ (* read_reg ) (struct igc_hw*,int,int*) ;} ;
struct igc_phy_info {int autoneg_advertised; int autoneg_mask; scalar_t__ id; TYPE_2__ ops; } ;
struct TYPE_3__ {int current_mode; } ;
struct igc_hw {struct igc_phy_info phy; TYPE_1__ fc; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int ADVERTISE_1000_FULL ; 
 int ADVERTISE_1000_HALF ; 
 int ADVERTISE_100_FULL ; 
 int ADVERTISE_100_HALF ; 
 int ADVERTISE_10_FULL ; 
 int ADVERTISE_10_HALF ; 
 int ADVERTISE_2500_FULL ; 
 int ADVERTISE_2500_HALF ; 
 int ANEG_MULTIGBT_AN_CTRL ; 
 int CR_1000T_FD_CAPS ; 
 int CR_1000T_HD_CAPS ; 
 int CR_2500T_FD_CAPS ; 
 scalar_t__ I225_I_PHY_ID ; 
 scalar_t__ IGC_ERR_CONFIG ; 
 int MMD_DEVADDR_SHIFT ; 
 int NWAY_AR_100TX_FD_CAPS ; 
 int NWAY_AR_100TX_HD_CAPS ; 
 int NWAY_AR_10T_FD_CAPS ; 
 int NWAY_AR_10T_HD_CAPS ; 
 int NWAY_AR_ASM_DIR ; 
 int NWAY_AR_PAUSE ; 
 int PHY_1000T_CTRL ; 
 int PHY_AUTONEG_ADV ; 
 int STANDARD_AN_REG_MASK ; 
 int /*<<< orphan*/  hw_dbg (char*,...) ; 
#define  igc_fc_full 131 
#define  igc_fc_none 130 
#define  igc_fc_rx_pause 129 
#define  igc_fc_tx_pause 128 
 scalar_t__ stub1 (struct igc_hw*,int,int*) ; 
 scalar_t__ stub2 (struct igc_hw*,int,int*) ; 
 scalar_t__ stub3 (struct igc_hw*,int,int*) ; 
 scalar_t__ stub4 (struct igc_hw*,int,int) ; 
 scalar_t__ stub5 (struct igc_hw*,int,int) ; 
 scalar_t__ stub6 (struct igc_hw*,int,int) ; 

__attribute__((used)) static s32 igc_phy_setup_autoneg(struct igc_hw *hw)
{
	struct igc_phy_info *phy = &hw->phy;
	u16 aneg_multigbt_an_ctrl = 0;
	u16 mii_1000t_ctrl_reg = 0;
	u16 mii_autoneg_adv_reg;
	s32 ret_val;

	phy->autoneg_advertised &= phy->autoneg_mask;

	/* Read the MII Auto-Neg Advertisement Register (Address 4). */
	ret_val = phy->ops.read_reg(hw, PHY_AUTONEG_ADV, &mii_autoneg_adv_reg);
	if (ret_val)
		return ret_val;

	if (phy->autoneg_mask & ADVERTISE_1000_FULL) {
		/* Read the MII 1000Base-T Control Register (Address 9). */
		ret_val = phy->ops.read_reg(hw, PHY_1000T_CTRL,
					    &mii_1000t_ctrl_reg);
		if (ret_val)
			return ret_val;
	}

	if ((phy->autoneg_mask & ADVERTISE_2500_FULL) &&
	    hw->phy.id == I225_I_PHY_ID) {
		/* Read the MULTI GBT AN Control Register - reg 7.32 */
		ret_val = phy->ops.read_reg(hw, (STANDARD_AN_REG_MASK <<
					    MMD_DEVADDR_SHIFT) |
					    ANEG_MULTIGBT_AN_CTRL,
					    &aneg_multigbt_an_ctrl);

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
	mii_autoneg_adv_reg &= ~(NWAY_AR_100TX_FD_CAPS |
				 NWAY_AR_100TX_HD_CAPS |
				 NWAY_AR_10T_FD_CAPS   |
				 NWAY_AR_10T_HD_CAPS);
	mii_1000t_ctrl_reg &= ~(CR_1000T_HD_CAPS | CR_1000T_FD_CAPS);

	hw_dbg("autoneg_advertised %x\n", phy->autoneg_advertised);

	/* Do we want to advertise 10 Mb Half Duplex? */
	if (phy->autoneg_advertised & ADVERTISE_10_HALF) {
		hw_dbg("Advertise 10mb Half duplex\n");
		mii_autoneg_adv_reg |= NWAY_AR_10T_HD_CAPS;
	}

	/* Do we want to advertise 10 Mb Full Duplex? */
	if (phy->autoneg_advertised & ADVERTISE_10_FULL) {
		hw_dbg("Advertise 10mb Full duplex\n");
		mii_autoneg_adv_reg |= NWAY_AR_10T_FD_CAPS;
	}

	/* Do we want to advertise 100 Mb Half Duplex? */
	if (phy->autoneg_advertised & ADVERTISE_100_HALF) {
		hw_dbg("Advertise 100mb Half duplex\n");
		mii_autoneg_adv_reg |= NWAY_AR_100TX_HD_CAPS;
	}

	/* Do we want to advertise 100 Mb Full Duplex? */
	if (phy->autoneg_advertised & ADVERTISE_100_FULL) {
		hw_dbg("Advertise 100mb Full duplex\n");
		mii_autoneg_adv_reg |= NWAY_AR_100TX_FD_CAPS;
	}

	/* We do not allow the Phy to advertise 1000 Mb Half Duplex */
	if (phy->autoneg_advertised & ADVERTISE_1000_HALF)
		hw_dbg("Advertise 1000mb Half duplex request denied!\n");

	/* Do we want to advertise 1000 Mb Full Duplex? */
	if (phy->autoneg_advertised & ADVERTISE_1000_FULL) {
		hw_dbg("Advertise 1000mb Full duplex\n");
		mii_1000t_ctrl_reg |= CR_1000T_FD_CAPS;
	}

	/* We do not allow the Phy to advertise 2500 Mb Half Duplex */
	if (phy->autoneg_advertised & ADVERTISE_2500_HALF)
		hw_dbg("Advertise 2500mb Half duplex request denied!\n");

	/* Do we want to advertise 2500 Mb Full Duplex? */
	if (phy->autoneg_advertised & ADVERTISE_2500_FULL) {
		hw_dbg("Advertise 2500mb Full duplex\n");
		aneg_multigbt_an_ctrl |= CR_2500T_FD_CAPS;
	} else {
		aneg_multigbt_an_ctrl &= ~CR_2500T_FD_CAPS;
	}

	/* Check for a software override of the flow control settings, and
	 * setup the PHY advertisement registers accordingly.  If
	 * auto-negotiation is enabled, then software will have to set the
	 * "PAUSE" bits to the correct value in the Auto-Negotiation
	 * Advertisement Register (PHY_AUTONEG_ADV) and re-start auto-
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
	case igc_fc_none:
		/* Flow control (Rx & Tx) is completely disabled by a
		 * software over-ride.
		 */
		mii_autoneg_adv_reg &= ~(NWAY_AR_ASM_DIR | NWAY_AR_PAUSE);
		break;
	case igc_fc_rx_pause:
		/* Rx Flow control is enabled, and Tx Flow control is
		 * disabled, by a software over-ride.
		 *
		 * Since there really isn't a way to advertise that we are
		 * capable of Rx Pause ONLY, we will advertise that we
		 * support both symmetric and asymmetric Rx PAUSE.  Later
		 * (in igc_config_fc_after_link_up) we will disable the
		 * hw's ability to send PAUSE frames.
		 */
		mii_autoneg_adv_reg |= (NWAY_AR_ASM_DIR | NWAY_AR_PAUSE);
		break;
	case igc_fc_tx_pause:
		/* Tx Flow control is enabled, and Rx Flow control is
		 * disabled, by a software over-ride.
		 */
		mii_autoneg_adv_reg |= NWAY_AR_ASM_DIR;
		mii_autoneg_adv_reg &= ~NWAY_AR_PAUSE;
		break;
	case igc_fc_full:
		/* Flow control (both Rx and Tx) is enabled by a software
		 * over-ride.
		 */
		mii_autoneg_adv_reg |= (NWAY_AR_ASM_DIR | NWAY_AR_PAUSE);
		break;
	default:
		hw_dbg("Flow control param set incorrectly\n");
		return -IGC_ERR_CONFIG;
	}

	ret_val = phy->ops.write_reg(hw, PHY_AUTONEG_ADV, mii_autoneg_adv_reg);
	if (ret_val)
		return ret_val;

	hw_dbg("Auto-Neg Advertising %x\n", mii_autoneg_adv_reg);

	if (phy->autoneg_mask & ADVERTISE_1000_FULL)
		ret_val = phy->ops.write_reg(hw, PHY_1000T_CTRL,
					     mii_1000t_ctrl_reg);

	if ((phy->autoneg_mask & ADVERTISE_2500_FULL) &&
	    hw->phy.id == I225_I_PHY_ID)
		ret_val = phy->ops.write_reg(hw,
					     (STANDARD_AN_REG_MASK <<
					     MMD_DEVADDR_SHIFT) |
					     ANEG_MULTIGBT_AN_CTRL,
					     aneg_multigbt_an_ctrl);

	return ret_val;
}