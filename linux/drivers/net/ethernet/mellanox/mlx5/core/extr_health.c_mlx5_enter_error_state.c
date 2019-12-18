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
struct TYPE_2__ {int /*<<< orphan*/  events; } ;
struct mlx5_core_dev {scalar_t__ state; int /*<<< orphan*/  intf_state_mutex; TYPE_1__ priv; } ;

/* Variables and functions */
 scalar_t__ MLX5_DEVICE_STATE_INTERNAL_ERROR ; 
 scalar_t__ MLX5_DEVICE_STATE_UNINITIALIZED ; 
 int /*<<< orphan*/  MLX5_DEV_EVENT_SYS_ERROR ; 
 scalar_t__ check_fatal_sensors (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_cmd_flush (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_notifier_call_chain (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void mlx5_enter_error_state(struct mlx5_core_dev *dev, bool force)
{
	mutex_lock(&dev->intf_state_mutex);
	if (dev->state == MLX5_DEVICE_STATE_INTERNAL_ERROR)
		goto unlock;
	if (dev->state == MLX5_DEVICE_STATE_UNINITIALIZED) {
		dev->state = MLX5_DEVICE_STATE_INTERNAL_ERROR;
		goto unlock;
	}

	if (check_fatal_sensors(dev) || force) {
		dev->state = MLX5_DEVICE_STATE_INTERNAL_ERROR;
		mlx5_cmd_flush(dev);
	}

	mlx5_notifier_call_chain(dev->priv.events, MLX5_DEV_EVENT_SYS_ERROR, (void *)1);
unlock:
	mutex_unlock(&dev->intf_state_mutex);
}