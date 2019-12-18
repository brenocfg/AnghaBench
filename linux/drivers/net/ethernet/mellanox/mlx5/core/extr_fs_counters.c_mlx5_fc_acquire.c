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
struct mlx5_fc_stats {int /*<<< orphan*/  fc_pool; } ;
struct mlx5_fc {int dummy; } ;
struct TYPE_2__ {struct mlx5_fc_stats fc_stats; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct mlx5_fc*) ; 
 scalar_t__ MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_counter_bulk_alloc ; 
 struct mlx5_fc* mlx5_fc_pool_acquire_counter (int /*<<< orphan*/ *) ; 
 struct mlx5_fc* mlx5_fc_single_alloc (struct mlx5_core_dev*) ; 

__attribute__((used)) static struct mlx5_fc *mlx5_fc_acquire(struct mlx5_core_dev *dev, bool aging)
{
	struct mlx5_fc_stats *fc_stats = &dev->priv.fc_stats;
	struct mlx5_fc *counter;

	if (aging && MLX5_CAP_GEN(dev, flow_counter_bulk_alloc) != 0) {
		counter = mlx5_fc_pool_acquire_counter(&fc_stats->fc_pool);
		if (!IS_ERR(counter))
			return counter;
	}

	return mlx5_fc_single_alloc(dev);
}