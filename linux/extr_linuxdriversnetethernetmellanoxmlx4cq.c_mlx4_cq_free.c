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
struct TYPE_4__ {TYPE_1__* eq; } ;
struct mlx4_cq_table {int /*<<< orphan*/  lock; int /*<<< orphan*/  tree; } ;
struct mlx4_priv {TYPE_2__ eq_table; struct mlx4_cq_table cq_table; } ;
struct mlx4_dev {int dummy; } ;
struct mlx4_cq {int /*<<< orphan*/  cqn; int /*<<< orphan*/  free; int /*<<< orphan*/  refcount; int /*<<< orphan*/  vector; } ;
struct TYPE_3__ {scalar_t__ irq; } ;

/* Variables and functions */
 size_t MLX4_CQ_TO_EQ_VECTOR (int /*<<< orphan*/ ) ; 
 size_t MLX4_EQ_ASYNC ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int mlx4_HW2SW_CQ (struct mlx4_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_cq_free_icm (struct mlx4_dev*,int /*<<< orphan*/ ) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_dev*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_irq (scalar_t__) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void mlx4_cq_free(struct mlx4_dev *dev, struct mlx4_cq *cq)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_cq_table *cq_table = &priv->cq_table;
	int err;

	err = mlx4_HW2SW_CQ(dev, NULL, cq->cqn);
	if (err)
		mlx4_warn(dev, "HW2SW_CQ failed (%d) for CQN %06x\n", err, cq->cqn);

	spin_lock(&cq_table->lock);
	radix_tree_delete(&cq_table->tree, cq->cqn);
	spin_unlock(&cq_table->lock);

	synchronize_irq(priv->eq_table.eq[MLX4_CQ_TO_EQ_VECTOR(cq->vector)].irq);
	if (priv->eq_table.eq[MLX4_CQ_TO_EQ_VECTOR(cq->vector)].irq !=
	    priv->eq_table.eq[MLX4_EQ_ASYNC].irq)
		synchronize_irq(priv->eq_table.eq[MLX4_EQ_ASYNC].irq);

	if (refcount_dec_and_test(&cq->refcount))
		complete(&cq->free);
	wait_for_completion(&cq->free);

	mlx4_cq_free_icm(dev, cq->cqn);
}