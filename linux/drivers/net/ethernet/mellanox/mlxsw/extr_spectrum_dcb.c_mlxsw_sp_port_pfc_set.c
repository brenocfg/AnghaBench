#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  rx_pause; } ;
struct mlxsw_sp_port {TYPE_2__* mlxsw_sp; TYPE_1__ link; int /*<<< orphan*/  local_port; } ;
struct ieee_pfc {int /*<<< orphan*/  pfc_en; } ;
struct TYPE_4__ {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PFCC_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_pfcc_pack (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_pfcc_pprx_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_pfcc_pptx_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_pfcc_prio_pack (char*,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pfcc ; 

__attribute__((used)) static int mlxsw_sp_port_pfc_set(struct mlxsw_sp_port *mlxsw_sp_port,
				 struct ieee_pfc *pfc)
{
	char pfcc_pl[MLXSW_REG_PFCC_LEN];

	mlxsw_reg_pfcc_pack(pfcc_pl, mlxsw_sp_port->local_port);
	mlxsw_reg_pfcc_pprx_set(pfcc_pl, mlxsw_sp_port->link.rx_pause);
	mlxsw_reg_pfcc_pptx_set(pfcc_pl, mlxsw_sp_port->link.tx_pause);
	mlxsw_reg_pfcc_prio_pack(pfcc_pl, pfc->pfc_en);

	return mlxsw_reg_write(mlxsw_sp_port->mlxsw_sp->core, MLXSW_REG(pfcc),
			       pfcc_pl);
}