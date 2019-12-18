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
struct mlx5_srq_attr {int type; } ;
struct mlx5_ib_dev {struct mlx5_srq_table srq_table; } ;
struct TYPE_2__ {int /*<<< orphan*/  free; int /*<<< orphan*/  refcount; int /*<<< orphan*/  res; } ;
struct mlx5_core_srq {int /*<<< orphan*/  srqn; TYPE_1__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  IB_SRQT_TM 129 
#define  IB_SRQT_XRC 128 
 int /*<<< orphan*/  MLX5_RES_SRQ ; 
 int /*<<< orphan*/  MLX5_RES_XRQ ; 
 int /*<<< orphan*/  MLX5_RES_XSRQ ; 
 int create_srq_split (struct mlx5_ib_dev*,struct mlx5_core_srq*,struct mlx5_srq_attr*) ; 
 int /*<<< orphan*/  destroy_srq_split (struct mlx5_ib_dev*,struct mlx5_core_srq*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int xa_err (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_store_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mlx5_core_srq*,int /*<<< orphan*/ ) ; 

int mlx5_cmd_create_srq(struct mlx5_ib_dev *dev, struct mlx5_core_srq *srq,
			struct mlx5_srq_attr *in)
{
	struct mlx5_srq_table *table = &dev->srq_table;
	int err;

	switch (in->type) {
	case IB_SRQT_XRC:
		srq->common.res = MLX5_RES_XSRQ;
		break;
	case IB_SRQT_TM:
		srq->common.res = MLX5_RES_XRQ;
		break;
	default:
		srq->common.res = MLX5_RES_SRQ;
	}

	err = create_srq_split(dev, srq, in);
	if (err)
		return err;

	refcount_set(&srq->common.refcount, 1);
	init_completion(&srq->common.free);

	err = xa_err(xa_store_irq(&table->array, srq->srqn, srq, GFP_KERNEL));
	if (err)
		goto err_destroy_srq_split;

	return 0;

err_destroy_srq_split:
	destroy_srq_split(dev, srq);

	return err;
}