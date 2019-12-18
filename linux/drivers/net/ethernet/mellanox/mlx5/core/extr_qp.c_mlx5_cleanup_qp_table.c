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
struct mlx5_qp_table {int /*<<< orphan*/  nb; } ;
struct TYPE_2__ {struct mlx5_qp_table qp_table; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_notifier_unregister (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_qp_debugfs_cleanup (struct mlx5_core_dev*) ; 

void mlx5_cleanup_qp_table(struct mlx5_core_dev *dev)
{
	struct mlx5_qp_table *table = &dev->priv.qp_table;

	mlx5_notifier_unregister(dev, &table->nb);
	mlx5_qp_debugfs_cleanup(dev);
}