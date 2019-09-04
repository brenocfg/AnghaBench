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
struct TYPE_4__ {int /*<<< orphan*/  buf_numa_node; int /*<<< orphan*/  db_numa_node; } ;
struct mlx5e_rq_param {TYPE_2__ wq; void* rqc; } ;
struct TYPE_3__ {int /*<<< orphan*/  wq; } ;
struct mlx5e_rq {struct mlx5_core_dev* mdev; int /*<<< orphan*/  xdp_rxq; int /*<<< orphan*/  wq_ctrl; TYPE_1__ wqe; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 void* MLX5_ADDR_OF (void*,void*,int /*<<< orphan*/ ) ; 
 int mlx5_wq_cyc_create (struct mlx5_core_dev*,TYPE_2__*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wq ; 
 int /*<<< orphan*/  xdp_rxq_info_unused (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5e_alloc_drop_rq(struct mlx5_core_dev *mdev,
			       struct mlx5e_rq *rq,
			       struct mlx5e_rq_param *param)
{
	void *rqc = param->rqc;
	void *rqc_wq = MLX5_ADDR_OF(rqc, rqc, wq);
	int err;

	param->wq.db_numa_node = param->wq.buf_numa_node;

	err = mlx5_wq_cyc_create(mdev, &param->wq, rqc_wq, &rq->wqe.wq,
				 &rq->wq_ctrl);
	if (err)
		return err;

	/* Mark as unused given "Drop-RQ" packets never reach XDP */
	xdp_rxq_info_unused(&rq->xdp_rxq);

	rq->mdev = mdev;

	return 0;
}