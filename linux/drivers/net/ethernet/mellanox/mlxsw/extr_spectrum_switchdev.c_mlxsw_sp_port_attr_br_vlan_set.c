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
struct switchdev_trans {int dummy; } ;
struct net_device {int dummy; } ;
struct mlxsw_sp_port {struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp_bridge_device {int vlan_enabled; int /*<<< orphan*/  dev; } ;
struct mlxsw_sp {int /*<<< orphan*/  bridge; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 struct mlxsw_sp_bridge_device* mlxsw_sp_bridge_device_find (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  switchdev_trans_ph_prepare (struct switchdev_trans*) ; 

__attribute__((used)) static int mlxsw_sp_port_attr_br_vlan_set(struct mlxsw_sp_port *mlxsw_sp_port,
					  struct switchdev_trans *trans,
					  struct net_device *orig_dev,
					  bool vlan_enabled)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	struct mlxsw_sp_bridge_device *bridge_device;

	if (!switchdev_trans_ph_prepare(trans))
		return 0;

	bridge_device = mlxsw_sp_bridge_device_find(mlxsw_sp->bridge, orig_dev);
	if (WARN_ON(!bridge_device))
		return -EINVAL;

	if (bridge_device->vlan_enabled == vlan_enabled)
		return 0;

	netdev_err(bridge_device->dev, "VLAN filtering can't be changed for existing bridge\n");
	return -EINVAL;
}