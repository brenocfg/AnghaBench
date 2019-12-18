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
struct mlxsw_sib {struct mlxsw_bus_info const* bus_info; struct mlxsw_core* core; } ;
struct mlxsw_core {int dummy; } ;
struct mlxsw_bus_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct mlxsw_sib* mlxsw_core_driver_priv (struct mlxsw_core*) ; 
 int mlxsw_sib_hw_id_get (struct mlxsw_sib*) ; 
 int mlxsw_sib_ports_create (struct mlxsw_sib*) ; 
 int /*<<< orphan*/  mlxsw_sib_ports_remove (struct mlxsw_sib*) ; 
 int mlxsw_sib_taps_init (struct mlxsw_sib*) ; 

__attribute__((used)) static int mlxsw_sib_init(struct mlxsw_core *mlxsw_core,
			  const struct mlxsw_bus_info *mlxsw_bus_info)
{
	struct mlxsw_sib *mlxsw_sib = mlxsw_core_driver_priv(mlxsw_core);
	int err;

	mlxsw_sib->core = mlxsw_core;
	mlxsw_sib->bus_info = mlxsw_bus_info;

	err = mlxsw_sib_hw_id_get(mlxsw_sib);
	if (err) {
		dev_err(mlxsw_sib->bus_info->dev, "Failed to get switch HW ID\n");
		return err;
	}

	err = mlxsw_sib_ports_create(mlxsw_sib);
	if (err) {
		dev_err(mlxsw_sib->bus_info->dev, "Failed to create ports\n");
		return err;
	}

	err = mlxsw_sib_taps_init(mlxsw_sib);
	if (err) {
		dev_err(mlxsw_sib->bus_info->dev, "Failed to set traps\n");
		goto err_traps_init_err;
	}

	return 0;

err_traps_init_err:
	mlxsw_sib_ports_remove(mlxsw_sib);
	return err;
}