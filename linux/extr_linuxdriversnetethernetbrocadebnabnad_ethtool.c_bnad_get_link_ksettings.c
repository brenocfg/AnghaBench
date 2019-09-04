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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct TYPE_3__ {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; scalar_t__ phy_address; int /*<<< orphan*/  port; int /*<<< orphan*/  autoneg; } ;
struct ethtool_link_ksettings {TYPE_2__ link_modes; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVERTISED_10000baseT_Full ; 
 int /*<<< orphan*/  ADVERTISED_FIBRE ; 
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
 int /*<<< orphan*/  PORT_FIBRE ; 
 int /*<<< orphan*/  SPEED_10000 ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 int /*<<< orphan*/  SUPPORTED_10000baseT_Full ; 
 int /*<<< orphan*/  SUPPORTED_FIBRE ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 

__attribute__((used)) static int
bnad_get_link_ksettings(struct net_device *netdev,
			struct ethtool_link_ksettings *cmd)
{
	u32 supported, advertising;

	supported = SUPPORTED_10000baseT_Full;
	advertising = ADVERTISED_10000baseT_Full;
	cmd->base.autoneg = AUTONEG_DISABLE;
	supported |= SUPPORTED_FIBRE;
	advertising |= ADVERTISED_FIBRE;
	cmd->base.port = PORT_FIBRE;
	cmd->base.phy_address = 0;

	if (netif_carrier_ok(netdev)) {
		cmd->base.speed = SPEED_10000;
		cmd->base.duplex = DUPLEX_FULL;
	} else {
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.duplex = DUPLEX_UNKNOWN;
	}

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	return 0;
}