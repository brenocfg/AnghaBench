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
struct mlxsw_listener {int dummy; } ;
struct mlxsw_core {int dummy; } ;
struct devlink_trap {scalar_t__ id; } ;
typedef  enum mlxsw_reg_hpkt_action { ____Placeholder_mlxsw_reg_hpkt_action } mlxsw_reg_hpkt_action ;
typedef  enum devlink_trap_action { ____Placeholder_devlink_trap_action } devlink_trap_action ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
#define  DEVLINK_TRAP_ACTION_DROP 129 
#define  DEVLINK_TRAP_ACTION_TRAP 128 
 int EINVAL ; 
 int MLXSW_REG_HPKT_ACTION_SET_FW_DEFAULT ; 
 int MLXSW_REG_HPKT_ACTION_TRAP_EXCEPTION_TO_CPU ; 
 int mlxsw_core_trap_action_set (struct mlxsw_core*,struct mlxsw_listener*,int) ; 
 scalar_t__* mlxsw_sp_listener_devlink_map ; 
 struct mlxsw_listener* mlxsw_sp_listeners_arr ; 

int mlxsw_sp_trap_action_set(struct mlxsw_core *mlxsw_core,
			     const struct devlink_trap *trap,
			     enum devlink_trap_action action)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(mlxsw_sp_listener_devlink_map); i++) {
		enum mlxsw_reg_hpkt_action hw_action;
		struct mlxsw_listener *listener;
		int err;

		if (mlxsw_sp_listener_devlink_map[i] != trap->id)
			continue;
		listener = &mlxsw_sp_listeners_arr[i];

		switch (action) {
		case DEVLINK_TRAP_ACTION_DROP:
			hw_action = MLXSW_REG_HPKT_ACTION_SET_FW_DEFAULT;
			break;
		case DEVLINK_TRAP_ACTION_TRAP:
			hw_action = MLXSW_REG_HPKT_ACTION_TRAP_EXCEPTION_TO_CPU;
			break;
		default:
			return -EINVAL;
		}

		err = mlxsw_core_trap_action_set(mlxsw_core, listener,
						 hw_action);
		if (err)
			return err;
	}

	return 0;
}