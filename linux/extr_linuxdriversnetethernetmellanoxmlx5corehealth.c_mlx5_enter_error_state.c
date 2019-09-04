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
struct mlx5_core_dev {scalar_t__ state; int /*<<< orphan*/  intf_state_mutex; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 scalar_t__ MLX5_DEVICE_STATE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  MLX5_DEV_EVENT_SYS_ERROR ; 
 scalar_t__ in_fatal (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*) ; 
 int /*<<< orphan*/  mlx5_core_event (struct mlx5_core_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_channel_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trigger_cmd_completions (struct mlx5_core_dev*) ; 

void mlx5_enter_error_state(struct mlx5_core_dev *dev, bool force)
{
	mutex_lock(&dev->intf_state_mutex);
	if (dev->state == MLX5_DEVICE_STATE_INTERNAL_ERROR)
		goto unlock;

	mlx5_core_err(dev, "start\n");
	if (pci_channel_offline(dev->pdev) || in_fatal(dev) || force) {
		dev->state = MLX5_DEVICE_STATE_INTERNAL_ERROR;
		trigger_cmd_completions(dev);
	}

	mlx5_core_event(dev, MLX5_DEV_EVENT_SYS_ERROR, 1);
	mlx5_core_err(dev, "end\n");

unlock:
	mutex_unlock(&dev->intf_state_mutex);
}