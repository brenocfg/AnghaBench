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
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int devlink_traps_register (struct devlink*,int /*<<< orphan*/ ,scalar_t__,struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_listener_devlink_map ; 
 int /*<<< orphan*/  mlxsw_sp_listeners_arr ; 
 int /*<<< orphan*/  mlxsw_sp_traps_arr ; 
 struct devlink* priv_to_devlink (int /*<<< orphan*/ ) ; 

int mlxsw_sp_devlink_traps_init(struct mlxsw_sp *mlxsw_sp)
{
	struct devlink *devlink = priv_to_devlink(mlxsw_sp->core);

	if (WARN_ON(ARRAY_SIZE(mlxsw_sp_listener_devlink_map) !=
		    ARRAY_SIZE(mlxsw_sp_listeners_arr)))
		return -EINVAL;

	return devlink_traps_register(devlink, mlxsw_sp_traps_arr,
				      ARRAY_SIZE(mlxsw_sp_traps_arr),
				      mlxsw_sp);
}