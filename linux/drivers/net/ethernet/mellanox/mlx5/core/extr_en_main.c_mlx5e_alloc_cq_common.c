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
typedef  scalar_t__ u32 ;
struct mlx5e_cq_param {int /*<<< orphan*/  eq_ix; int /*<<< orphan*/  cqc; int /*<<< orphan*/  wq; } ;
struct TYPE_3__ {scalar_t__* db; } ;
struct TYPE_4__ {TYPE_1__ db; } ;
struct mlx5_core_cq {int cqe_sz; unsigned int irqn; int /*<<< orphan*/  event; int /*<<< orphan*/  comp; int /*<<< orphan*/  vector; scalar_t__* arm_db; scalar_t__* set_ci_db; } ;
struct mlx5e_cq {struct mlx5_core_dev* mdev; int /*<<< orphan*/  wq; TYPE_2__ wq_ctrl; struct mlx5_core_cq mcq; } ;
struct mlx5_cqe64 {int op_own; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int mlx5_cqwq_create (struct mlx5_core_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ mlx5_cqwq_get_size (int /*<<< orphan*/ *) ; 
 struct mlx5_cqe64* mlx5_cqwq_get_wqe (int /*<<< orphan*/ *,scalar_t__) ; 
 int mlx5_vector2eqn (struct mlx5_core_dev*,int /*<<< orphan*/ ,int*,unsigned int*) ; 
 int /*<<< orphan*/  mlx5e_completion_event ; 
 int /*<<< orphan*/  mlx5e_cq_error_event ; 

__attribute__((used)) static int mlx5e_alloc_cq_common(struct mlx5_core_dev *mdev,
				 struct mlx5e_cq_param *param,
				 struct mlx5e_cq *cq)
{
	struct mlx5_core_cq *mcq = &cq->mcq;
	int eqn_not_used;
	unsigned int irqn;
	int err;
	u32 i;

	err = mlx5_vector2eqn(mdev, param->eq_ix, &eqn_not_used, &irqn);
	if (err)
		return err;

	err = mlx5_cqwq_create(mdev, &param->wq, param->cqc, &cq->wq,
			       &cq->wq_ctrl);
	if (err)
		return err;

	mcq->cqe_sz     = 64;
	mcq->set_ci_db  = cq->wq_ctrl.db.db;
	mcq->arm_db     = cq->wq_ctrl.db.db + 1;
	*mcq->set_ci_db = 0;
	*mcq->arm_db    = 0;
	mcq->vector     = param->eq_ix;
	mcq->comp       = mlx5e_completion_event;
	mcq->event      = mlx5e_cq_error_event;
	mcq->irqn       = irqn;

	for (i = 0; i < mlx5_cqwq_get_size(&cq->wq); i++) {
		struct mlx5_cqe64 *cqe = mlx5_cqwq_get_wqe(&cq->wq, i);

		cqe->op_own = 0xf1;
	}

	cq->mdev = mdev;

	return 0;
}