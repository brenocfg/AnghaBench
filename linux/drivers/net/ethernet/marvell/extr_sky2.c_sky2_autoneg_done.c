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
typedef  int u16 ;
struct sky2_port {unsigned int port; scalar_t__ duplex; int flow_status; int /*<<< orphan*/  speed; int /*<<< orphan*/  netdev; struct sky2_hw* hw; } ;
struct sky2_hw {int flags; scalar_t__ chip_id; } ;

/* Variables and functions */
 int ADVERTISE_1000XPAUSE ; 
 int ADVERTISE_1000XPSE_ASYM ; 
 int ADVERTISE_PAUSE_ASYM ; 
 int ADVERTISE_PAUSE_CAP ; 
 scalar_t__ CHIP_ID_YUKON_EC_U ; 
 scalar_t__ CHIP_ID_YUKON_EX ; 
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ DUPLEX_HALF ; 
 int FC_BOTH ; 
 void* FC_NONE ; 
 int FC_RX ; 
 int FC_TX ; 
 int /*<<< orphan*/  GMAC_CTRL ; 
 int /*<<< orphan*/  GMC_PAUSE_OFF ; 
 int /*<<< orphan*/  GMC_PAUSE_ON ; 
 int LPA_1000XPAUSE ; 
 int LPA_1000XPAUSE_ASYM ; 
 int LPA_PAUSE_ASYM ; 
 int LPA_PAUSE_CAP ; 
 int /*<<< orphan*/  PHY_MARV_AUNE_ADV ; 
 int /*<<< orphan*/  PHY_MARV_AUNE_LP ; 
 int PHY_M_AN_RF ; 
 int PHY_M_PS_FULL_DUP ; 
 int PHY_M_PS_SPDUP_RES ; 
 int SKY2_HW_FIBRE_PHY ; 
 int /*<<< orphan*/  SK_REG (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int gm_phy_read (struct sky2_hw*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sky2_phy_speed (struct sky2_hw*,int) ; 
 int /*<<< orphan*/  sky2_write8 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sky2_autoneg_done(struct sky2_port *sky2, u16 aux)
{
	struct sky2_hw *hw = sky2->hw;
	unsigned port = sky2->port;
	u16 advert, lpa;

	advert = gm_phy_read(hw, port, PHY_MARV_AUNE_ADV);
	lpa = gm_phy_read(hw, port, PHY_MARV_AUNE_LP);
	if (lpa & PHY_M_AN_RF) {
		netdev_err(sky2->netdev, "remote fault\n");
		return -1;
	}

	if (!(aux & PHY_M_PS_SPDUP_RES)) {
		netdev_err(sky2->netdev, "speed/duplex mismatch\n");
		return -1;
	}

	sky2->speed = sky2_phy_speed(hw, aux);
	sky2->duplex = (aux & PHY_M_PS_FULL_DUP) ? DUPLEX_FULL : DUPLEX_HALF;

	/* Since the pause result bits seem to in different positions on
	 * different chips. look at registers.
	 */
	if (hw->flags & SKY2_HW_FIBRE_PHY) {
		/* Shift for bits in fiber PHY */
		advert &= ~(ADVERTISE_PAUSE_CAP|ADVERTISE_PAUSE_ASYM);
		lpa &= ~(LPA_PAUSE_CAP|LPA_PAUSE_ASYM);

		if (advert & ADVERTISE_1000XPAUSE)
			advert |= ADVERTISE_PAUSE_CAP;
		if (advert & ADVERTISE_1000XPSE_ASYM)
			advert |= ADVERTISE_PAUSE_ASYM;
		if (lpa & LPA_1000XPAUSE)
			lpa |= LPA_PAUSE_CAP;
		if (lpa & LPA_1000XPAUSE_ASYM)
			lpa |= LPA_PAUSE_ASYM;
	}

	sky2->flow_status = FC_NONE;
	if (advert & ADVERTISE_PAUSE_CAP) {
		if (lpa & LPA_PAUSE_CAP)
			sky2->flow_status = FC_BOTH;
		else if (advert & ADVERTISE_PAUSE_ASYM)
			sky2->flow_status = FC_RX;
	} else if (advert & ADVERTISE_PAUSE_ASYM) {
		if ((lpa & LPA_PAUSE_CAP) && (lpa & LPA_PAUSE_ASYM))
			sky2->flow_status = FC_TX;
	}

	if (sky2->duplex == DUPLEX_HALF && sky2->speed < SPEED_1000 &&
	    !(hw->chip_id == CHIP_ID_YUKON_EC_U || hw->chip_id == CHIP_ID_YUKON_EX))
		sky2->flow_status = FC_NONE;

	if (sky2->flow_status & FC_TX)
		sky2_write8(hw, SK_REG(port, GMAC_CTRL), GMC_PAUSE_ON);
	else
		sky2_write8(hw, SK_REG(port, GMAC_CTRL), GMC_PAUSE_OFF);

	return 0;
}