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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct phy_device {int dummy; } ;
struct netcp_intf {int dummy; } ;
struct net_device {struct phy_device* phydev; } ;
struct gbe_intf {TYPE_3__* slave; } ;
struct TYPE_5__ {int /*<<< orphan*/  supported; int /*<<< orphan*/  advertising; } ;
struct TYPE_4__ {scalar_t__ port; } ;
struct ethtool_link_ksettings {TYPE_2__ link_modes; TYPE_1__ base; } ;
struct TYPE_6__ {scalar_t__ phy_port_t; } ;

/* Variables and functions */
 int ADVERTISED_AUI ; 
 int ADVERTISED_BNC ; 
 int ADVERTISED_FIBRE ; 
 int ADVERTISED_MII ; 
 int ADVERTISED_TP ; 
 int EINVAL ; 
 scalar_t__ PORT_AUI ; 
 scalar_t__ PORT_BNC ; 
 scalar_t__ PORT_FIBRE ; 
 scalar_t__ PORT_MII ; 
 scalar_t__ PORT_TP ; 
 int /*<<< orphan*/  ethtool_convert_link_mode_to_legacy_u32 (int*,int /*<<< orphan*/ ) ; 
 struct gbe_intf* keystone_get_intf_data (struct netcp_intf*) ; 
 struct netcp_intf* netdev_priv (struct net_device*) ; 
 int phy_ethtool_ksettings_set (struct phy_device*,struct ethtool_link_ksettings const*) ; 

__attribute__((used)) static int keystone_set_link_ksettings(struct net_device *ndev,
				       const struct ethtool_link_ksettings *cmd)
{
	struct netcp_intf *netcp = netdev_priv(ndev);
	struct phy_device *phy = ndev->phydev;
	struct gbe_intf *gbe_intf;
	u8 port = cmd->base.port;
	u32 advertising, supported;
	u32 features;

	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);
	ethtool_convert_link_mode_to_legacy_u32(&supported,
						cmd->link_modes.supported);
	features = advertising & supported;

	if (!phy)
		return -EINVAL;

	gbe_intf = keystone_get_intf_data(netcp);
	if (!gbe_intf)
		return -EINVAL;

	if (!gbe_intf->slave)
		return -EINVAL;

	if (port != gbe_intf->slave->phy_port_t) {
		if ((port == PORT_TP) && !(features & ADVERTISED_TP))
			return -EINVAL;

		if ((port == PORT_AUI) && !(features & ADVERTISED_AUI))
			return -EINVAL;

		if ((port == PORT_BNC) && !(features & ADVERTISED_BNC))
			return -EINVAL;

		if ((port == PORT_MII) && !(features & ADVERTISED_MII))
			return -EINVAL;

		if ((port == PORT_FIBRE) && !(features & ADVERTISED_FIBRE))
			return -EINVAL;
	}

	gbe_intf->slave->phy_port_t = port;
	return phy_ethtool_ksettings_set(phy, cmd);
}