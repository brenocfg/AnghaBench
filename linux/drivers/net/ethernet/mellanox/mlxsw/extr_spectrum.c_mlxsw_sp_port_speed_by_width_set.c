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
typedef  int u8 ;
typedef  int u32 ;
struct mlxsw_sp_port_type_speed_ops {int (* port_speed_base ) (struct mlxsw_sp*,int /*<<< orphan*/ ,int*) ;int (* to_ptys_upper_speed ) (struct mlxsw_sp*,int) ;int /*<<< orphan*/  (* reg_ptys_eth_pack ) (struct mlxsw_sp*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  autoneg; } ;
struct mlxsw_sp_port {TYPE_1__ link; int /*<<< orphan*/  local_port; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; struct mlxsw_sp_port_type_speed_ops* port_type_speed_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PTYS_LEN ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ptys ; 
 int stub1 (struct mlxsw_sp*,int /*<<< orphan*/ ,int*) ; 
 int stub2 (struct mlxsw_sp*,int) ; 
 int /*<<< orphan*/  stub3 (struct mlxsw_sp*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mlxsw_sp_port_speed_by_width_set(struct mlxsw_sp_port *mlxsw_sp_port, u8 width)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	const struct mlxsw_sp_port_type_speed_ops *ops;
	char ptys_pl[MLXSW_REG_PTYS_LEN];
	u32 eth_proto_admin;
	u32 upper_speed;
	u32 base_speed;
	int err;

	ops = mlxsw_sp->port_type_speed_ops;

	err = ops->port_speed_base(mlxsw_sp, mlxsw_sp_port->local_port,
				   &base_speed);
	if (err)
		return err;
	upper_speed = base_speed * width;

	eth_proto_admin = ops->to_ptys_upper_speed(mlxsw_sp, upper_speed);
	ops->reg_ptys_eth_pack(mlxsw_sp, ptys_pl, mlxsw_sp_port->local_port,
			       eth_proto_admin, mlxsw_sp_port->link.autoneg);
	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(ptys), ptys_pl);
}