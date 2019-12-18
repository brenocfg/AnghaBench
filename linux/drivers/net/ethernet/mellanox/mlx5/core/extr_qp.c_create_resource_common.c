#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlx5_qp_table {int /*<<< orphan*/  lock; int /*<<< orphan*/  tree; } ;
struct TYPE_4__ {int res; int /*<<< orphan*/  free; int /*<<< orphan*/  refcount; } ;
struct mlx5_core_qp {int qpn; int /*<<< orphan*/  pid; TYPE_1__ common; } ;
struct TYPE_5__ {struct mlx5_qp_table qp_table; } ;
struct mlx5_core_dev {TYPE_2__ priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int MLX5_USER_INDEX_LEN ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int radix_tree_insert (int /*<<< orphan*/ *,int,struct mlx5_core_qp*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_resource_common(struct mlx5_core_dev *dev,
				  struct mlx5_core_qp *qp,
				  int rsc_type)
{
	struct mlx5_qp_table *table = &dev->priv.qp_table;
	int err;

	qp->common.res = rsc_type;
	spin_lock_irq(&table->lock);
	err = radix_tree_insert(&table->tree,
				qp->qpn | (rsc_type << MLX5_USER_INDEX_LEN),
				qp);
	spin_unlock_irq(&table->lock);
	if (err)
		return err;

	refcount_set(&qp->common.refcount, 1);
	init_completion(&qp->common.free);
	qp->pid = current->pid;

	return 0;
}