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
struct notifier_block {int dummy; } ;
struct mlx5_eq_table {int /*<<< orphan*/  irq_table; } ;
struct mlx5_eq {int /*<<< orphan*/  vecidx; } ;
struct TYPE_2__ {struct mlx5_eq_table* eq_table; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  eq_update_ci (struct mlx5_eq*,int) ; 
 int mlx5_irq_attach_nb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct notifier_block*) ; 

int mlx5_eq_enable(struct mlx5_core_dev *dev, struct mlx5_eq *eq,
		   struct notifier_block *nb)
{
	struct mlx5_eq_table *eq_table = dev->priv.eq_table;
	int err;

	err = mlx5_irq_attach_nb(eq_table->irq_table, eq->vecidx, nb);
	if (!err)
		eq_update_ci(eq, 1);

	return err;
}