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
struct mlxsw_sp_rif_params {int /*<<< orphan*/  system_port; int /*<<< orphan*/  lag_id; int /*<<< orphan*/  lag; int /*<<< orphan*/  vid; } ;
struct mlxsw_sp_port_vlan {int /*<<< orphan*/  vid; struct mlxsw_sp_port* mlxsw_sp_port; } ;
struct mlxsw_sp_port {int /*<<< orphan*/  local_port; int /*<<< orphan*/  lag_id; int /*<<< orphan*/  lagged; } ;

/* Variables and functions */

__attribute__((used)) static void
mlxsw_sp_rif_subport_params_init(struct mlxsw_sp_rif_params *params,
				 struct mlxsw_sp_port_vlan *mlxsw_sp_port_vlan)
{
	struct mlxsw_sp_port *mlxsw_sp_port = mlxsw_sp_port_vlan->mlxsw_sp_port;

	params->vid = mlxsw_sp_port_vlan->vid;
	params->lag = mlxsw_sp_port->lagged;
	if (params->lag)
		params->lag_id = mlxsw_sp_port->lag_id;
	else
		params->system_port = mlxsw_sp_port->local_port;
}