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
struct TYPE_4__ {int /*<<< orphan*/  done; } ;
struct mlx4_ib_drain_cqe {int /*<<< orphan*/  done; TYPE_2__ cqe; } ;
struct mlx4_ib_dev {struct mlx4_dev* dev; } ;
struct mlx4_dev {TYPE_1__* persist; } ;
struct ib_recv_wr {TYPE_2__* wr_cqe; } ;
struct ib_qp_attr {int /*<<< orphan*/  qp_state; } ;
struct ib_qp {int /*<<< orphan*/  device; struct ib_cq* recv_cq; } ;
struct ib_cq {int dummy; } ;
struct TYPE_3__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_QPS_ERR ; 
 int /*<<< orphan*/  IB_QP_STATE ; 
 scalar_t__ MLX4_DEVICE_STATE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int _mlx4_ib_post_recv (struct ib_qp*,struct ib_recv_wr*,struct ib_recv_wr const**,int) ; 
 int /*<<< orphan*/  handle_drain_completion (struct ib_cq*,struct mlx4_ib_drain_cqe*,struct mlx4_ib_dev*) ; 
 int ib_modify_qp (struct ib_qp*,struct ib_qp_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_ib_drain_qp_done ; 
 struct mlx4_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 

void mlx4_ib_drain_rq(struct ib_qp *qp)
{
	struct ib_cq *cq = qp->recv_cq;
	struct ib_qp_attr attr = { .qp_state = IB_QPS_ERR };
	struct mlx4_ib_drain_cqe rdrain;
	struct ib_recv_wr rwr = {};
	const struct ib_recv_wr *bad_rwr;
	int ret;
	struct mlx4_ib_dev *dev = to_mdev(qp->device);
	struct mlx4_dev *mdev = dev->dev;

	ret = ib_modify_qp(qp, &attr, IB_QP_STATE);
	if (ret && mdev->persist->state != MLX4_DEVICE_STATE_INTERNAL_ERROR) {
		WARN_ONCE(ret, "failed to drain recv queue: %d\n", ret);
		return;
	}

	rwr.wr_cqe = &rdrain.cqe;
	rdrain.cqe.done = mlx4_ib_drain_qp_done;
	init_completion(&rdrain.done);

	ret = _mlx4_ib_post_recv(qp, &rwr, &bad_rwr, true);
	if (ret) {
		WARN_ONCE(ret, "failed to drain recv queue: %d\n", ret);
		return;
	}

	handle_drain_completion(cq, &rdrain, dev);
}