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
struct netdev_notifier_changeupper_info {int /*<<< orphan*/  info; } ;
struct net_device {int dummy; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 unsigned long NETDEV_PRECHANGEUPPER ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 struct mlxsw_sp* mlxsw_sp_lower_get (struct net_device*) ; 
 struct netlink_ext_ack* netdev_notifier_info_to_extack (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlxsw_sp_netdevice_macvlan_event(struct net_device *macvlan_dev,
					    unsigned long event, void *ptr)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_lower_get(macvlan_dev);
	struct netdev_notifier_changeupper_info *info = ptr;
	struct netlink_ext_ack *extack;

	if (!mlxsw_sp || event != NETDEV_PRECHANGEUPPER)
		return 0;

	extack = netdev_notifier_info_to_extack(&info->info);

	/* VRF enslavement is handled in mlxsw_sp_netdevice_vrf_event() */
	NL_SET_ERR_MSG_MOD(extack, "Unknown upper device type");

	return -EOPNOTSUPP;
}