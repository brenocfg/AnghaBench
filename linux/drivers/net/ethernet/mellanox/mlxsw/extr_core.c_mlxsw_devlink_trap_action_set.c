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
struct mlxsw_driver {int (* trap_action_set ) (struct mlxsw_core*,struct devlink_trap const*,int) ;} ;
struct mlxsw_core {struct mlxsw_driver* driver; } ;
struct devlink_trap {int dummy; } ;
struct devlink {int dummy; } ;
typedef  enum devlink_trap_action { ____Placeholder_devlink_trap_action } devlink_trap_action ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct mlxsw_core* devlink_priv (struct devlink*) ; 
 int stub1 (struct mlxsw_core*,struct devlink_trap const*,int) ; 

__attribute__((used)) static int mlxsw_devlink_trap_action_set(struct devlink *devlink,
					 const struct devlink_trap *trap,
					 enum devlink_trap_action action)
{
	struct mlxsw_core *mlxsw_core = devlink_priv(devlink);
	struct mlxsw_driver *mlxsw_driver = mlxsw_core->driver;

	if (!mlxsw_driver->trap_action_set)
		return -EOPNOTSUPP;
	return mlxsw_driver->trap_action_set(mlxsw_core, trap, action);
}