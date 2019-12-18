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
struct mlxsw_sp_port {int /*<<< orphan*/  dev; } ;
struct dcb_ieee_app_prio_map {int dummy; } ;
struct dcb_ieee_app_dscp_map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_QPTS_TRUST_STATE_DSCP ; 
 int /*<<< orphan*/  MLXSW_REG_QPTS_TRUST_STATE_PCP ; 
 int /*<<< orphan*/  mlxsw_sp_port_dcb_app_default_prio (struct mlxsw_sp_port*) ; 
 int /*<<< orphan*/  mlxsw_sp_port_dcb_app_dscp_prio_map (struct mlxsw_sp_port*,int /*<<< orphan*/ ,struct dcb_ieee_app_dscp_map*) ; 
 int mlxsw_sp_port_dcb_app_prio_dscp_map (struct mlxsw_sp_port*,struct dcb_ieee_app_prio_map*) ; 
 int mlxsw_sp_port_dcb_app_update_qpdpm (struct mlxsw_sp_port*,struct dcb_ieee_app_dscp_map*) ; 
 int mlxsw_sp_port_dcb_app_update_qpdsm (struct mlxsw_sp_port*,struct dcb_ieee_app_prio_map*) ; 
 int mlxsw_sp_port_dcb_toggle_trust (struct mlxsw_sp_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mlxsw_sp_port_dcb_app_update(struct mlxsw_sp_port *mlxsw_sp_port)
{
	struct dcb_ieee_app_prio_map prio_map;
	struct dcb_ieee_app_dscp_map dscp_map;
	u8 default_prio;
	bool have_dscp;
	int err;

	default_prio = mlxsw_sp_port_dcb_app_default_prio(mlxsw_sp_port);
	have_dscp = mlxsw_sp_port_dcb_app_prio_dscp_map(mlxsw_sp_port,
							&prio_map);

	mlxsw_sp_port_dcb_app_dscp_prio_map(mlxsw_sp_port, default_prio,
					    &dscp_map);
	err = mlxsw_sp_port_dcb_app_update_qpdpm(mlxsw_sp_port,
						 &dscp_map);
	if (err) {
		netdev_err(mlxsw_sp_port->dev, "Couldn't configure priority map\n");
		return err;
	}

	err = mlxsw_sp_port_dcb_app_update_qpdsm(mlxsw_sp_port,
						 &prio_map);
	if (err) {
		netdev_err(mlxsw_sp_port->dev, "Couldn't configure DSCP rewrite map\n");
		return err;
	}

	if (!have_dscp) {
		err = mlxsw_sp_port_dcb_toggle_trust(mlxsw_sp_port,
					MLXSW_REG_QPTS_TRUST_STATE_PCP);
		if (err)
			netdev_err(mlxsw_sp_port->dev, "Couldn't switch to trust L2\n");
		return err;
	}

	err = mlxsw_sp_port_dcb_toggle_trust(mlxsw_sp_port,
					     MLXSW_REG_QPTS_TRUST_STATE_DSCP);
	if (err) {
		/* A failure to set trust DSCP means that the QPDPM and QPDSM
		 * maps installed above are not in effect. And since we are here
		 * attempting to set trust DSCP, we couldn't have attempted to
		 * switch trust to PCP. Thus no cleanup is necessary.
		 */
		netdev_err(mlxsw_sp_port->dev, "Couldn't switch to trust L3\n");
		return err;
	}

	return 0;
}