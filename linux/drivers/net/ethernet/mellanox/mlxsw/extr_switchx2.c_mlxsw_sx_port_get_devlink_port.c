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
struct mlxsw_sx_port {int /*<<< orphan*/  local_port; struct mlxsw_sx* mlxsw_sx; } ;
struct mlxsw_sx {int /*<<< orphan*/  core; } ;
struct devlink_port {int dummy; } ;

/* Variables and functions */
 struct devlink_port* mlxsw_core_port_devlink_port_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlxsw_sx_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static struct devlink_port *
mlxsw_sx_port_get_devlink_port(struct net_device *dev)
{
	struct mlxsw_sx_port *mlxsw_sx_port = netdev_priv(dev);
	struct mlxsw_sx *mlxsw_sx = mlxsw_sx_port->mlxsw_sx;

	return mlxsw_core_port_devlink_port_get(mlxsw_sx->core,
						mlxsw_sx_port->local_port);
}