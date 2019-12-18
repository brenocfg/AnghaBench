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
struct dcb_ieee_app_prio_map {int /*<<< orphan*/ * map; } ;

/* Variables and functions */
 short ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_QPDSM_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_qpdsm_pack (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_qpdsm_prio_pack (char*,short,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  qpdsm ; 

__attribute__((used)) static int
mlxsw_sp_port_dcb_app_update_qpdsm(struct mlxsw_sp_port *mlxsw_sp_port,
				   struct dcb_ieee_app_prio_map *map)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	char qpdsm_pl[MLXSW_REG_QPDSM_LEN];
	short int i;

	mlxsw_reg_qpdsm_pack(qpdsm_pl, mlxsw_sp_port->local_port);
	for (i = 0; i < ARRAY_SIZE(map->map); ++i)
		mlxsw_reg_qpdsm_prio_pack(qpdsm_pl, i, map->map[i]);
	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(qpdsm), qpdsm_pl);
}