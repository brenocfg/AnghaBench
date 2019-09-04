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
struct netdev_private {scalar_t__ autoneg; int phy_addr_external; int advertising; scalar_t__ speed; scalar_t__ duplex; scalar_t__ full_duplex; scalar_t__ ignore_phy; } ;
struct net_device {scalar_t__ if_port; } ;
struct TYPE_4__ {scalar_t__ port; scalar_t__ autoneg; scalar_t__ speed; scalar_t__ duplex; int phy_address; } ;
struct TYPE_3__ {int /*<<< orphan*/  advertising; } ;
struct ethtool_link_ksettings {TYPE_2__ base; TYPE_1__ link_modes; } ;

/* Variables and functions */
 scalar_t__ ADVERTISED_100baseT_Full ; 
 scalar_t__ ADVERTISED_100baseT_Half ; 
 scalar_t__ ADVERTISED_10baseT_Full ; 
 scalar_t__ ADVERTISED_10baseT_Half ; 
 int ADVERTISE_100BASE4 ; 
 int ADVERTISE_100FULL ; 
 int ADVERTISE_100HALF ; 
 int ADVERTISE_10FULL ; 
 int ADVERTISE_10HALF ; 
 int ADVERTISE_ALL ; 
 scalar_t__ AUTONEG_DISABLE ; 
 scalar_t__ AUTONEG_ENABLE ; 
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ DUPLEX_HALF ; 
 int EINVAL ; 
 scalar_t__ PORT_FIBRE ; 
 scalar_t__ PORT_MII ; 
 scalar_t__ PORT_TP ; 
 int PhyAddrMask ; 
 scalar_t__ SPEED_10 ; 
 scalar_t__ SPEED_100 ; 
 int /*<<< orphan*/  check_link (struct net_device*) ; 
 int /*<<< orphan*/  ethtool_convert_link_mode_to_legacy_u32 (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_phy_fixup (struct net_device*) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  switch_port_external (struct net_device*) ; 
 int /*<<< orphan*/  switch_port_internal (struct net_device*) ; 

__attribute__((used)) static int netdev_set_ecmd(struct net_device *dev,
			   const struct ethtool_link_ksettings *ecmd)
{
	struct netdev_private *np = netdev_priv(dev);
	u32 advertising;

	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						ecmd->link_modes.advertising);

	if (ecmd->base.port != PORT_TP &&
	    ecmd->base.port != PORT_MII &&
	    ecmd->base.port != PORT_FIBRE)
		return -EINVAL;
	if (ecmd->base.autoneg == AUTONEG_ENABLE) {
		if ((advertising & (ADVERTISED_10baseT_Half |
					  ADVERTISED_10baseT_Full |
					  ADVERTISED_100baseT_Half |
					  ADVERTISED_100baseT_Full)) == 0) {
			return -EINVAL;
		}
	} else if (ecmd->base.autoneg == AUTONEG_DISABLE) {
		u32 speed = ecmd->base.speed;
		if (speed != SPEED_10 && speed != SPEED_100)
			return -EINVAL;
		if (ecmd->base.duplex != DUPLEX_HALF &&
		    ecmd->base.duplex != DUPLEX_FULL)
			return -EINVAL;
	} else {
		return -EINVAL;
	}

	/*
	 * If we're ignoring the PHY then autoneg and the internal
	 * transceiver are really not going to work so don't let the
	 * user select them.
	 */
	if (np->ignore_phy && (ecmd->base.autoneg == AUTONEG_ENABLE ||
			       ecmd->base.port == PORT_TP))
		return -EINVAL;

	/*
	 * maxtxpkt, maxrxpkt: ignored for now.
	 *
	 * transceiver:
	 * PORT_TP is always XCVR_INTERNAL, PORT_MII and PORT_FIBRE are always
	 * XCVR_EXTERNAL. The implementation thus ignores ecmd->transceiver and
	 * selects based on ecmd->port.
	 *
	 * Actually PORT_FIBRE is nearly identical to PORT_MII: it's for fibre
	 * phys that are connected to the mii bus. It's used to apply fibre
	 * specific updates.
	 */

	/* WHEW! now lets bang some bits */

	/* save the parms */
	dev->if_port          = ecmd->base.port;
	np->autoneg           = ecmd->base.autoneg;
	np->phy_addr_external = ecmd->base.phy_address & PhyAddrMask;
	if (np->autoneg == AUTONEG_ENABLE) {
		/* advertise only what has been requested */
		np->advertising &= ~(ADVERTISE_ALL | ADVERTISE_100BASE4);
		if (advertising & ADVERTISED_10baseT_Half)
			np->advertising |= ADVERTISE_10HALF;
		if (advertising & ADVERTISED_10baseT_Full)
			np->advertising |= ADVERTISE_10FULL;
		if (advertising & ADVERTISED_100baseT_Half)
			np->advertising |= ADVERTISE_100HALF;
		if (advertising & ADVERTISED_100baseT_Full)
			np->advertising |= ADVERTISE_100FULL;
	} else {
		np->speed  = ecmd->base.speed;
		np->duplex = ecmd->base.duplex;
		/* user overriding the initial full duplex parm? */
		if (np->duplex == DUPLEX_HALF)
			np->full_duplex = 0;
	}

	/* get the right phy enabled */
	if (ecmd->base.port == PORT_TP)
		switch_port_internal(dev);
	else
		switch_port_external(dev);

	/* set parms and see how this affected our link status */
	init_phy_fixup(dev);
	check_link(dev);
	return 0;
}