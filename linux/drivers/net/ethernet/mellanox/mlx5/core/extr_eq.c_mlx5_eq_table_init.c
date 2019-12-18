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
struct mlx5_eq_table {int /*<<< orphan*/  irq_table; int /*<<< orphan*/ * nh; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq_table; struct mlx5_eq_table* eq_table; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_INIT_NOTIFIER_HEAD (int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLX5_EVENT_TYPE_MAX ; 
 struct mlx5_eq_table* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_eq_debugfs_init (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int mlx5_eq_table_init(struct mlx5_core_dev *dev)
{
	struct mlx5_eq_table *eq_table;
	int i;

	eq_table = kvzalloc(sizeof(*eq_table), GFP_KERNEL);
	if (!eq_table)
		return -ENOMEM;

	dev->priv.eq_table = eq_table;

	mlx5_eq_debugfs_init(dev);

	mutex_init(&eq_table->lock);
	for (i = 0; i < MLX5_EVENT_TYPE_MAX; i++)
		ATOMIC_INIT_NOTIFIER_HEAD(&eq_table->nh[i]);

	eq_table->irq_table = dev->priv.irq_table;
	return 0;
}