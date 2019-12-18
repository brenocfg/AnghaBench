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
union devlink_param_value {scalar_t__ vu32; } ;
struct mlxsw_core {int dummy; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_DEVLINK_PARAM_ID_ACL_REGION_REHASH_INTERVAL ; 
 int /*<<< orphan*/  devlink_param_driverinit_value_set (struct devlink*,int /*<<< orphan*/ ,union devlink_param_value) ; 
 int devlink_params_register (struct devlink*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp2_devlink_params ; 
 int mlxsw_sp_params_register (struct mlxsw_core*) ; 
 int /*<<< orphan*/  mlxsw_sp_params_unregister (struct mlxsw_core*) ; 
 struct devlink* priv_to_devlink (struct mlxsw_core*) ; 

__attribute__((used)) static int mlxsw_sp2_params_register(struct mlxsw_core *mlxsw_core)
{
	struct devlink *devlink = priv_to_devlink(mlxsw_core);
	union devlink_param_value value;
	int err;

	err = mlxsw_sp_params_register(mlxsw_core);
	if (err)
		return err;

	err = devlink_params_register(devlink, mlxsw_sp2_devlink_params,
				      ARRAY_SIZE(mlxsw_sp2_devlink_params));
	if (err)
		goto err_devlink_params_register;

	value.vu32 = 0;
	devlink_param_driverinit_value_set(devlink,
					   MLXSW_DEVLINK_PARAM_ID_ACL_REGION_REHASH_INTERVAL,
					   value);
	return 0;

err_devlink_params_register:
	mlxsw_sp_params_unregister(mlxsw_core);
	return err;
}