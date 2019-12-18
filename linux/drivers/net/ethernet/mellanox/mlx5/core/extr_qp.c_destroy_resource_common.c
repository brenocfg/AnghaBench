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
struct mlx5_qp_table {int /*<<< orphan*/  lock; int /*<<< orphan*/  tree; } ;
struct mlx5_core_rsc_common {int dummy; } ;
struct TYPE_3__ {int res; int /*<<< orphan*/  free; } ;
struct mlx5_core_qp {int qpn; TYPE_1__ common; } ;
struct TYPE_4__ {struct mlx5_qp_table qp_table; } ;
struct mlx5_core_dev {TYPE_2__ priv; } ;

/* Variables and functions */
 int MLX5_USER_INDEX_LEN ; 
 int /*<<< orphan*/  mlx5_core_put_rsc (struct mlx5_core_rsc_common*) ; 
 int /*<<< orphan*/  radix_tree_delete (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_resource_common(struct mlx5_core_dev *dev,
				    struct mlx5_core_qp *qp)
{
	struct mlx5_qp_table *table = &dev->priv.qp_table;
	unsigned long flags;

	spin_lock_irqsave(&table->lock, flags);
	radix_tree_delete(&table->tree,
			  qp->qpn | (qp->common.res << MLX5_USER_INDEX_LEN));
	spin_unlock_irqrestore(&table->lock, flags);
	mlx5_core_put_rsc((struct mlx5_core_rsc_common *)qp);
	wait_for_completion(&qp->common.free);
}