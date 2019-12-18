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
struct mlxsw_core {TYPE_1__* bus; } ;
struct devlink {int dummy; } ;
struct TYPE_2__ {int features; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int MLXSW_BUS_F_RESET ; 
 struct mlxsw_core* devlink_priv (struct devlink*) ; 
 int /*<<< orphan*/  mlxsw_core_bus_device_unregister (struct mlxsw_core*,int) ; 

__attribute__((used)) static int
mlxsw_devlink_core_bus_device_reload_down(struct devlink *devlink,
					  struct netlink_ext_ack *extack)
{
	struct mlxsw_core *mlxsw_core = devlink_priv(devlink);

	if (!(mlxsw_core->bus->features & MLXSW_BUS_F_RESET))
		return -EOPNOTSUPP;

	mlxsw_core_bus_device_unregister(mlxsw_core, true);
	return 0;
}