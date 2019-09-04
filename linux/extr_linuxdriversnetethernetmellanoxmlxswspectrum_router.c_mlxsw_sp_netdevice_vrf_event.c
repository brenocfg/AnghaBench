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
struct netdev_notifier_changeupper_info {int /*<<< orphan*/  info; int /*<<< orphan*/  linking; } ;
struct net_device {int dummy; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
#define  NETDEV_CHANGEUPPER 129 
#define  NETDEV_PRECHANGEUPPER 128 
 struct mlxsw_sp* mlxsw_sp_lower_get (struct net_device*) ; 
 int mlxsw_sp_port_vrf_join (struct mlxsw_sp*,struct net_device*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  mlxsw_sp_port_vrf_leave (struct mlxsw_sp*,struct net_device*) ; 
 struct netlink_ext_ack* netdev_notifier_info_to_extack (int /*<<< orphan*/ *) ; 
 scalar_t__ netif_is_macvlan (struct net_device*) ; 

int mlxsw_sp_netdevice_vrf_event(struct net_device *l3_dev, unsigned long event,
				 struct netdev_notifier_changeupper_info *info)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_lower_get(l3_dev);
	int err = 0;

	/* We do not create a RIF for a macvlan, but only use it to
	 * direct more MAC addresses to the router.
	 */
	if (!mlxsw_sp || netif_is_macvlan(l3_dev))
		return 0;

	switch (event) {
	case NETDEV_PRECHANGEUPPER:
		return 0;
	case NETDEV_CHANGEUPPER:
		if (info->linking) {
			struct netlink_ext_ack *extack;

			extack = netdev_notifier_info_to_extack(&info->info);
			err = mlxsw_sp_port_vrf_join(mlxsw_sp, l3_dev, extack);
		} else {
			mlxsw_sp_port_vrf_leave(mlxsw_sp, l3_dev);
		}
		break;
	}

	return err;
}