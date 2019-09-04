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
typedef  int /*<<< orphan*/  u8 ;
struct mlx5_ib_sq {int dummy; } ;
struct mlx5_ib_rq {int dummy; } ;
struct mlx5_ib_raw_packet_qp {struct mlx5_ib_rq rq; struct mlx5_ib_sq sq; } ;
struct TYPE_4__ {scalar_t__ wqe_cnt; } ;
struct TYPE_3__ {scalar_t__ wqe_cnt; } ;
struct mlx5_ib_qp {TYPE_2__ rq; TYPE_1__ sq; struct mlx5_ib_raw_packet_qp raw_packet_qp; } ;
struct mlx5_ib_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_RQ_STATE_NA ; 
 int /*<<< orphan*/  MLX5_SQ_STATE_NA ; 
 int query_raw_packet_qp_rq_state (struct mlx5_ib_dev*,struct mlx5_ib_rq*,int /*<<< orphan*/ *) ; 
 int query_raw_packet_qp_sq_state (struct mlx5_ib_dev*,struct mlx5_ib_sq*,int /*<<< orphan*/ *) ; 
 int sqrq_state_to_qp_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlx5_ib_qp*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_raw_packet_qp_state(struct mlx5_ib_dev *dev,
				     struct mlx5_ib_qp *qp,
				     u8 *raw_packet_qp_state)
{
	struct mlx5_ib_raw_packet_qp *raw_packet_qp = &qp->raw_packet_qp;
	struct mlx5_ib_sq *sq = &raw_packet_qp->sq;
	struct mlx5_ib_rq *rq = &raw_packet_qp->rq;
	int err;
	u8 sq_state = MLX5_SQ_STATE_NA;
	u8 rq_state = MLX5_RQ_STATE_NA;

	if (qp->sq.wqe_cnt) {
		err = query_raw_packet_qp_sq_state(dev, sq, &sq_state);
		if (err)
			return err;
	}

	if (qp->rq.wqe_cnt) {
		err = query_raw_packet_qp_rq_state(dev, rq, &rq_state);
		if (err)
			return err;
	}

	return sqrq_state_to_qp_state(sq_state, rq_state, qp,
				      raw_packet_qp_state);
}