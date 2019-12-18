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
struct mlx5_qp_table {int /*<<< orphan*/  lock; int /*<<< orphan*/  tree; } ;
struct mlx5_core_rsc_common {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 struct mlx5_core_rsc_common* radix_tree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct mlx5_core_rsc_common *
mlx5_get_rsc(struct mlx5_qp_table *table, u32 rsn)
{
	struct mlx5_core_rsc_common *common;
	unsigned long flags;

	spin_lock_irqsave(&table->lock, flags);

	common = radix_tree_lookup(&table->tree, rsn);
	if (common)
		refcount_inc(&common->refcount);

	spin_unlock_irqrestore(&table->lock, flags);

	return common;
}