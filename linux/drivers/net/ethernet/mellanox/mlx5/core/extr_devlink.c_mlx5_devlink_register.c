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
struct devlink {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_params_publish (struct devlink*) ; 
 int devlink_params_register (struct devlink*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devlink_register (struct devlink*,struct device*) ; 
 int /*<<< orphan*/  devlink_unregister (struct devlink*) ; 
 int /*<<< orphan*/  mlx5_devlink_params ; 
 int /*<<< orphan*/  mlx5_devlink_set_params_init_values (struct devlink*) ; 

int mlx5_devlink_register(struct devlink *devlink, struct device *dev)
{
	int err;

	err = devlink_register(devlink, dev);
	if (err)
		return err;

	err = devlink_params_register(devlink, mlx5_devlink_params,
				      ARRAY_SIZE(mlx5_devlink_params));
	if (err)
		goto params_reg_err;
	mlx5_devlink_set_params_init_values(devlink);
	devlink_params_publish(devlink);
	return 0;

params_reg_err:
	devlink_unregister(devlink);
	return err;
}