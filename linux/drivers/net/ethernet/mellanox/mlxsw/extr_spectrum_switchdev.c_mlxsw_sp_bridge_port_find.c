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
struct net_device {int dummy; } ;
struct mlxsw_sp_bridge_port {int dummy; } ;
struct mlxsw_sp_bridge_device {int dummy; } ;
struct mlxsw_sp_bridge {int dummy; } ;

/* Variables and functions */
 struct mlxsw_sp_bridge_port* __mlxsw_sp_bridge_port_find (struct mlxsw_sp_bridge_device*,struct net_device*) ; 
 struct mlxsw_sp_bridge_device* mlxsw_sp_bridge_device_find (struct mlxsw_sp_bridge*,struct net_device*) ; 
 struct net_device* netdev_master_upper_dev_get (struct net_device*) ; 

struct mlxsw_sp_bridge_port *
mlxsw_sp_bridge_port_find(struct mlxsw_sp_bridge *bridge,
			  struct net_device *brport_dev)
{
	struct net_device *br_dev = netdev_master_upper_dev_get(brport_dev);
	struct mlxsw_sp_bridge_device *bridge_device;

	if (!br_dev)
		return NULL;

	bridge_device = mlxsw_sp_bridge_device_find(bridge, br_dev);
	if (!bridge_device)
		return NULL;

	return __mlxsw_sp_bridge_port_find(bridge_device, brport_dev);
}