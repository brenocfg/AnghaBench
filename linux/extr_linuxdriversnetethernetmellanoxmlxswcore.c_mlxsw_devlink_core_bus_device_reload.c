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
struct netlink_ext_ack {int dummy; } ;
struct mlxsw_core {int reload_fail; int /*<<< orphan*/  bus_priv; TYPE_1__* bus; int /*<<< orphan*/  bus_info; } ;
struct devlink {int dummy; } ;
struct TYPE_2__ {int features; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int MLXSW_BUS_F_RESET ; 
 struct mlxsw_core* devlink_priv (struct devlink*) ; 
 int mlxsw_core_bus_device_register (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int,struct devlink*) ; 
 int /*<<< orphan*/  mlxsw_core_bus_device_unregister (struct mlxsw_core*,int) ; 

__attribute__((used)) static int mlxsw_devlink_core_bus_device_reload(struct devlink *devlink,
						struct netlink_ext_ack *extack)
{
	struct mlxsw_core *mlxsw_core = devlink_priv(devlink);
	int err;

	if (!(mlxsw_core->bus->features & MLXSW_BUS_F_RESET))
		return -EOPNOTSUPP;

	mlxsw_core_bus_device_unregister(mlxsw_core, true);
	err = mlxsw_core_bus_device_register(mlxsw_core->bus_info,
					     mlxsw_core->bus,
					     mlxsw_core->bus_priv, true,
					     devlink);
	mlxsw_core->reload_fail = !!err;

	return err;
}