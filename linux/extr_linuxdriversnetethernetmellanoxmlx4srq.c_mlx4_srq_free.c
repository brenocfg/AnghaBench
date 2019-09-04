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
struct mlx4_srq_table {int /*<<< orphan*/  lock; int /*<<< orphan*/  tree; } ;
struct mlx4_srq {int /*<<< orphan*/  srqn; int /*<<< orphan*/  free; int /*<<< orphan*/  refcount; } ;
struct mlx4_dev {int dummy; } ;
struct TYPE_2__ {struct mlx4_srq_table srq_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int mlx4_HW2SW_SRQ (struct mlx4_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_srq_free_icm (struct mlx4_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_dev*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void mlx4_srq_free(struct mlx4_dev *dev, struct mlx4_srq *srq)
{
	struct mlx4_srq_table *srq_table = &mlx4_priv(dev)->srq_table;
	int err;

	err = mlx4_HW2SW_SRQ(dev, NULL, srq->srqn);
	if (err)
		mlx4_warn(dev, "HW2SW_SRQ failed (%d) for SRQN %06x\n", err, srq->srqn);

	spin_lock_irq(&srq_table->lock);
	radix_tree_delete(&srq_table->tree, srq->srqn);
	spin_unlock_irq(&srq_table->lock);

	if (refcount_dec_and_test(&srq->refcount))
		complete(&srq->free);
	wait_for_completion(&srq->free);

	mlx4_srq_free_icm(dev, srq->srqn);
}