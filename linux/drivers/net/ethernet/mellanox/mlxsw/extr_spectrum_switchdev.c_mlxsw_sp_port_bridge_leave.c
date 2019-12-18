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
struct net_device {int dummy; } ;
struct mlxsw_sp_port {struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp_bridge_port {int dummy; } ;
struct mlxsw_sp_bridge_device {TYPE_1__* ops; } ;
struct mlxsw_sp {int /*<<< orphan*/  bridge; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* port_leave ) (struct mlxsw_sp_bridge_device*,struct mlxsw_sp_bridge_port*,struct mlxsw_sp_port*) ;} ;

/* Variables and functions */
 struct mlxsw_sp_bridge_port* __mlxsw_sp_bridge_port_find (struct mlxsw_sp_bridge_device*,struct net_device*) ; 
 struct mlxsw_sp_bridge_device* mlxsw_sp_bridge_device_find (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  mlxsw_sp_bridge_port_put (int /*<<< orphan*/ ,struct mlxsw_sp_bridge_port*) ; 
 int /*<<< orphan*/  stub1 (struct mlxsw_sp_bridge_device*,struct mlxsw_sp_bridge_port*,struct mlxsw_sp_port*) ; 

void mlxsw_sp_port_bridge_leave(struct mlxsw_sp_port *mlxsw_sp_port,
				struct net_device *brport_dev,
				struct net_device *br_dev)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	struct mlxsw_sp_bridge_device *bridge_device;
	struct mlxsw_sp_bridge_port *bridge_port;

	bridge_device = mlxsw_sp_bridge_device_find(mlxsw_sp->bridge, br_dev);
	if (!bridge_device)
		return;
	bridge_port = __mlxsw_sp_bridge_port_find(bridge_device, brport_dev);
	if (!bridge_port)
		return;

	bridge_device->ops->port_leave(bridge_device, bridge_port,
				       mlxsw_sp_port);
	mlxsw_sp_bridge_port_put(mlxsw_sp->bridge, bridge_port);
}