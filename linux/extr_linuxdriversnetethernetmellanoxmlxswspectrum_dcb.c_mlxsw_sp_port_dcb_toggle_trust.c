#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int trust_state; } ;
struct mlxsw_sp_port {TYPE_1__ dcb; } ;
typedef  enum mlxsw_reg_qpts_trust_state { ____Placeholder_mlxsw_reg_qpts_trust_state } mlxsw_reg_qpts_trust_state ;

/* Variables and functions */
 int MLXSW_REG_QPTS_TRUST_STATE_DSCP ; 
 int mlxsw_sp_port_dcb_app_update_qpts (struct mlxsw_sp_port*,int) ; 
 int mlxsw_sp_port_dcb_app_update_qrwe (struct mlxsw_sp_port*,int) ; 

__attribute__((used)) static int
mlxsw_sp_port_dcb_toggle_trust(struct mlxsw_sp_port *mlxsw_sp_port,
			       enum mlxsw_reg_qpts_trust_state ts)
{
	bool rewrite_dscp = ts == MLXSW_REG_QPTS_TRUST_STATE_DSCP;
	int err;

	if (mlxsw_sp_port->dcb.trust_state == ts)
		return 0;

	err = mlxsw_sp_port_dcb_app_update_qpts(mlxsw_sp_port, ts);
	if (err)
		return err;

	err = mlxsw_sp_port_dcb_app_update_qrwe(mlxsw_sp_port, rewrite_dscp);
	if (err)
		goto err_update_qrwe;

	mlxsw_sp_port->dcb.trust_state = ts;
	return 0;

err_update_qrwe:
	mlxsw_sp_port_dcb_app_update_qpts(mlxsw_sp_port,
					  mlxsw_sp_port->dcb.trust_state);
	return err;
}