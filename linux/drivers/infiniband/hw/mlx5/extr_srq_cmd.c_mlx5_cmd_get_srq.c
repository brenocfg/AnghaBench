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
struct mlx5_srq_table {int /*<<< orphan*/  array; } ;
struct mlx5_ib_dev {struct mlx5_srq_table srq_table; } ;
struct TYPE_2__ {int /*<<< orphan*/  refcount; } ;
struct mlx5_core_srq {TYPE_1__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 struct mlx5_core_srq* xa_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_unlock (int /*<<< orphan*/ *) ; 

struct mlx5_core_srq *mlx5_cmd_get_srq(struct mlx5_ib_dev *dev, u32 srqn)
{
	struct mlx5_srq_table *table = &dev->srq_table;
	struct mlx5_core_srq *srq;

	xa_lock(&table->array);
	srq = xa_load(&table->array, srqn);
	if (srq)
		refcount_inc(&srq->common.refcount);
	xa_unlock(&table->array);

	return srq;
}