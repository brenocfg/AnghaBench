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
struct mlxsw_sp_port {int /*<<< orphan*/  local_port; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
struct dcb_ieee_app_dscp_map {int /*<<< orphan*/ * map; } ;

/* Variables and functions */
 short ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_QPDPM_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_qpdpm_dscp_pack (char*,short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_qpdpm_pack (char*,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  qpdpm ; 

__attribute__((used)) static int
mlxsw_sp_port_dcb_app_update_qpdpm(struct mlxsw_sp_port *mlxsw_sp_port,
				   struct dcb_ieee_app_dscp_map *map)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	char qpdpm_pl[MLXSW_REG_QPDPM_LEN];
	short int i;

	mlxsw_reg_qpdpm_pack(qpdpm_pl, mlxsw_sp_port->local_port);
	for (i = 0; i < ARRAY_SIZE(map->map); ++i)
		mlxsw_reg_qpdpm_dscp_pack(qpdpm_pl, i, map->map[i]);
	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(qpdpm), qpdpm_pl);
}