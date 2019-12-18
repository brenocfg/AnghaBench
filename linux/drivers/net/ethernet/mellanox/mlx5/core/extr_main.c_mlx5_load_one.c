#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  embedded_cpu; } ;
struct mlx5_core_dev {int /*<<< orphan*/  intf_state_mutex; int /*<<< orphan*/  state; int /*<<< orphan*/  intf_state; TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_DEVICE_STATE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  MLX5_DEVICE_STATE_UP ; 
 int /*<<< orphan*/  MLX5_INTERFACE_STATE_UP ; 
 int /*<<< orphan*/  mlx5_attach_device (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_cleanup_once (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*,...) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*) ; 
 scalar_t__ mlx5_device_registered (struct mlx5_core_dev*) ; 
 int mlx5_function_setup (struct mlx5_core_dev*,int) ; 
 int /*<<< orphan*/  mlx5_function_teardown (struct mlx5_core_dev*,int) ; 
 int mlx5_init_once (struct mlx5_core_dev*) ; 
 int mlx5_load (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_read_embedded_cpu (struct mlx5_core_dev*) ; 
 int mlx5_register_device (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_unload (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5_load_one(struct mlx5_core_dev *dev, bool boot)
{
	int err = 0;

	dev->caps.embedded_cpu = mlx5_read_embedded_cpu(dev);
	mutex_lock(&dev->intf_state_mutex);
	if (test_bit(MLX5_INTERFACE_STATE_UP, &dev->intf_state)) {
		mlx5_core_warn(dev, "interface is up, NOP\n");
		goto out;
	}
	/* remove any previous indication of internal error */
	dev->state = MLX5_DEVICE_STATE_UP;

	err = mlx5_function_setup(dev, boot);
	if (err)
		goto out;

	if (boot) {
		err = mlx5_init_once(dev);
		if (err) {
			mlx5_core_err(dev, "sw objs init failed\n");
			goto function_teardown;
		}
	}

	err = mlx5_load(dev);
	if (err)
		goto err_load;

	if (mlx5_device_registered(dev)) {
		mlx5_attach_device(dev);
	} else {
		err = mlx5_register_device(dev);
		if (err) {
			mlx5_core_err(dev, "register device failed %d\n", err);
			goto err_reg_dev;
		}
	}

	set_bit(MLX5_INTERFACE_STATE_UP, &dev->intf_state);
out:
	mutex_unlock(&dev->intf_state_mutex);

	return err;

err_reg_dev:
	mlx5_unload(dev);
err_load:
	if (boot)
		mlx5_cleanup_once(dev);
function_teardown:
	mlx5_function_teardown(dev, boot);
	dev->state = MLX5_DEVICE_STATE_INTERNAL_ERROR;
	mutex_unlock(&dev->intf_state_mutex);

	return err;
}