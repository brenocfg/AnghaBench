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
struct mlxsw_sp {int dummy; } ;
struct mlxsw_core {int dummy; } ;
struct devlink_trap_group {int dummy; } ;

/* Variables and functions */
 int __mlxsw_sp_trap_group_init (struct mlxsw_sp*,struct devlink_trap_group const*) ; 
 struct mlxsw_sp* mlxsw_core_driver_priv (struct mlxsw_core*) ; 
 int mlxsw_sp_trap_group_policer_init (struct mlxsw_sp*,struct devlink_trap_group const*) ; 

int mlxsw_sp_trap_group_init(struct mlxsw_core *mlxsw_core,
			     const struct devlink_trap_group *group)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_core_driver_priv(mlxsw_core);
	int err;

	err = mlxsw_sp_trap_group_policer_init(mlxsw_sp, group);
	if (err)
		return err;

	err = __mlxsw_sp_trap_group_init(mlxsw_sp, group);
	if (err)
		return err;

	return 0;
}