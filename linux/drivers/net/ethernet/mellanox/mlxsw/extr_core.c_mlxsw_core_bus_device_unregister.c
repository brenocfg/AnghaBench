#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mapping; } ;
struct mlxsw_core {TYPE_3__* driver; int /*<<< orphan*/  bus_priv; TYPE_2__* bus; TYPE_1__ lag; int /*<<< orphan*/  hwmon; int /*<<< orphan*/  thermal; } ;
struct devlink {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* params_unregister ) (struct mlxsw_core*) ;int /*<<< orphan*/  (* fini ) (struct mlxsw_core*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* fini ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  devlink_free (struct devlink*) ; 
 scalar_t__ devlink_is_reload_failed (struct devlink*) ; 
 int /*<<< orphan*/  devlink_params_unpublish (struct devlink*) ; 
 int /*<<< orphan*/  devlink_resources_unregister (struct devlink*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devlink_unregister (struct devlink*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_emad_fini (struct mlxsw_core*) ; 
 int /*<<< orphan*/  mlxsw_hwmon_fini (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_ports_fini (struct mlxsw_core*) ; 
 int /*<<< orphan*/  mlxsw_thermal_fini (int /*<<< orphan*/ ) ; 
 struct devlink* priv_to_devlink (struct mlxsw_core*) ; 
 int /*<<< orphan*/  stub1 (struct mlxsw_core*) ; 
 int /*<<< orphan*/  stub2 (struct mlxsw_core*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct mlxsw_core*) ; 

void mlxsw_core_bus_device_unregister(struct mlxsw_core *mlxsw_core,
				      bool reload)
{
	struct devlink *devlink = priv_to_devlink(mlxsw_core);

	if (devlink_is_reload_failed(devlink)) {
		if (!reload)
			/* Only the parts that were not de-initialized in the
			 * failed reload attempt need to be de-initialized.
			 */
			goto reload_fail_deinit;
		else
			return;
	}

	if (mlxsw_core->driver->params_unregister)
		devlink_params_unpublish(devlink);
	mlxsw_thermal_fini(mlxsw_core->thermal);
	mlxsw_hwmon_fini(mlxsw_core->hwmon);
	if (mlxsw_core->driver->fini)
		mlxsw_core->driver->fini(mlxsw_core);
	if (mlxsw_core->driver->params_unregister && !reload)
		mlxsw_core->driver->params_unregister(mlxsw_core);
	if (!reload)
		devlink_unregister(devlink);
	mlxsw_emad_fini(mlxsw_core);
	kfree(mlxsw_core->lag.mapping);
	mlxsw_ports_fini(mlxsw_core);
	if (!reload)
		devlink_resources_unregister(devlink, NULL);
	mlxsw_core->bus->fini(mlxsw_core->bus_priv);

	return;

reload_fail_deinit:
	if (mlxsw_core->driver->params_unregister)
		mlxsw_core->driver->params_unregister(mlxsw_core);
	devlink_unregister(devlink);
	devlink_resources_unregister(devlink, NULL);
	devlink_free(devlink);
}