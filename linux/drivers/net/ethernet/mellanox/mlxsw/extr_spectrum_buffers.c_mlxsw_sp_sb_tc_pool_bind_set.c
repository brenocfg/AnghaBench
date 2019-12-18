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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  size_t u16 ;
struct netlink_ext_ack {int dummy; } ;
struct mlxsw_sp_sb_cm {size_t pool_index; scalar_t__ max_buff; scalar_t__ freeze_thresh; scalar_t__ freeze_pool; } ;
struct mlxsw_sp_port {scalar_t__ local_port; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {TYPE_2__* sb_vals; } ;
struct mlxsw_core_port {int dummy; } ;
typedef  enum mlxsw_reg_sbxx_dir { ____Placeholder_mlxsw_reg_sbxx_dir } mlxsw_reg_sbxx_dir ;
typedef  enum devlink_sb_pool_type { ____Placeholder_devlink_sb_pool_type } devlink_sb_pool_type ;
struct TYPE_4__ {struct mlxsw_sp_sb_cm* cms_egress; struct mlxsw_sp_sb_cm* cms_ingress; TYPE_1__* pool_dess; } ;
struct TYPE_3__ {int dir; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MLXSW_PORT_CPU_PORT ; 
 int MLXSW_REG_SBXX_DIR_INGRESS ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 struct mlxsw_sp_port* mlxsw_core_port_driver_priv (struct mlxsw_core_port*) ; 
 int mlxsw_sp_sb_cm_write (struct mlxsw_sp*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int,size_t) ; 
 int mlxsw_sp_sb_threshold_in (struct mlxsw_sp*,size_t,scalar_t__,scalar_t__*,struct netlink_ext_ack*) ; 

int mlxsw_sp_sb_tc_pool_bind_set(struct mlxsw_core_port *mlxsw_core_port,
				 unsigned int sb_index, u16 tc_index,
				 enum devlink_sb_pool_type pool_type,
				 u16 pool_index, u32 threshold,
				 struct netlink_ext_ack *extack)
{
	struct mlxsw_sp_port *mlxsw_sp_port =
			mlxsw_core_port_driver_priv(mlxsw_core_port);
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	u8 local_port = mlxsw_sp_port->local_port;
	const struct mlxsw_sp_sb_cm *cm;
	u8 pg_buff = tc_index;
	enum mlxsw_reg_sbxx_dir dir = (enum mlxsw_reg_sbxx_dir) pool_type;
	u32 max_buff;
	int err;

	if (local_port == MLXSW_PORT_CPU_PORT) {
		NL_SET_ERR_MSG_MOD(extack, "Changing CPU port's binding is forbidden");
		return -EINVAL;
	}

	if (dir != mlxsw_sp->sb_vals->pool_dess[pool_index].dir) {
		NL_SET_ERR_MSG_MOD(extack, "Binding egress TC to ingress pool and vice versa is forbidden");
		return -EINVAL;
	}

	if (dir == MLXSW_REG_SBXX_DIR_INGRESS)
		cm = &mlxsw_sp->sb_vals->cms_ingress[tc_index];
	else
		cm = &mlxsw_sp->sb_vals->cms_egress[tc_index];

	if (cm->freeze_pool && cm->pool_index != pool_index) {
		NL_SET_ERR_MSG_MOD(extack, "Binding this TC to a different pool is forbidden");
		return -EINVAL;
	}

	if (cm->freeze_thresh && cm->max_buff != threshold) {
		NL_SET_ERR_MSG_MOD(extack, "Changing this TC's threshold is forbidden");
		return -EINVAL;
	}

	err = mlxsw_sp_sb_threshold_in(mlxsw_sp, pool_index,
				       threshold, &max_buff, extack);
	if (err)
		return err;

	return mlxsw_sp_sb_cm_write(mlxsw_sp, local_port, pg_buff,
				    0, max_buff, false, pool_index);
}