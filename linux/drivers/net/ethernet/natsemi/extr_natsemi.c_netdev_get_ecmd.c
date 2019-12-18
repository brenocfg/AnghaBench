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
typedef  scalar_t__ u32 ;
struct netdev_private {int advertising; int /*<<< orphan*/  phy_addr_external; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct net_device {int if_port; } ;
struct TYPE_4__ {int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct TYPE_3__ {int port; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  phy_address; } ;
struct ethtool_link_ksettings {TYPE_2__ link_modes; TYPE_1__ base; } ;

/* Variables and functions */
 scalar_t__ ADVERTISED_100baseT_Full ; 
 scalar_t__ ADVERTISED_100baseT_Half ; 
 scalar_t__ ADVERTISED_10baseT_Full ; 
 scalar_t__ ADVERTISED_10baseT_Half ; 
 scalar_t__ ADVERTISED_Autoneg ; 
 scalar_t__ ADVERTISED_FIBRE ; 
 scalar_t__ ADVERTISED_MII ; 
 scalar_t__ ADVERTISED_TP ; 
 int ADVERTISE_100FULL ; 
 int ADVERTISE_100HALF ; 
 int ADVERTISE_10FULL ; 
 int ADVERTISE_10HALF ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 scalar_t__ LPA_100FULL ; 
 scalar_t__ LPA_100HALF ; 
 scalar_t__ LPA_10FULL ; 
 int /*<<< orphan*/  MII_LPA ; 
#define  PORT_FIBRE 130 
#define  PORT_MII 129 
#define  PORT_TP 128 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 scalar_t__ SUPPORTED_100baseT_Full ; 
 scalar_t__ SUPPORTED_100baseT_Half ; 
 scalar_t__ SUPPORTED_10baseT_Full ; 
 scalar_t__ SUPPORTED_10baseT_Half ; 
 scalar_t__ SUPPORTED_Autoneg ; 
 scalar_t__ SUPPORTED_FIBRE ; 
 scalar_t__ SUPPORTED_MII ; 
 scalar_t__ SUPPORTED_TP ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,scalar_t__) ; 
 int mdio_read (struct net_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ mii_nway_result (int) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int netdev_get_ecmd(struct net_device *dev,
			   struct ethtool_link_ksettings *ecmd)
{
	struct netdev_private *np = netdev_priv(dev);
	u32 supported, advertising;
	u32 tmp;

	ecmd->base.port   = dev->if_port;
	ecmd->base.speed  = np->speed;
	ecmd->base.duplex = np->duplex;
	ecmd->base.autoneg = np->autoneg;
	advertising = 0;

	if (np->advertising & ADVERTISE_10HALF)
		advertising |= ADVERTISED_10baseT_Half;
	if (np->advertising & ADVERTISE_10FULL)
		advertising |= ADVERTISED_10baseT_Full;
	if (np->advertising & ADVERTISE_100HALF)
		advertising |= ADVERTISED_100baseT_Half;
	if (np->advertising & ADVERTISE_100FULL)
		advertising |= ADVERTISED_100baseT_Full;
	supported   = (SUPPORTED_Autoneg |
		SUPPORTED_10baseT_Half  | SUPPORTED_10baseT_Full  |
		SUPPORTED_100baseT_Half | SUPPORTED_100baseT_Full |
		SUPPORTED_TP | SUPPORTED_MII | SUPPORTED_FIBRE);
	ecmd->base.phy_address = np->phy_addr_external;
	/*
	 * We intentionally report the phy address of the external
	 * phy, even if the internal phy is used. This is necessary
	 * to work around a deficiency of the ethtool interface:
	 * It's only possible to query the settings of the active
	 * port. Therefore
	 * # ethtool -s ethX port mii
	 * actually sends an ioctl to switch to port mii with the
	 * settings that are used for the current active port.
	 * If we would report a different phy address in this
	 * command, then
	 * # ethtool -s ethX port tp;ethtool -s ethX port mii
	 * would unintentionally change the phy address.
	 *
	 * Fortunately the phy address doesn't matter with the
	 * internal phy...
	 */

	/* set information based on active port type */
	switch (ecmd->base.port) {
	default:
	case PORT_TP:
		advertising |= ADVERTISED_TP;
		break;
	case PORT_MII:
		advertising |= ADVERTISED_MII;
		break;
	case PORT_FIBRE:
		advertising |= ADVERTISED_FIBRE;
		break;
	}

	/* if autonegotiation is on, try to return the active speed/duplex */
	if (ecmd->base.autoneg == AUTONEG_ENABLE) {
		advertising |= ADVERTISED_Autoneg;
		tmp = mii_nway_result(
			np->advertising & mdio_read(dev, MII_LPA));
		if (tmp == LPA_100FULL || tmp == LPA_100HALF)
			ecmd->base.speed = SPEED_100;
		else
			ecmd->base.speed = SPEED_10;
		if (tmp == LPA_100FULL || tmp == LPA_10FULL)
			ecmd->base.duplex = DUPLEX_FULL;
		else
			ecmd->base.duplex = DUPLEX_HALF;
	}

	/* ignore maxtxpkt, maxrxpkt for now */

	ethtool_convert_legacy_u32_to_link_mode(ecmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(ecmd->link_modes.advertising,
						advertising);

	return 0;
}