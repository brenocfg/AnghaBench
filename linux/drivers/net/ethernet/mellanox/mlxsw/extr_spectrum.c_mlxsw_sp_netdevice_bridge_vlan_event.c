#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct netlink_ext_ack {int dummy; } ;
struct netdev_notifier_changeupper_info {int /*<<< orphan*/  linking; struct net_device* upper_dev; int /*<<< orphan*/  info; } ;
struct net_device {int dummy; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  NETDEV_CHANGEUPPER 129 
#define  NETDEV_PRECHANGEUPPER 128 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 struct mlxsw_sp* mlxsw_sp_lower_get (struct net_device*) ; 
 int /*<<< orphan*/  mlxsw_sp_rif_find_by_dev (struct mlxsw_sp*,struct net_device*) ; 
 int /*<<< orphan*/  mlxsw_sp_rif_macvlan_del (struct mlxsw_sp*,struct net_device*) ; 
 struct netlink_ext_ack* netdev_notifier_info_to_extack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_is_macvlan (struct net_device*) ; 

__attribute__((used)) static int mlxsw_sp_netdevice_bridge_vlan_event(struct net_device *vlan_dev,
						struct net_device *br_dev,
						unsigned long event, void *ptr,
						u16 vid)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_lower_get(vlan_dev);
	struct netdev_notifier_changeupper_info *info = ptr;
	struct netlink_ext_ack *extack;
	struct net_device *upper_dev;

	if (!mlxsw_sp)
		return 0;

	extack = netdev_notifier_info_to_extack(&info->info);

	switch (event) {
	case NETDEV_PRECHANGEUPPER:
		upper_dev = info->upper_dev;
		if (!netif_is_macvlan(upper_dev)) {
			NL_SET_ERR_MSG_MOD(extack, "Unknown upper device type");
			return -EOPNOTSUPP;
		}
		if (!info->linking)
			break;
		if (netif_is_macvlan(upper_dev) &&
		    !mlxsw_sp_rif_find_by_dev(mlxsw_sp, vlan_dev)) {
			NL_SET_ERR_MSG_MOD(extack, "macvlan is only supported on top of router interfaces");
			return -EOPNOTSUPP;
		}
		break;
	case NETDEV_CHANGEUPPER:
		upper_dev = info->upper_dev;
		if (info->linking)
			break;
		if (netif_is_macvlan(upper_dev))
			mlxsw_sp_rif_macvlan_del(mlxsw_sp, upper_dev);
		break;
	}

	return 0;
}