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
struct mlx5_srq_table {int /*<<< orphan*/  array; } ;
struct mlx5_ib_dev {struct mlx5_srq_table srq_table; } ;
struct TYPE_2__ {int /*<<< orphan*/  free; } ;
struct mlx5_core_srq {TYPE_1__ common; int /*<<< orphan*/  srqn; } ;

/* Variables and functions */
 int destroy_srq_split (struct mlx5_ib_dev*,struct mlx5_core_srq*) ; 
 int /*<<< orphan*/  mlx5_core_res_put (TYPE_1__*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 struct mlx5_core_srq* xa_erase_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void mlx5_cmd_destroy_srq(struct mlx5_ib_dev *dev, struct mlx5_core_srq *srq)
{
	struct mlx5_srq_table *table = &dev->srq_table;
	struct mlx5_core_srq *tmp;
	int err;

	tmp = xa_erase_irq(&table->array, srq->srqn);
	if (!tmp || tmp != srq)
		return;

	err = destroy_srq_split(dev, srq);
	if (err)
		return;

	mlx5_core_res_put(&srq->common);
	wait_for_completion(&srq->common.free);
}