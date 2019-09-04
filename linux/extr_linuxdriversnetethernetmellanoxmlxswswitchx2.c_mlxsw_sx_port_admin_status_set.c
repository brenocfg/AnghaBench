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
struct mlxsw_sx_port {int /*<<< orphan*/  local_port; struct mlxsw_sx* mlxsw_sx; } ;
struct mlxsw_sx {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_PORT_ADMIN_STATUS_DOWN ; 
 int /*<<< orphan*/  MLXSW_PORT_ADMIN_STATUS_UP ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PAOS_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_paos_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  paos ; 

__attribute__((used)) static int mlxsw_sx_port_admin_status_set(struct mlxsw_sx_port *mlxsw_sx_port,
					  bool is_up)
{
	struct mlxsw_sx *mlxsw_sx = mlxsw_sx_port->mlxsw_sx;
	char paos_pl[MLXSW_REG_PAOS_LEN];

	mlxsw_reg_paos_pack(paos_pl, mlxsw_sx_port->local_port,
			    is_up ? MLXSW_PORT_ADMIN_STATUS_UP :
			    MLXSW_PORT_ADMIN_STATUS_DOWN);
	return mlxsw_reg_write(mlxsw_sx->core, MLXSW_REG(paos), paos_pl);
}