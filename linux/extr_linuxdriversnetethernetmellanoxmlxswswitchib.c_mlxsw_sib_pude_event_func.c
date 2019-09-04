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
struct mlxsw_sib_port {int dummy; } ;
struct mlxsw_sib {TYPE_1__* bus_info; struct mlxsw_sib_port** ports; } ;
struct mlxsw_reg_info {int dummy; } ;
typedef  enum mlxsw_reg_pude_oper_status { ____Placeholder_mlxsw_reg_pude_oper_status } mlxsw_reg_pude_oper_status ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,size_t) ; 
 size_t mlxsw_reg_pude_local_port_get (char*) ; 
 int mlxsw_reg_pude_oper_status_get (char*) ; 
 int /*<<< orphan*/  mlxsw_sib_pude_ib_event_func (struct mlxsw_sib_port*,int) ; 

__attribute__((used)) static void mlxsw_sib_pude_event_func(const struct mlxsw_reg_info *reg,
				      char *pude_pl, void *priv)
{
	struct mlxsw_sib *mlxsw_sib = priv;
	struct mlxsw_sib_port *mlxsw_sib_port;
	enum mlxsw_reg_pude_oper_status status;
	u8 local_port;

	local_port = mlxsw_reg_pude_local_port_get(pude_pl);
	mlxsw_sib_port = mlxsw_sib->ports[local_port];
	if (!mlxsw_sib_port) {
		dev_warn(mlxsw_sib->bus_info->dev, "Port %d: Link event received for non-existent port\n",
			 local_port);
		return;
	}

	status = mlxsw_reg_pude_oper_status_get(pude_pl);
	mlxsw_sib_pude_ib_event_func(mlxsw_sib_port, status);
}