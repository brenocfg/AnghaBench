#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct phy_device {scalar_t__ interface; int /*<<< orphan*/  mdix; int /*<<< orphan*/  mdix_ctrl; int /*<<< orphan*/  autoneg; TYPE_2__ mdio; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  lp_advertising; int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct TYPE_6__ {int /*<<< orphan*/  eth_tp_mdix; int /*<<< orphan*/  eth_tp_mdix_ctrl; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  phy_address; int /*<<< orphan*/  transceiver; int /*<<< orphan*/  port; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct TYPE_4__ {int /*<<< orphan*/  lp_advertising; int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct ethtool_link_ksettings {TYPE_3__ base; TYPE_1__ link_modes; } ;

/* Variables and functions */
 scalar_t__ PHY_INTERFACE_MODE_MOCA ; 
 int /*<<< orphan*/  PORT_BNC ; 
 int /*<<< orphan*/  PORT_MII ; 
 int /*<<< orphan*/  XCVR_EXTERNAL ; 
 int /*<<< orphan*/  XCVR_INTERNAL ; 
 int /*<<< orphan*/  linkmode_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ phy_is_internal (struct phy_device*) ; 

void phy_ethtool_ksettings_get(struct phy_device *phydev,
			       struct ethtool_link_ksettings *cmd)
{
	linkmode_copy(cmd->link_modes.supported, phydev->supported);
	linkmode_copy(cmd->link_modes.advertising, phydev->advertising);
	linkmode_copy(cmd->link_modes.lp_advertising, phydev->lp_advertising);

	cmd->base.speed = phydev->speed;
	cmd->base.duplex = phydev->duplex;
	if (phydev->interface == PHY_INTERFACE_MODE_MOCA)
		cmd->base.port = PORT_BNC;
	else
		cmd->base.port = PORT_MII;
	cmd->base.transceiver = phy_is_internal(phydev) ?
				XCVR_INTERNAL : XCVR_EXTERNAL;
	cmd->base.phy_address = phydev->mdio.addr;
	cmd->base.autoneg = phydev->autoneg;
	cmd->base.eth_tp_mdix_ctrl = phydev->mdix_ctrl;
	cmd->base.eth_tp_mdix = phydev->mdix;
}