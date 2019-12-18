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
typedef  int u8 ;
struct mlxsw_sp_port {int /*<<< orphan*/  local_port; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PMLP_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_pmlp_module_set (char*,int,int) ; 
 int /*<<< orphan*/  mlxsw_reg_pmlp_pack (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_pmlp_tx_lane_set (char*,int,int) ; 
 int /*<<< orphan*/  mlxsw_reg_pmlp_width_set (char*,int) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pmlp ; 

__attribute__((used)) static int mlxsw_sp_port_module_map(struct mlxsw_sp_port *mlxsw_sp_port,
				    u8 module, u8 width, u8 lane)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	char pmlp_pl[MLXSW_REG_PMLP_LEN];
	int i;

	mlxsw_reg_pmlp_pack(pmlp_pl, mlxsw_sp_port->local_port);
	mlxsw_reg_pmlp_width_set(pmlp_pl, width);
	for (i = 0; i < width; i++) {
		mlxsw_reg_pmlp_module_set(pmlp_pl, i, module);
		mlxsw_reg_pmlp_tx_lane_set(pmlp_pl, i, lane + i);  /* Rx & Tx */
	}

	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(pmlp), pmlp_pl);
}