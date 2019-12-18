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
struct mlxsw_bus_info {int dummy; } ;
struct mlxsw_bus {int dummy; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int __mlxsw_core_bus_device_register (struct mlxsw_bus_info const*,struct mlxsw_bus const*,void*,int,struct devlink*) ; 

int mlxsw_core_bus_device_register(const struct mlxsw_bus_info *mlxsw_bus_info,
				   const struct mlxsw_bus *mlxsw_bus,
				   void *bus_priv, bool reload,
				   struct devlink *devlink)
{
	bool called_again = false;
	int err;

again:
	err = __mlxsw_core_bus_device_register(mlxsw_bus_info, mlxsw_bus,
					       bus_priv, reload, devlink);
	/* -EAGAIN is returned in case the FW was updated. FW needs
	 * a reset, so lets try to call __mlxsw_core_bus_device_register()
	 * again.
	 */
	if (err == -EAGAIN && !called_again) {
		called_again = true;
		goto again;
	}

	return err;
}