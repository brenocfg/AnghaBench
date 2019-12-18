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
union devlink_param_value {int /*<<< orphan*/  vu8; } ;
struct mlxsw_core {int dummy; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEVLINK_PARAM_FW_LOAD_POLICY_VALUE_DRIVER ; 
 int /*<<< orphan*/  DEVLINK_PARAM_GENERIC_ID_FW_LOAD_POLICY ; 
 int /*<<< orphan*/  devlink_param_driverinit_value_set (struct devlink*,int /*<<< orphan*/ ,union devlink_param_value) ; 
 int devlink_params_register (struct devlink*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_devlink_params ; 
 struct devlink* priv_to_devlink (struct mlxsw_core*) ; 

__attribute__((used)) static int mlxsw_sp_params_register(struct mlxsw_core *mlxsw_core)
{
	struct devlink *devlink = priv_to_devlink(mlxsw_core);
	union devlink_param_value value;
	int err;

	err = devlink_params_register(devlink, mlxsw_sp_devlink_params,
				      ARRAY_SIZE(mlxsw_sp_devlink_params));
	if (err)
		return err;

	value.vu8 = DEVLINK_PARAM_FW_LOAD_POLICY_VALUE_DRIVER;
	devlink_param_driverinit_value_set(devlink,
					   DEVLINK_PARAM_GENERIC_ID_FW_LOAD_POLICY,
					   value);
	return 0;
}