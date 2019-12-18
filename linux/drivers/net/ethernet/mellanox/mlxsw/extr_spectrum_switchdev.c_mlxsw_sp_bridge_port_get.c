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
struct mlxsw_sp_bridge_port {int /*<<< orphan*/  ref_count; } ;
struct mlxsw_sp_bridge_device {int dummy; } ;
struct mlxsw_sp_bridge {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct mlxsw_sp_bridge_port* ERR_CAST (struct mlxsw_sp_bridge_device*) ; 
 struct mlxsw_sp_bridge_port* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct mlxsw_sp_bridge_device*) ; 
 struct mlxsw_sp_bridge_device* mlxsw_sp_bridge_device_get (struct mlxsw_sp_bridge*,struct net_device*) ; 
 int /*<<< orphan*/  mlxsw_sp_bridge_device_put (struct mlxsw_sp_bridge*,struct mlxsw_sp_bridge_device*) ; 
 struct mlxsw_sp_bridge_port* mlxsw_sp_bridge_port_create (struct mlxsw_sp_bridge_device*,struct net_device*) ; 
 struct mlxsw_sp_bridge_port* mlxsw_sp_bridge_port_find (struct mlxsw_sp_bridge*,struct net_device*) ; 
 struct net_device* netdev_master_upper_dev_get (struct net_device*) ; 

__attribute__((used)) static struct mlxsw_sp_bridge_port *
mlxsw_sp_bridge_port_get(struct mlxsw_sp_bridge *bridge,
			 struct net_device *brport_dev)
{
	struct net_device *br_dev = netdev_master_upper_dev_get(brport_dev);
	struct mlxsw_sp_bridge_device *bridge_device;
	struct mlxsw_sp_bridge_port *bridge_port;
	int err;

	bridge_port = mlxsw_sp_bridge_port_find(bridge, brport_dev);
	if (bridge_port) {
		bridge_port->ref_count++;
		return bridge_port;
	}

	bridge_device = mlxsw_sp_bridge_device_get(bridge, br_dev);
	if (IS_ERR(bridge_device))
		return ERR_CAST(bridge_device);

	bridge_port = mlxsw_sp_bridge_port_create(bridge_device, brport_dev);
	if (!bridge_port) {
		err = -ENOMEM;
		goto err_bridge_port_create;
	}

	return bridge_port;

err_bridge_port_create:
	mlxsw_sp_bridge_device_put(bridge, bridge_device);
	return ERR_PTR(err);
}