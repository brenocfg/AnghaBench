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

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_QRWE_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_qrwe_pack (char*,int /*<<< orphan*/ ,int,int) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  qrwe ; 

__attribute__((used)) static int
mlxsw_sp_port_dcb_app_update_qrwe(struct mlxsw_sp_port *mlxsw_sp_port,
				  bool rewrite_dscp)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	char qrwe_pl[MLXSW_REG_QRWE_LEN];

	mlxsw_reg_qrwe_pack(qrwe_pl, mlxsw_sp_port->local_port,
			    false, rewrite_dscp);
	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(qrwe), qrwe_pl);
}