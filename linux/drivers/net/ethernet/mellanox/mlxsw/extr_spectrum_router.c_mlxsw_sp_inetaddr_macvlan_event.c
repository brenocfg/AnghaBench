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
struct net_device {int dummy; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
#define  NETDEV_DOWN 129 
#define  NETDEV_UP 128 
 int mlxsw_sp_rif_macvlan_add (struct mlxsw_sp*,struct net_device*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  mlxsw_sp_rif_macvlan_del (struct mlxsw_sp*,struct net_device*) ; 

__attribute__((used)) static int mlxsw_sp_inetaddr_macvlan_event(struct mlxsw_sp *mlxsw_sp,
					   struct net_device *macvlan_dev,
					   unsigned long event,
					   struct netlink_ext_ack *extack)
{
	switch (event) {
	case NETDEV_UP:
		return mlxsw_sp_rif_macvlan_add(mlxsw_sp, macvlan_dev, extack);
	case NETDEV_DOWN:
		mlxsw_sp_rif_macvlan_del(mlxsw_sp, macvlan_dev);
		break;
	}

	return 0;
}