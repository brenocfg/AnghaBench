#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlx5_pagefault {int dummy; } ;
struct mlx5_ib_wq {int wqe_shift; } ;
struct TYPE_6__ {int qp_type; scalar_t__ srq; } ;
struct mlx5_ib_qp {TYPE_3__ ibqp; scalar_t__ wq_sig; struct mlx5_ib_wq rq; } ;
struct TYPE_4__ {int rc_odp_caps; } ;
struct TYPE_5__ {TYPE_1__ per_transport_caps; } ;
struct mlx5_ib_dev {TYPE_2__ odp_caps; } ;

/* Variables and functions */
 int EFAULT ; 
 int IB_ODP_SUPPORT_RECV ; 
#define  IB_QPT_RC 128 
 int /*<<< orphan*/  mlx5_ib_err (struct mlx5_ib_dev*,char*,...) ; 

__attribute__((used)) static int mlx5_ib_mr_responder_pfault_handler(
	struct mlx5_ib_dev *dev, struct mlx5_pagefault *pfault,
	struct mlx5_ib_qp *qp, void **wqe, void **wqe_end, int wqe_length)
{
	struct mlx5_ib_wq *wq = &qp->rq;
	int wqe_size = 1 << wq->wqe_shift;

	if (qp->ibqp.srq) {
		mlx5_ib_err(dev, "ODP fault on SRQ is not supported\n");
		return -EFAULT;
	}

	if (qp->wq_sig) {
		mlx5_ib_err(dev, "ODP fault with WQE signatures is not supported\n");
		return -EFAULT;
	}

	if (wqe_size > wqe_length) {
		mlx5_ib_err(dev, "Couldn't read all of the receive WQE's content\n");
		return -EFAULT;
	}

	switch (qp->ibqp.qp_type) {
	case IB_QPT_RC:
		if (!(dev->odp_caps.per_transport_caps.rc_odp_caps &
		      IB_ODP_SUPPORT_RECV))
			goto invalid_transport_or_opcode;
		break;
	default:
invalid_transport_or_opcode:
		mlx5_ib_err(dev, "ODP fault on QP of an unsupported transport. transport: 0x%x\n",
			    qp->ibqp.qp_type);
		return -EFAULT;
	}

	*wqe_end = *wqe + wqe_size;

	return 0;
}