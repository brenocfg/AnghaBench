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
struct mlxsw_sx {struct mlxsw_bus_info const* bus_info; struct mlxsw_core* core; } ;
struct mlxsw_core {int dummy; } ;
struct mlxsw_bus_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct mlxsw_sx* mlxsw_core_driver_priv (struct mlxsw_core*) ; 
 int mlxsw_sx_flood_init (struct mlxsw_sx*) ; 
 int mlxsw_sx_hw_id_get (struct mlxsw_sx*) ; 
 int mlxsw_sx_ports_create (struct mlxsw_sx*) ; 
 int /*<<< orphan*/  mlxsw_sx_ports_remove (struct mlxsw_sx*) ; 
 int /*<<< orphan*/  mlxsw_sx_traps_fini (struct mlxsw_sx*) ; 
 int mlxsw_sx_traps_init (struct mlxsw_sx*) ; 

__attribute__((used)) static int mlxsw_sx_init(struct mlxsw_core *mlxsw_core,
			 const struct mlxsw_bus_info *mlxsw_bus_info)
{
	struct mlxsw_sx *mlxsw_sx = mlxsw_core_driver_priv(mlxsw_core);
	int err;

	mlxsw_sx->core = mlxsw_core;
	mlxsw_sx->bus_info = mlxsw_bus_info;

	err = mlxsw_sx_hw_id_get(mlxsw_sx);
	if (err) {
		dev_err(mlxsw_sx->bus_info->dev, "Failed to get switch HW ID\n");
		return err;
	}

	err = mlxsw_sx_ports_create(mlxsw_sx);
	if (err) {
		dev_err(mlxsw_sx->bus_info->dev, "Failed to create ports\n");
		return err;
	}

	err = mlxsw_sx_traps_init(mlxsw_sx);
	if (err) {
		dev_err(mlxsw_sx->bus_info->dev, "Failed to set traps\n");
		goto err_listener_register;
	}

	err = mlxsw_sx_flood_init(mlxsw_sx);
	if (err) {
		dev_err(mlxsw_sx->bus_info->dev, "Failed to initialize flood tables\n");
		goto err_flood_init;
	}

	return 0;

err_flood_init:
	mlxsw_sx_traps_fini(mlxsw_sx);
err_listener_register:
	mlxsw_sx_ports_remove(mlxsw_sx);
	return err;
}