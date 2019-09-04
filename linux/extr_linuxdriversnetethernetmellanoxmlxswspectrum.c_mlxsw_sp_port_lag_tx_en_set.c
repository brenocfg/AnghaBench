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
 int mlxsw_sp_lag_dist_port_add (struct mlxsw_sp_port*,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_lag_dist_port_remove (struct mlxsw_sp_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sp_port_lag_tx_en_set(struct mlxsw_sp_port *mlxsw_sp_port,
				       bool lag_tx_enabled)
{
	if (lag_tx_enabled)
		return mlxsw_sp_lag_dist_port_add(mlxsw_sp_port,
						  mlxsw_sp_port->lag_id);
	else
		return mlxsw_sp_lag_dist_port_remove(mlxsw_sp_port,
						     mlxsw_sp_port->lag_id);
}