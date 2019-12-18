#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_10__ {int /*<<< orphan*/  autoneg; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct TYPE_7__ {int /*<<< orphan*/  prtad; } ;
struct TYPE_8__ {TYPE_2__ mdio; } ;
struct port_info {TYPE_5__ link_config; TYPE_3__ phy; } ;
struct net_device {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  autoneg; int /*<<< orphan*/  phy_address; int /*<<< orphan*/  port; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct TYPE_6__ {int /*<<< orphan*/  supported; int /*<<< orphan*/  advertising; } ;
struct ethtool_link_ksettings {TYPE_4__ base; TYPE_1__ link_modes; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
 int /*<<< orphan*/  PORT_FIBRE ; 
 int /*<<< orphan*/  PORT_TP ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 int SUPPORTED_TP ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethtool_convert_link_mode_to_legacy_u32 (int*,int /*<<< orphan*/ ) ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 

__attribute__((used)) static int get_link_ksettings(struct net_device *dev,
			      struct ethtool_link_ksettings *cmd)
{
	struct port_info *p = netdev_priv(dev);
	u32 supported;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						p->link_config.supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						p->link_config.advertising);

	if (netif_carrier_ok(dev)) {
		cmd->base.speed = p->link_config.speed;
		cmd->base.duplex = p->link_config.duplex;
	} else {
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.duplex = DUPLEX_UNKNOWN;
	}

	ethtool_convert_link_mode_to_legacy_u32(&supported,
						cmd->link_modes.supported);

	cmd->base.port = (supported & SUPPORTED_TP) ? PORT_TP : PORT_FIBRE;
	cmd->base.phy_address = p->phy.mdio.prtad;
	cmd->base.autoneg = p->link_config.autoneg;
	return 0;
}