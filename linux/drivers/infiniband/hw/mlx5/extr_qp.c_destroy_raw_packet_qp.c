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
struct mlx5_ib_sq {int dummy; } ;
struct mlx5_ib_rq {int dummy; } ;
struct mlx5_ib_raw_packet_qp {struct mlx5_ib_rq rq; struct mlx5_ib_sq sq; } ;
struct TYPE_6__ {int /*<<< orphan*/  pd; } ;
struct TYPE_5__ {scalar_t__ wqe_cnt; } ;
struct TYPE_4__ {scalar_t__ wqe_cnt; } ;
struct mlx5_ib_qp {TYPE_3__ ibqp; TYPE_2__ sq; int /*<<< orphan*/  flags_en; TYPE_1__ rq; struct mlx5_ib_raw_packet_qp raw_packet_qp; } ;
struct mlx5_ib_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_raw_packet_qp_rq (struct mlx5_ib_dev*,struct mlx5_ib_rq*) ; 
 int /*<<< orphan*/  destroy_raw_packet_qp_sq (struct mlx5_ib_dev*,struct mlx5_ib_sq*) ; 
 int /*<<< orphan*/  destroy_raw_packet_qp_tir (struct mlx5_ib_dev*,struct mlx5_ib_rq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_raw_packet_qp_tis (struct mlx5_ib_dev*,struct mlx5_ib_sq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_raw_packet_qp(struct mlx5_ib_dev *dev,
				  struct mlx5_ib_qp *qp)
{
	struct mlx5_ib_raw_packet_qp *raw_packet_qp = &qp->raw_packet_qp;
	struct mlx5_ib_sq *sq = &raw_packet_qp->sq;
	struct mlx5_ib_rq *rq = &raw_packet_qp->rq;

	if (qp->rq.wqe_cnt) {
		destroy_raw_packet_qp_tir(dev, rq, qp->flags_en, qp->ibqp.pd);
		destroy_raw_packet_qp_rq(dev, rq);
	}

	if (qp->sq.wqe_cnt) {
		destroy_raw_packet_qp_sq(dev, sq);
		destroy_raw_packet_qp_tis(dev, sq, qp->ibqp.pd);
	}
}