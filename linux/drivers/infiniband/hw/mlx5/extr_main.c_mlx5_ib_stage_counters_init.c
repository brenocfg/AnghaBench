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
struct mlx5_ib_dev {int /*<<< orphan*/  ib_dev; int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 scalar_t__ MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_set_device_ops (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  max_qp_cnt ; 
 int mlx5_ib_alloc_counters (struct mlx5_ib_dev*) ; 
 int /*<<< orphan*/  mlx5_ib_dev_hw_stats_ops ; 

__attribute__((used)) static int mlx5_ib_stage_counters_init(struct mlx5_ib_dev *dev)
{
	if (MLX5_CAP_GEN(dev->mdev, max_qp_cnt)) {
		ib_set_device_ops(&dev->ib_dev, &mlx5_ib_dev_hw_stats_ops);

		return mlx5_ib_alloc_counters(dev);
	}

	return 0;
}