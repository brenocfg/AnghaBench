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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {scalar_t__ port_type; } ;
struct netxen_adapter {int capabilities; int /*<<< orphan*/  link_autoneg; int /*<<< orphan*/  link_duplex; int /*<<< orphan*/  link_speed; TYPE_1__ ahw; } ;
struct net_device {TYPE_3__* netdev_ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  autoneg; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct ethtool_link_ksettings {TYPE_2__ base; } ;
struct TYPE_6__ {int (* ndo_open ) (struct net_device*) ;int /*<<< orphan*/  (* ndo_stop ) (struct net_device*) ;} ;

/* Variables and functions */
 int EIO ; 
 int EOPNOTSUPP ; 
 scalar_t__ NETXEN_NIC_GBE ; 
 int NX_FW_CAPABILITY_GBE_LINK_CFG ; 
 int NX_RCODE_NOT_SUPPORTED ; 
 struct netxen_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int nx_fw_cmd_set_gbe_port (struct netxen_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 
 int stub2 (struct net_device*) ; 

__attribute__((used)) static int
netxen_nic_set_link_ksettings(struct net_device *dev,
			      const struct ethtool_link_ksettings *cmd)
{
	struct netxen_adapter *adapter = netdev_priv(dev);
	u32 speed = cmd->base.speed;
	int ret;

	if (adapter->ahw.port_type != NETXEN_NIC_GBE)
		return -EOPNOTSUPP;

	if (!(adapter->capabilities & NX_FW_CAPABILITY_GBE_LINK_CFG))
		return -EOPNOTSUPP;

	ret = nx_fw_cmd_set_gbe_port(adapter, speed, cmd->base.duplex,
				     cmd->base.autoneg);
	if (ret == NX_RCODE_NOT_SUPPORTED)
		return -EOPNOTSUPP;
	else if (ret)
		return -EIO;

	adapter->link_speed = speed;
	adapter->link_duplex = cmd->base.duplex;
	adapter->link_autoneg = cmd->base.autoneg;

	if (!netif_running(dev))
		return 0;

	dev->netdev_ops->ndo_stop(dev);
	return dev->netdev_ops->ndo_open(dev);
}