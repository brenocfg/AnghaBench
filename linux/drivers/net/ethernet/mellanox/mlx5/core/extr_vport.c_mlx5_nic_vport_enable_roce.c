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
struct TYPE_2__ {int /*<<< orphan*/  roce_en; } ;
struct mlx5_core_dev {TYPE_1__ roce; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_VPORT_ROCE_ENABLED ; 
 int mlx5_nic_vport_update_roce_state (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_roce_en_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mlx5_nic_vport_enable_roce(struct mlx5_core_dev *mdev)
{
	int err = 0;

	mutex_lock(&mlx5_roce_en_lock);
	if (!mdev->roce.roce_en)
		err = mlx5_nic_vport_update_roce_state(mdev, MLX5_VPORT_ROCE_ENABLED);

	if (!err)
		mdev->roce.roce_en++;
	mutex_unlock(&mlx5_roce_en_lock);

	return err;
}