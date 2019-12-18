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
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_add_dev_by_protocol (struct mlx5_core_dev*,int) ; 
 scalar_t__ mlx5_has_added_dev_by_protocol (struct mlx5_core_dev*,int) ; 
 int /*<<< orphan*/  mlx5_intf_mutex ; 
 int /*<<< orphan*/  mlx5_remove_dev_by_protocol (struct mlx5_core_dev*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void mlx5_reload_interface(struct mlx5_core_dev *mdev, int protocol)
{
	mutex_lock(&mlx5_intf_mutex);
	if (mlx5_has_added_dev_by_protocol(mdev, protocol)) {
		mlx5_remove_dev_by_protocol(mdev, protocol);
		mlx5_add_dev_by_protocol(mdev, protocol);
	}
	mutex_unlock(&mlx5_intf_mutex);
}