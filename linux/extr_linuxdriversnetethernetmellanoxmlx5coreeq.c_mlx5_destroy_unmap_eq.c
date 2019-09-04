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
struct TYPE_2__ {int /*<<< orphan*/  task; } ;
struct mlx5_eq {scalar_t__ type; int /*<<< orphan*/  buf; TYPE_1__ tasklet_ctx; int /*<<< orphan*/  irqn; int /*<<< orphan*/  eqn; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLX5_EQ_TYPE_COMP ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct mlx5_eq*) ; 
 int /*<<< orphan*/  mlx5_buf_free (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 
 int mlx5_cmd_destroy_eq (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_debug_eq_remove (struct mlx5_core_dev*,struct mlx5_eq*) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 

int mlx5_destroy_unmap_eq(struct mlx5_core_dev *dev, struct mlx5_eq *eq)
{
	int err;

	mlx5_debug_eq_remove(dev, eq);
	free_irq(eq->irqn, eq);
	err = mlx5_cmd_destroy_eq(dev, eq->eqn);
	if (err)
		mlx5_core_warn(dev, "failed to destroy a previously created eq: eqn %d\n",
			       eq->eqn);
	synchronize_irq(eq->irqn);

	if (eq->type == MLX5_EQ_TYPE_COMP) {
		tasklet_disable(&eq->tasklet_ctx.task);
#ifdef CONFIG_INFINIBAND_ON_DEMAND_PAGING
	} else if (eq->type == MLX5_EQ_TYPE_PF) {
		cancel_work_sync(&eq->pf_ctx.work);
		destroy_workqueue(eq->pf_ctx.wq);
		mempool_destroy(eq->pf_ctx.pool);
#endif
	}
	mlx5_buf_free(dev, &eq->buf);

	return err;
}