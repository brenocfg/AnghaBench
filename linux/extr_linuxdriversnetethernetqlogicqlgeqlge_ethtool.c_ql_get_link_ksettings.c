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
struct ql_adapter {int link_status; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct TYPE_3__ {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  port; int /*<<< orphan*/  autoneg; } ;
struct ethtool_link_ksettings {TYPE_2__ link_modes; TYPE_1__ base; } ;

/* Variables and functions */
 int ADVERTISED_10000baseT_Full ; 
 int ADVERTISED_Autoneg ; 
 int ADVERTISED_FIBRE ; 
 int ADVERTISED_TP ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  PORT_FIBRE ; 
 int /*<<< orphan*/  PORT_TP ; 
 int /*<<< orphan*/  SPEED_10000 ; 
 int STS_LINK_TYPE_10GBASET ; 
 int STS_LINK_TYPE_MASK ; 
 int SUPPORTED_10000baseT_Full ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_FIBRE ; 
 int SUPPORTED_TP ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,int) ; 
 struct ql_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ql_get_link_ksettings(struct net_device *ndev,
				 struct ethtool_link_ksettings *ecmd)
{
	struct ql_adapter *qdev = netdev_priv(ndev);
	u32 supported, advertising;

	supported = SUPPORTED_10000baseT_Full;
	advertising = ADVERTISED_10000baseT_Full;

	if ((qdev->link_status & STS_LINK_TYPE_MASK) ==
				STS_LINK_TYPE_10GBASET) {
		supported |= (SUPPORTED_TP | SUPPORTED_Autoneg);
		advertising |= (ADVERTISED_TP | ADVERTISED_Autoneg);
		ecmd->base.port = PORT_TP;
		ecmd->base.autoneg = AUTONEG_ENABLE;
	} else {
		supported |= SUPPORTED_FIBRE;
		advertising |= ADVERTISED_FIBRE;
		ecmd->base.port = PORT_FIBRE;
	}

	ecmd->base.speed = SPEED_10000;
	ecmd->base.duplex = DUPLEX_FULL;

	ethtool_convert_legacy_u32_to_link_mode(ecmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(ecmd->link_modes.advertising,
						advertising);

	return 0;
}