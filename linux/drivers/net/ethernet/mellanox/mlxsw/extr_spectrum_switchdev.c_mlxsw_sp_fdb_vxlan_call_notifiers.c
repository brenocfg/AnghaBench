#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  union mlxsw_sp_l3addr {int dummy; } mlxsw_sp_l3addr ;
struct TYPE_2__ {int /*<<< orphan*/  dst_port; } ;
struct vxlan_dev {TYPE_1__ cfg; } ;
struct switchdev_notifier_vxlan_fdb_info {int offloaded; int /*<<< orphan*/  info; void* vni; int /*<<< orphan*/  eth_addr; scalar_t__ remote_ifindex; void* remote_vni; int /*<<< orphan*/  remote_port; int /*<<< orphan*/  remote_ip; } ;
struct net_device {int dummy; } ;
typedef  enum switchdev_notifier_type { ____Placeholder_switchdev_notifier_type } switchdev_notifier_type ;
typedef  enum mlxsw_sp_l3proto { ____Placeholder_mlxsw_sp_l3proto } mlxsw_sp_l3proto ;
typedef  void* __be32 ;

/* Variables and functions */
 int SWITCHDEV_VXLAN_FDB_ADD_TO_BRIDGE ; 
 int SWITCHDEV_VXLAN_FDB_DEL_TO_BRIDGE ; 
 int /*<<< orphan*/  call_switchdev_notifiers (int,struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  mlxsw_sp_switchdev_addr_vxlan_convert (int,union mlxsw_sp_l3addr*,int /*<<< orphan*/ *) ; 
 struct vxlan_dev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void mlxsw_sp_fdb_vxlan_call_notifiers(struct net_device *dev,
					      const char *mac,
					      enum mlxsw_sp_l3proto proto,
					      union mlxsw_sp_l3addr *addr,
					      __be32 vni, bool adding)
{
	struct switchdev_notifier_vxlan_fdb_info info;
	struct vxlan_dev *vxlan = netdev_priv(dev);
	enum switchdev_notifier_type type;

	type = adding ? SWITCHDEV_VXLAN_FDB_ADD_TO_BRIDGE :
			SWITCHDEV_VXLAN_FDB_DEL_TO_BRIDGE;
	mlxsw_sp_switchdev_addr_vxlan_convert(proto, addr, &info.remote_ip);
	info.remote_port = vxlan->cfg.dst_port;
	info.remote_vni = vni;
	info.remote_ifindex = 0;
	ether_addr_copy(info.eth_addr, mac);
	info.vni = vni;
	info.offloaded = adding;
	call_switchdev_notifiers(type, dev, &info.info, NULL);
}