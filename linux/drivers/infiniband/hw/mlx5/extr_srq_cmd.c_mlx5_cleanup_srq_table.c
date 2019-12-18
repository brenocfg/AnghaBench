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
struct mlx5_srq_table {int /*<<< orphan*/  nb; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; struct mlx5_srq_table srq_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_notifier_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mlx5_cleanup_srq_table(struct mlx5_ib_dev *dev)
{
	struct mlx5_srq_table *table = &dev->srq_table;

	mlx5_notifier_unregister(dev->mdev, &table->nb);
}