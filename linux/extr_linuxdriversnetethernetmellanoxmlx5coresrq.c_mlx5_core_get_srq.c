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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_srq_table {int /*<<< orphan*/  lock; int /*<<< orphan*/  tree; } ;
struct mlx5_core_srq {int /*<<< orphan*/  refcount; } ;
struct TYPE_2__ {struct mlx5_srq_table srq_table; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct mlx5_core_srq* radix_tree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct mlx5_core_srq *mlx5_core_get_srq(struct mlx5_core_dev *dev, u32 srqn)
{
	struct mlx5_srq_table *table = &dev->priv.srq_table;
	struct mlx5_core_srq *srq;

	spin_lock(&table->lock);

	srq = radix_tree_lookup(&table->tree, srqn);
	if (srq)
		atomic_inc(&srq->refcount);

	spin_unlock(&table->lock);

	return srq;
}