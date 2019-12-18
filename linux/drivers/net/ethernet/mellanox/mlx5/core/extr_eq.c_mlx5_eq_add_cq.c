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
struct mlx5_eq {struct mlx5_cq_table cq_table; } ;
struct mlx5_core_cq {int /*<<< orphan*/  cqn; } ;

/* Variables and functions */
 int radix_tree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mlx5_core_cq*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int mlx5_eq_add_cq(struct mlx5_eq *eq, struct mlx5_core_cq *cq)
{
	struct mlx5_cq_table *table = &eq->cq_table;
	int err;

	spin_lock(&table->lock);
	err = radix_tree_insert(&table->tree, cq->cqn, cq);
	spin_unlock(&table->lock);

	return err;
}