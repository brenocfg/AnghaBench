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
struct netlink_ext_ack {int dummy; } ;
struct netdev_notifier_changeupper_info {int /*<<< orphan*/  linking; struct net_device* upper_dev; int /*<<< orphan*/  upper_info; int /*<<< orphan*/  info; } ;
struct net_device {int dummy; } ;
struct mlxsw_sp_port {struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  NETDEV_CHANGEUPPER 129 
#define  NETDEV_PRECHANGEUPPER 128 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  is_vlan_dev (struct net_device*) ; 
 int /*<<< orphan*/  mlxsw_sp_bridge_device_is_offloaded (struct mlxsw_sp*,struct net_device*) ; 
 int /*<<< orphan*/  mlxsw_sp_bridge_has_vxlan (struct net_device*) ; 
 int /*<<< orphan*/  mlxsw_sp_bridge_vxlan_is_valid (struct net_device*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  mlxsw_sp_master_lag_check (struct mlxsw_sp*,struct net_device*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int mlxsw_sp_port_bridge_join (struct mlxsw_sp_port*,struct net_device*,struct net_device*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  mlxsw_sp_port_bridge_leave (struct mlxsw_sp_port*,struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  mlxsw_sp_port_lag_col_dist_disable (struct mlxsw_sp_port*) ; 
 int mlxsw_sp_port_lag_join (struct mlxsw_sp_port*,struct net_device*) ; 
 int /*<<< orphan*/  mlxsw_sp_port_lag_leave (struct mlxsw_sp_port*,struct net_device*) ; 
 int mlxsw_sp_port_ovs_join (struct mlxsw_sp_port*) ; 
 int /*<<< orphan*/  mlxsw_sp_port_ovs_leave (struct mlxsw_sp_port*) ; 
 int /*<<< orphan*/  mlxsw_sp_rif_find_by_dev (struct mlxsw_sp*,struct net_device*) ; 
 int /*<<< orphan*/  mlxsw_sp_rif_macvlan_del (struct mlxsw_sp*,struct net_device*) ; 
 int /*<<< orphan*/  netdev_has_any_upper_dev (struct net_device*) ; 
 struct net_device* netdev_master_upper_dev_get (struct net_device*) ; 
 struct netlink_ext_ack* netdev_notifier_info_to_extack (int /*<<< orphan*/ *) ; 
 struct mlxsw_sp_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_is_bridge_master (struct net_device*) ; 
 int /*<<< orphan*/  netif_is_bridge_port (struct net_device*) ; 
 int /*<<< orphan*/  netif_is_lag_master (struct net_device*) ; 
 int /*<<< orphan*/  netif_is_lag_port (struct net_device*) ; 
 int /*<<< orphan*/  netif_is_macvlan (struct net_device*) ; 
 int /*<<< orphan*/  netif_is_ovs_master (struct net_device*) ; 
 int /*<<< orphan*/  netif_is_ovs_port (struct net_device*) ; 
 struct net_device* vlan_dev_real_dev (struct net_device*) ; 
 int /*<<< orphan*/  vlan_uses_dev (struct net_device*) ; 

__attribute__((used)) static int mlxsw_sp_netdevice_port_upper_event(struct net_device *lower_dev,
					       struct net_device *dev,
					       unsigned long event, void *ptr)
{
	struct netdev_notifier_changeupper_info *info;
	struct mlxsw_sp_port *mlxsw_sp_port;
	struct netlink_ext_ack *extack;
	struct net_device *upper_dev;
	struct mlxsw_sp *mlxsw_sp;
	int err = 0;

	mlxsw_sp_port = netdev_priv(dev);
	mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	info = ptr;
	extack = netdev_notifier_info_to_extack(&info->info);

	switch (event) {
	case NETDEV_PRECHANGEUPPER:
		upper_dev = info->upper_dev;
		if (!is_vlan_dev(upper_dev) &&
		    !netif_is_lag_master(upper_dev) &&
		    !netif_is_bridge_master(upper_dev) &&
		    !netif_is_ovs_master(upper_dev) &&
		    !netif_is_macvlan(upper_dev)) {
			NL_SET_ERR_MSG_MOD(extack, "Unknown upper device type");
			return -EINVAL;
		}
		if (!info->linking)
			break;
		if (netif_is_bridge_master(upper_dev) &&
		    !mlxsw_sp_bridge_device_is_offloaded(mlxsw_sp, upper_dev) &&
		    mlxsw_sp_bridge_has_vxlan(upper_dev) &&
		    !mlxsw_sp_bridge_vxlan_is_valid(upper_dev, extack))
			return -EOPNOTSUPP;
		if (netdev_has_any_upper_dev(upper_dev) &&
		    (!netif_is_bridge_master(upper_dev) ||
		     !mlxsw_sp_bridge_device_is_offloaded(mlxsw_sp,
							  upper_dev))) {
			NL_SET_ERR_MSG_MOD(extack, "Enslaving a port to a device that already has an upper device is not supported");
			return -EINVAL;
		}
		if (netif_is_lag_master(upper_dev) &&
		    !mlxsw_sp_master_lag_check(mlxsw_sp, upper_dev,
					       info->upper_info, extack))
			return -EINVAL;
		if (netif_is_lag_master(upper_dev) && vlan_uses_dev(dev)) {
			NL_SET_ERR_MSG_MOD(extack, "Master device is a LAG master and this device has a VLAN");
			return -EINVAL;
		}
		if (netif_is_lag_port(dev) && is_vlan_dev(upper_dev) &&
		    !netif_is_lag_master(vlan_dev_real_dev(upper_dev))) {
			NL_SET_ERR_MSG_MOD(extack, "Can not put a VLAN on a LAG port");
			return -EINVAL;
		}
		if (netif_is_macvlan(upper_dev) &&
		    !mlxsw_sp_rif_find_by_dev(mlxsw_sp, lower_dev)) {
			NL_SET_ERR_MSG_MOD(extack, "macvlan is only supported on top of router interfaces");
			return -EOPNOTSUPP;
		}
		if (netif_is_ovs_master(upper_dev) && vlan_uses_dev(dev)) {
			NL_SET_ERR_MSG_MOD(extack, "Master device is an OVS master and this device has a VLAN");
			return -EINVAL;
		}
		if (netif_is_ovs_port(dev) && is_vlan_dev(upper_dev)) {
			NL_SET_ERR_MSG_MOD(extack, "Can not put a VLAN on an OVS port");
			return -EINVAL;
		}
		break;
	case NETDEV_CHANGEUPPER:
		upper_dev = info->upper_dev;
		if (netif_is_bridge_master(upper_dev)) {
			if (info->linking)
				err = mlxsw_sp_port_bridge_join(mlxsw_sp_port,
								lower_dev,
								upper_dev,
								extack);
			else
				mlxsw_sp_port_bridge_leave(mlxsw_sp_port,
							   lower_dev,
							   upper_dev);
		} else if (netif_is_lag_master(upper_dev)) {
			if (info->linking) {
				err = mlxsw_sp_port_lag_join(mlxsw_sp_port,
							     upper_dev);
			} else {
				mlxsw_sp_port_lag_col_dist_disable(mlxsw_sp_port);
				mlxsw_sp_port_lag_leave(mlxsw_sp_port,
							upper_dev);
			}
		} else if (netif_is_ovs_master(upper_dev)) {
			if (info->linking)
				err = mlxsw_sp_port_ovs_join(mlxsw_sp_port);
			else
				mlxsw_sp_port_ovs_leave(mlxsw_sp_port);
		} else if (netif_is_macvlan(upper_dev)) {
			if (!info->linking)
				mlxsw_sp_rif_macvlan_del(mlxsw_sp, upper_dev);
		} else if (is_vlan_dev(upper_dev)) {
			struct net_device *br_dev;

			if (!netif_is_bridge_port(upper_dev))
				break;
			if (info->linking)
				break;
			br_dev = netdev_master_upper_dev_get(upper_dev);
			mlxsw_sp_port_bridge_leave(mlxsw_sp_port, upper_dev,
						   br_dev);
		}
		break;
	}

	return err;
}