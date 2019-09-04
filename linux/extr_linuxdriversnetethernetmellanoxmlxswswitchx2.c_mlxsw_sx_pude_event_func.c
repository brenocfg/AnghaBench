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
typedef  size_t u8 ;
struct mlxsw_sx_port {int dummy; } ;
struct mlxsw_sx {int /*<<< orphan*/  core; TYPE_1__* bus_info; struct mlxsw_sx_port** ports; } ;
struct mlxsw_reg_info {int dummy; } ;
typedef  enum mlxsw_reg_pude_oper_status { ____Placeholder_mlxsw_reg_pude_oper_status } mlxsw_reg_pude_oper_status ;
typedef  enum devlink_port_type { ____Placeholder_devlink_port_type } devlink_port_type ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DEVLINK_PORT_TYPE_ETH ; 
 int DEVLINK_PORT_TYPE_IB ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,size_t) ; 
 int mlxsw_core_port_type_get (int /*<<< orphan*/ ,size_t) ; 
 size_t mlxsw_reg_pude_local_port_get (char*) ; 
 int mlxsw_reg_pude_oper_status_get (char*) ; 
 int /*<<< orphan*/  mlxsw_sx_pude_eth_event_func (struct mlxsw_sx_port*,int) ; 
 int /*<<< orphan*/  mlxsw_sx_pude_ib_event_func (struct mlxsw_sx_port*,int) ; 

__attribute__((used)) static void mlxsw_sx_pude_event_func(const struct mlxsw_reg_info *reg,
				     char *pude_pl, void *priv)
{
	struct mlxsw_sx *mlxsw_sx = priv;
	struct mlxsw_sx_port *mlxsw_sx_port;
	enum mlxsw_reg_pude_oper_status status;
	enum devlink_port_type port_type;
	u8 local_port;

	local_port = mlxsw_reg_pude_local_port_get(pude_pl);
	mlxsw_sx_port = mlxsw_sx->ports[local_port];
	if (!mlxsw_sx_port) {
		dev_warn(mlxsw_sx->bus_info->dev, "Port %d: Link event received for non-existent port\n",
			 local_port);
		return;
	}

	status = mlxsw_reg_pude_oper_status_get(pude_pl);
	port_type = mlxsw_core_port_type_get(mlxsw_sx->core, local_port);
	if (port_type == DEVLINK_PORT_TYPE_ETH)
		mlxsw_sx_pude_eth_event_func(mlxsw_sx_port, status);
	else if (port_type == DEVLINK_PORT_TYPE_IB)
		mlxsw_sx_pude_ib_event_func(mlxsw_sx_port, status);
}