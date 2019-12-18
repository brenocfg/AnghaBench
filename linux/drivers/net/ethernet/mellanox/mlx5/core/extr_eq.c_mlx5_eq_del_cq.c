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
struct mlx5_cq_table {int /*<<< orphan*/  lock; int /*<<< orphan*/  tree; } ;
struct mlx5_eq {int /*<<< orphan*/  eqn; int /*<<< orphan*/  dev; struct mlx5_cq_table cq_table; } ;
struct mlx5_core_cq {int /*<<< orphan*/  cqn; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_core_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx5_core_cq* radix_tree_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void mlx5_eq_del_cq(struct mlx5_eq *eq, struct mlx5_core_cq *cq)
{
	struct mlx5_cq_table *table = &eq->cq_table;
	struct mlx5_core_cq *tmp;

	spin_lock(&table->lock);
	tmp = radix_tree_delete(&table->tree, cq->cqn);
	spin_unlock(&table->lock);

	if (!tmp) {
		mlx5_core_dbg(eq->dev, "cq 0x%x not found in eq 0x%x tree\n",
			      eq->eqn, cq->cqn);
		return;
	}

	if (tmp != cq)
		mlx5_core_dbg(eq->dev, "corruption on cqn 0x%x in eq 0x%x\n",
			      eq->eqn, cq->cqn);
}