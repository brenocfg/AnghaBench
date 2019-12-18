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
typedef  scalar_t__ u8 ;
struct mlx5dr_cq {TYPE_2__* qp; } ;
struct mlx5_cqe64 {int /*<<< orphan*/  wqe_counter; } ;
struct TYPE_3__ {int wqe_cnt; scalar_t__* wqe_head; scalar_t__ cc; } ;
struct TYPE_4__ {TYPE_1__ sq; } ;

/* Variables and functions */
 int CQ_OK ; 
 int CQ_POLL_ERR ; 
 scalar_t__ MLX5_CQE_REQ_ERR ; 
 scalar_t__ MLX5_CQE_RESP_ERR ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ get_cqe_opcode (struct mlx5_cqe64*) ; 

__attribute__((used)) static int dr_parse_cqe(struct mlx5dr_cq *dr_cq, struct mlx5_cqe64 *cqe64)
{
	unsigned int idx;
	u8 opcode;

	opcode = get_cqe_opcode(cqe64);
	if (opcode == MLX5_CQE_REQ_ERR) {
		idx = be16_to_cpu(cqe64->wqe_counter) &
			(dr_cq->qp->sq.wqe_cnt - 1);
		dr_cq->qp->sq.cc = dr_cq->qp->sq.wqe_head[idx] + 1;
	} else if (opcode == MLX5_CQE_RESP_ERR) {
		++dr_cq->qp->sq.cc;
	} else {
		idx = be16_to_cpu(cqe64->wqe_counter) &
			(dr_cq->qp->sq.wqe_cnt - 1);
		dr_cq->qp->sq.cc = dr_cq->qp->sq.wqe_head[idx] + 1;

		return CQ_OK;
	}

	return CQ_POLL_ERR;
}