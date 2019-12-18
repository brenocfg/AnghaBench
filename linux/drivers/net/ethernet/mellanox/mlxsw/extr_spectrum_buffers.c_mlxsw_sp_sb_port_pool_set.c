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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct netlink_ext_ack {int dummy; } ;
struct mlxsw_sp_port {scalar_t__ local_port; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int dummy; } ;
struct mlxsw_core_port {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MLXSW_PORT_CPU_PORT ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 struct mlxsw_sp_port* mlxsw_core_port_driver_priv (struct mlxsw_core_port*) ; 
 int mlxsw_sp_sb_pm_write (struct mlxsw_sp*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_sb_threshold_in (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct netlink_ext_ack*) ; 

int mlxsw_sp_sb_port_pool_set(struct mlxsw_core_port *mlxsw_core_port,
			      unsigned int sb_index, u16 pool_index,
			      u32 threshold, struct netlink_ext_ack *extack)
{
	struct mlxsw_sp_port *mlxsw_sp_port =
			mlxsw_core_port_driver_priv(mlxsw_core_port);
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	u8 local_port = mlxsw_sp_port->local_port;
	u32 max_buff;
	int err;

	if (local_port == MLXSW_PORT_CPU_PORT) {
		NL_SET_ERR_MSG_MOD(extack, "Changing CPU port's threshold is forbidden");
		return -EINVAL;
	}

	err = mlxsw_sp_sb_threshold_in(mlxsw_sp, pool_index,
				       threshold, &max_buff, extack);
	if (err)
		return err;

	return mlxsw_sp_sb_pm_write(mlxsw_sp, local_port, pool_index,
				    0, max_buff);
}