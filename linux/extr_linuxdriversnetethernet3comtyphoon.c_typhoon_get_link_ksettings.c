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
typedef  int u32 ;
struct typhoon {int xcvr_select; int capabilities; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct TYPE_3__ {int /*<<< orphan*/  autoneg; scalar_t__ phy_address; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  port; } ;
struct ethtool_link_ksettings {TYPE_2__ link_modes; TYPE_1__ base; } ;

/* Variables and functions */
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_100baseT_Half ; 
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_10baseT_Half ; 
 int ADVERTISED_Autoneg ; 
 int ADVERTISED_FIBRE ; 
 int ADVERTISED_TP ; 
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int /*<<< orphan*/  PORT_FIBRE ; 
 int /*<<< orphan*/  PORT_TP ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_FIBRE ; 
 int SUPPORTED_TP ; 
 int TYPHOON_FIBER ; 
#define  TYPHOON_XCVR_100FULL 132 
#define  TYPHOON_XCVR_100HALF 131 
#define  TYPHOON_XCVR_10FULL 130 
#define  TYPHOON_XCVR_10HALF 129 
#define  TYPHOON_XCVR_AUTONEG 128 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,int) ; 
 struct typhoon* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  typhoon_do_get_stats (struct typhoon*) ; 

__attribute__((used)) static int
typhoon_get_link_ksettings(struct net_device *dev,
			   struct ethtool_link_ksettings *cmd)
{
	struct typhoon *tp = netdev_priv(dev);
	u32 supported, advertising = 0;

	supported = SUPPORTED_100baseT_Half | SUPPORTED_100baseT_Full |
				SUPPORTED_Autoneg;

	switch (tp->xcvr_select) {
	case TYPHOON_XCVR_10HALF:
		advertising = ADVERTISED_10baseT_Half;
		break;
	case TYPHOON_XCVR_10FULL:
		advertising = ADVERTISED_10baseT_Full;
		break;
	case TYPHOON_XCVR_100HALF:
		advertising = ADVERTISED_100baseT_Half;
		break;
	case TYPHOON_XCVR_100FULL:
		advertising = ADVERTISED_100baseT_Full;
		break;
	case TYPHOON_XCVR_AUTONEG:
		advertising = ADVERTISED_10baseT_Half |
					    ADVERTISED_10baseT_Full |
					    ADVERTISED_100baseT_Half |
					    ADVERTISED_100baseT_Full |
					    ADVERTISED_Autoneg;
		break;
	}

	if(tp->capabilities & TYPHOON_FIBER) {
		supported |= SUPPORTED_FIBRE;
		advertising |= ADVERTISED_FIBRE;
		cmd->base.port = PORT_FIBRE;
	} else {
		supported |= SUPPORTED_10baseT_Half |
		    			SUPPORTED_10baseT_Full |
					SUPPORTED_TP;
		advertising |= ADVERTISED_TP;
		cmd->base.port = PORT_TP;
	}

	/* need to get stats to make these link speed/duplex valid */
	typhoon_do_get_stats(tp);
	cmd->base.speed = tp->speed;
	cmd->base.duplex = tp->duplex;
	cmd->base.phy_address = 0;
	if(tp->xcvr_select == TYPHOON_XCVR_AUTONEG)
		cmd->base.autoneg = AUTONEG_ENABLE;
	else
		cmd->base.autoneg = AUTONEG_DISABLE;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	return 0;
}