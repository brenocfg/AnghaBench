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
struct mlxsw_sp_port {int /*<<< orphan*/  lag_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_lag_col_port_disable (struct mlxsw_sp_port*,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_lag_col_port_enable (struct mlxsw_sp_port*,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_lag_dist_port_add (struct mlxsw_sp_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mlxsw_sp_port_lag_col_dist_enable(struct mlxsw_sp_port *mlxsw_sp_port)
{
	int err;

	err = mlxsw_sp_lag_col_port_enable(mlxsw_sp_port,
					   mlxsw_sp_port->lag_id);
	if (err)
		return err;

	err = mlxsw_sp_lag_dist_port_add(mlxsw_sp_port, mlxsw_sp_port->lag_id);
	if (err)
		goto err_dist_port_add;

	return 0;

err_dist_port_add:
	mlxsw_sp_lag_col_port_disable(mlxsw_sp_port, mlxsw_sp_port->lag_id);
	return err;
}