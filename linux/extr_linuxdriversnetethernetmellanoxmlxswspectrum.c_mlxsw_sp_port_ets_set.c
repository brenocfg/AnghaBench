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
typedef  int /*<<< orphan*/  u8 ;
struct mlxsw_sp_port {int /*<<< orphan*/  local_port; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
typedef  enum mlxsw_reg_qeec_hr { ____Placeholder_mlxsw_reg_qeec_hr } mlxsw_reg_qeec_hr ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_QEEC_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_qeec_de_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_qeec_dwrr_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_qeec_dwrr_weight_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_qeec_pack (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  qeec ; 

int mlxsw_sp_port_ets_set(struct mlxsw_sp_port *mlxsw_sp_port,
			  enum mlxsw_reg_qeec_hr hr, u8 index, u8 next_index,
			  bool dwrr, u8 dwrr_weight)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	char qeec_pl[MLXSW_REG_QEEC_LEN];

	mlxsw_reg_qeec_pack(qeec_pl, mlxsw_sp_port->local_port, hr, index,
			    next_index);
	mlxsw_reg_qeec_de_set(qeec_pl, true);
	mlxsw_reg_qeec_dwrr_set(qeec_pl, dwrr);
	mlxsw_reg_qeec_dwrr_weight_set(qeec_pl, dwrr_weight);
	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(qeec), qeec_pl);
}