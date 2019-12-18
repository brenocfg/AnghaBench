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
typedef  int u8 ;
typedef  int u16 ;
struct link_vars {scalar_t__ line_speed; int fault_detected; int duplex; } ;
struct link_params {int port; struct bnx2x* bp; } ;
struct bnx2x_phy {int flags; scalar_t__ req_line_speed; } ;
struct bnx2x {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BP_PATH (struct bnx2x*) ; 
 int /*<<< orphan*/  CHIP_IS_E1x (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ DUAL_MEDIA (struct link_params*) ; 
 int DUPLEX_FULL ; 
 int FLAGS_NOC ; 
 int FLAGS_SFP_NOT_APPROVED ; 
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_CTRL ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_RXCTRL ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_RXSTAT ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_STAT ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_TXCTRL ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_TXSTAT ; 
 int /*<<< orphan*/  MDIO_PMA_REG_8073_SPEED_LINK_STATUS ; 
 int /*<<< orphan*/  MDIO_PMA_REG_8727_GPIO_CTRL ; 
 int /*<<< orphan*/  MDIO_PMA_REG_8727_PCS_GP ; 
 int /*<<< orphan*/  MDIO_PMA_REG_M8051_MSGOUT_REG ; 
 int /*<<< orphan*/  MDIO_PMA_REG_PHY_IDENTIFIER ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 scalar_t__ SPEED_1000 ; 
 scalar_t__ SPEED_10000 ; 
 int /*<<< orphan*/  bnx2x_8727_handle_mod_abs (struct bnx2x_phy*,struct link_params*) ; 
 int /*<<< orphan*/  bnx2x_8727_power_module (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_cl45_read (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  bnx2x_cl45_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_ext_phy_resolve_fc (struct bnx2x_phy*,struct link_params*,struct link_vars*) ; 
 int /*<<< orphan*/  bnx2x_sfp_mask_fault (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_sfp_set_transmitter (struct link_params*,struct bnx2x_phy*,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static u8 bnx2x_8727_read_status(struct bnx2x_phy *phy,
				 struct link_params *params,
				 struct link_vars *vars)

{
	struct bnx2x *bp = params->bp;
	u8 link_up = 0, oc_port = params->port;
	u16 link_status = 0;
	u16 rx_alarm_status, lasi_ctrl, val1;

	/* If PHY is not initialized, do not check link status */
	bnx2x_cl45_read(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_LASI_CTRL,
			&lasi_ctrl);
	if (!lasi_ctrl)
		return 0;

	/* Check the LASI on Rx */
	bnx2x_cl45_read(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_LASI_RXSTAT,
			&rx_alarm_status);
	vars->line_speed = 0;
	DP(NETIF_MSG_LINK, "8727 RX_ALARM_STATUS  0x%x\n", rx_alarm_status);

	bnx2x_sfp_mask_fault(bp, phy, MDIO_PMA_LASI_TXSTAT,
			     MDIO_PMA_LASI_TXCTRL);

	bnx2x_cl45_read(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_LASI_STAT, &val1);

	DP(NETIF_MSG_LINK, "8727 LASI status 0x%x\n", val1);

	/* Clear MSG-OUT */
	bnx2x_cl45_read(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_M8051_MSGOUT_REG, &val1);

	/* If a module is present and there is need to check
	 * for over current
	 */
	if (!(phy->flags & FLAGS_NOC) && !(rx_alarm_status & (1<<5))) {
		/* Check over-current using 8727 GPIO0 input*/
		bnx2x_cl45_read(bp, phy,
				MDIO_PMA_DEVAD, MDIO_PMA_REG_8727_GPIO_CTRL,
				&val1);

		if ((val1 & (1<<8)) == 0) {
			if (!CHIP_IS_E1x(bp))
				oc_port = BP_PATH(bp) + (params->port << 1);
			DP(NETIF_MSG_LINK,
			   "8727 Power fault has been detected on port %d\n",
			   oc_port);
			netdev_err(bp->dev, "Error: Power fault on Port %d has "
					    "been detected and the power to "
					    "that SFP+ module has been removed "
					    "to prevent failure of the card. "
					    "Please remove the SFP+ module and "
					    "restart the system to clear this "
					    "error.\n",
			 oc_port);
			/* Disable all RX_ALARMs except for mod_abs */
			bnx2x_cl45_write(bp, phy,
					 MDIO_PMA_DEVAD,
					 MDIO_PMA_LASI_RXCTRL, (1<<5));

			bnx2x_cl45_read(bp, phy,
					MDIO_PMA_DEVAD,
					MDIO_PMA_REG_PHY_IDENTIFIER, &val1);
			/* Wait for module_absent_event */
			val1 |= (1<<8);
			bnx2x_cl45_write(bp, phy,
					 MDIO_PMA_DEVAD,
					 MDIO_PMA_REG_PHY_IDENTIFIER, val1);
			/* Clear RX alarm */
			bnx2x_cl45_read(bp, phy,
				MDIO_PMA_DEVAD,
				MDIO_PMA_LASI_RXSTAT, &rx_alarm_status);
			bnx2x_8727_power_module(params->bp, phy, 0);
			return 0;
		}
	} /* Over current check */

	/* When module absent bit is set, check module */
	if (rx_alarm_status & (1<<5)) {
		bnx2x_8727_handle_mod_abs(phy, params);
		/* Enable all mod_abs and link detection bits */
		bnx2x_cl45_write(bp, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_LASI_RXCTRL,
				 ((1<<5) | (1<<2)));
	}

	if (!(phy->flags & FLAGS_SFP_NOT_APPROVED)) {
		DP(NETIF_MSG_LINK, "Enabling 8727 TX laser\n");
		bnx2x_sfp_set_transmitter(params, phy, 1);
	} else {
		DP(NETIF_MSG_LINK, "Tx is disabled\n");
		return 0;
	}

	bnx2x_cl45_read(bp, phy,
			MDIO_PMA_DEVAD,
			MDIO_PMA_REG_8073_SPEED_LINK_STATUS, &link_status);

	/* Bits 0..2 --> speed detected,
	 * Bits 13..15--> link is down
	 */
	if ((link_status & (1<<2)) && (!(link_status & (1<<15)))) {
		link_up = 1;
		vars->line_speed = SPEED_10000;
		DP(NETIF_MSG_LINK, "port %x: External link up in 10G\n",
			   params->port);
	} else if ((link_status & (1<<0)) && (!(link_status & (1<<13)))) {
		link_up = 1;
		vars->line_speed = SPEED_1000;
		DP(NETIF_MSG_LINK, "port %x: External link up in 1G\n",
			   params->port);
	} else {
		link_up = 0;
		DP(NETIF_MSG_LINK, "port %x: External link is down\n",
			   params->port);
	}

	/* Capture 10G link fault. */
	if (vars->line_speed == SPEED_10000) {
		bnx2x_cl45_read(bp, phy, MDIO_PMA_DEVAD,
			    MDIO_PMA_LASI_TXSTAT, &val1);

		bnx2x_cl45_read(bp, phy, MDIO_PMA_DEVAD,
			    MDIO_PMA_LASI_TXSTAT, &val1);

		if (val1 & (1<<0)) {
			vars->fault_detected = 1;
		}
	}

	if (link_up) {
		bnx2x_ext_phy_resolve_fc(phy, params, vars);
		vars->duplex = DUPLEX_FULL;
		DP(NETIF_MSG_LINK, "duplex = 0x%x\n", vars->duplex);
	}

	if ((DUAL_MEDIA(params)) &&
	    (phy->req_line_speed == SPEED_1000)) {
		bnx2x_cl45_read(bp, phy,
				MDIO_PMA_DEVAD,
				MDIO_PMA_REG_8727_PCS_GP, &val1);
		/* In case of dual-media board and 1G, power up the XAUI side,
		 * otherwise power it down. For 10G it is done automatically
		 */
		if (link_up)
			val1 &= ~(3<<10);
		else
			val1 |= (3<<10);
		bnx2x_cl45_write(bp, phy,
				 MDIO_PMA_DEVAD,
				 MDIO_PMA_REG_8727_PCS_GP, val1);
	}
	return link_up;
}