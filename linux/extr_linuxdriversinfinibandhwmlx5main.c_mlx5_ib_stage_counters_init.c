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
struct TYPE_2__ {int /*<<< orphan*/  alloc_hw_stats; int /*<<< orphan*/  get_hw_stats; } ;
struct mlx5_ib_dev {TYPE_1__ ib_dev; int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 scalar_t__ MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_qp_cnt ; 
 int mlx5_ib_alloc_counters (struct mlx5_ib_dev*) ; 
 int /*<<< orphan*/  mlx5_ib_alloc_hw_stats ; 
 int /*<<< orphan*/  mlx5_ib_get_hw_stats ; 

int mlx5_ib_stage_counters_init(struct mlx5_ib_dev *dev)
{
	if (MLX5_CAP_GEN(dev->mdev, max_qp_cnt)) {
		dev->ib_dev.get_hw_stats	= mlx5_ib_get_hw_stats;
		dev->ib_dev.alloc_hw_stats	= mlx5_ib_alloc_hw_stats;

		return mlx5_ib_alloc_counters(dev);
	}

	return 0;
}