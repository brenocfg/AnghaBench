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
struct net_device {int dummy; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int __mlxsw_sp_inetaddr_lag_event (struct net_device*,struct net_device*,unsigned long,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 scalar_t__ br_vlan_enabled (struct net_device*) ; 
 int mlxsw_sp_inetaddr_bridge_event (struct mlxsw_sp*,struct net_device*,unsigned long,struct netlink_ext_ack*) ; 
 int mlxsw_sp_inetaddr_port_vlan_event (struct net_device*,struct net_device*,unsigned long,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 scalar_t__ mlxsw_sp_port_dev_check (struct net_device*) ; 
 scalar_t__ netif_is_bridge_master (struct net_device*) ; 
 scalar_t__ netif_is_bridge_port (struct net_device*) ; 
 scalar_t__ netif_is_lag_master (struct net_device*) ; 
 struct net_device* vlan_dev_real_dev (struct net_device*) ; 
 int /*<<< orphan*/  vlan_dev_vlan_id (struct net_device*) ; 

__attribute__((used)) static int mlxsw_sp_inetaddr_vlan_event(struct mlxsw_sp *mlxsw_sp,
					struct net_device *vlan_dev,
					unsigned long event,
					struct netlink_ext_ack *extack)
{
	struct net_device *real_dev = vlan_dev_real_dev(vlan_dev);
	u16 vid = vlan_dev_vlan_id(vlan_dev);

	if (netif_is_bridge_port(vlan_dev))
		return 0;

	if (mlxsw_sp_port_dev_check(real_dev))
		return mlxsw_sp_inetaddr_port_vlan_event(vlan_dev, real_dev,
							 event, vid, extack);
	else if (netif_is_lag_master(real_dev))
		return __mlxsw_sp_inetaddr_lag_event(vlan_dev, real_dev, event,
						     vid, extack);
	else if (netif_is_bridge_master(real_dev) && br_vlan_enabled(real_dev))
		return mlxsw_sp_inetaddr_bridge_event(mlxsw_sp, vlan_dev, event,
						      extack);

	return 0;
}