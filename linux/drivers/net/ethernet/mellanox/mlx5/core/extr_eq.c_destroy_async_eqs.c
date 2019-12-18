#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  core; int /*<<< orphan*/  irq_nb; } ;
struct TYPE_7__ {int /*<<< orphan*/  core; int /*<<< orphan*/  irq_nb; } ;
struct TYPE_6__ {int /*<<< orphan*/  core; int /*<<< orphan*/  irq_nb; } ;
struct mlx5_eq_table {int /*<<< orphan*/  cq_err_nb; TYPE_4__ cmd_eq; TYPE_3__ async_eq; TYPE_2__ pages_eq; } ;
struct TYPE_5__ {struct mlx5_eq_table* eq_table; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int destroy_async_eq (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_cmd_use_polling (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*,int) ; 
 int /*<<< orphan*/  mlx5_eq_disable (struct mlx5_core_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_eq_notifier_unregister (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_async_eqs(struct mlx5_core_dev *dev)
{
	struct mlx5_eq_table *table = dev->priv.eq_table;
	int err;

	mlx5_eq_disable(dev, &table->pages_eq.core, &table->pages_eq.irq_nb);
	err = destroy_async_eq(dev, &table->pages_eq.core);
	if (err)
		mlx5_core_err(dev, "failed to destroy pages eq, err(%d)\n",
			      err);

	mlx5_eq_disable(dev, &table->async_eq.core, &table->async_eq.irq_nb);
	err = destroy_async_eq(dev, &table->async_eq.core);
	if (err)
		mlx5_core_err(dev, "failed to destroy async eq, err(%d)\n",
			      err);

	mlx5_cmd_use_polling(dev);

	mlx5_eq_disable(dev, &table->cmd_eq.core, &table->cmd_eq.irq_nb);
	err = destroy_async_eq(dev, &table->cmd_eq.core);
	if (err)
		mlx5_core_err(dev, "failed to destroy command eq, err(%d)\n",
			      err);

	mlx5_eq_notifier_unregister(dev, &table->cq_err_nb);
}