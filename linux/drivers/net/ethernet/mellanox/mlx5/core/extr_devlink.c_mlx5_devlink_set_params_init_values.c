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
union devlink_param_value {int /*<<< orphan*/  vstr; } ;
struct TYPE_4__ {TYPE_1__* steering; } ;
struct mlx5_core_dev {TYPE_2__ priv; } ;
struct devlink {int dummy; } ;
struct TYPE_3__ {scalar_t__ mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_DEVLINK_PARAM_FLOW_STEERING_MODE ; 
 scalar_t__ MLX5_FLOW_STEERING_MODE_DMFS ; 
 int /*<<< orphan*/  devlink_param_driverinit_value_set (struct devlink*,int /*<<< orphan*/ ,union devlink_param_value) ; 
 struct mlx5_core_dev* devlink_priv (struct devlink*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void mlx5_devlink_set_params_init_values(struct devlink *devlink)
{
	struct mlx5_core_dev *dev = devlink_priv(devlink);
	union devlink_param_value value;

	if (dev->priv.steering->mode == MLX5_FLOW_STEERING_MODE_DMFS)
		strcpy(value.vstr, "dmfs");
	else
		strcpy(value.vstr, "smfs");
	devlink_param_driverinit_value_set(devlink,
					   MLX5_DEVLINK_PARAM_FLOW_STEERING_MODE,
					   value);
}