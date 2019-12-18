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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_cq_table {int /*<<< orphan*/  tree; } ;
struct mlx5_eq {struct mlx5_cq_table cq_table; } ;
struct mlx5_core_cq {int dummy; } ;

/* Variables and functions */
 scalar_t__ likely (struct mlx5_core_cq*) ; 
 int /*<<< orphan*/  mlx5_cq_hold (struct mlx5_core_cq*) ; 
 struct mlx5_core_cq* radix_tree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static struct mlx5_core_cq *mlx5_eq_cq_get(struct mlx5_eq *eq, u32 cqn)
{
	struct mlx5_cq_table *table = &eq->cq_table;
	struct mlx5_core_cq *cq = NULL;

	rcu_read_lock();
	cq = radix_tree_lookup(&table->tree, cqn);
	if (likely(cq))
		mlx5_cq_hold(cq);
	rcu_read_unlock();

	return cq;
}