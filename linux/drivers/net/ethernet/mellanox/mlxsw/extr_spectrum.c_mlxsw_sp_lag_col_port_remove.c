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
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp_port {int /*<<< orphan*/  local_port; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_SLCOR_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_slcor_port_remove_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  slcor ; 

__attribute__((used)) static int mlxsw_sp_lag_col_port_remove(struct mlxsw_sp_port *mlxsw_sp_port,
					u16 lag_id)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	char slcor_pl[MLXSW_REG_SLCOR_LEN];

	mlxsw_reg_slcor_port_remove_pack(slcor_pl, mlxsw_sp_port->local_port,
					 lag_id);
	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(slcor), slcor_pl);
}