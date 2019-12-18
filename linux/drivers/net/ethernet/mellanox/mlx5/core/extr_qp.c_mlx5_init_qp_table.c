#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  notifier_call; } ;
struct mlx5_qp_table {TYPE_2__ nb; int /*<<< orphan*/  tree; int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {struct mlx5_qp_table qp_table; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mlx5_qp_table*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_notifier_register (struct mlx5_core_dev*,TYPE_2__*) ; 
 int /*<<< orphan*/  mlx5_qp_debugfs_init (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  rsc_event_notifier ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void mlx5_init_qp_table(struct mlx5_core_dev *dev)
{
	struct mlx5_qp_table *table = &dev->priv.qp_table;

	memset(table, 0, sizeof(*table));
	spin_lock_init(&table->lock);
	INIT_RADIX_TREE(&table->tree, GFP_ATOMIC);
	mlx5_qp_debugfs_init(dev);

	table->nb.notifier_call = rsc_event_notifier;
	mlx5_notifier_register(dev, &table->nb);
}