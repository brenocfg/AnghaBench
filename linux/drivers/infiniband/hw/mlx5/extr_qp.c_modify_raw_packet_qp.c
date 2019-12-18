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
typedef  int /*<<< orphan*/  u8 ;
struct mlx5_modify_raw_qp_param {int operation; int /*<<< orphan*/  port; int /*<<< orphan*/  set_mask; } ;
struct mlx5_ib_sq {int state; struct mlx5_flow_handle* flow_rule; } ;
struct mlx5_ib_rq {int dummy; } ;
struct mlx5_ib_raw_packet_qp {struct mlx5_ib_sq sq; struct mlx5_ib_rq rq; } ;
struct TYPE_6__ {int /*<<< orphan*/  pd; } ;
struct TYPE_5__ {int /*<<< orphan*/  wqe_cnt; } ;
struct TYPE_4__ {int /*<<< orphan*/  wqe_cnt; } ;
struct mlx5_ib_qp {TYPE_3__ ibqp; TYPE_2__ sq; TYPE_1__ rq; struct mlx5_ib_raw_packet_qp raw_packet_qp; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct mlx5_flow_handle {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct mlx5_flow_handle*) ; 
#define  MLX5_CMD_OP_2ERR_QP 134 
#define  MLX5_CMD_OP_2RST_QP 133 
#define  MLX5_CMD_OP_INIT2INIT_QP 132 
#define  MLX5_CMD_OP_INIT2RTR_QP 131 
#define  MLX5_CMD_OP_RST2INIT_QP 130 
#define  MLX5_CMD_OP_RTR2RTS_QP 129 
#define  MLX5_CMD_OP_RTS2RTS_QP 128 
 int /*<<< orphan*/  MLX5_RAW_QP_RATE_LIMIT ; 
 int MLX5_RQC_STATE_ERR ; 
 int MLX5_RQC_STATE_RDY ; 
 int MLX5_RQC_STATE_RST ; 
 int MLX5_SQC_STATE_ERR ; 
 int MLX5_SQC_STATE_RDY ; 
 int MLX5_SQC_STATE_RST ; 
 int PTR_ERR (struct mlx5_flow_handle*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct mlx5_flow_handle* create_flow_rule_vport_sq (struct mlx5_ib_dev*,struct mlx5_ib_sq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_flow_rule_vport_sq (struct mlx5_ib_sq*) ; 
 int /*<<< orphan*/  mlx5_del_flow_rules (struct mlx5_flow_handle*) ; 
 int modify_raw_packet_qp_rq (struct mlx5_ib_dev*,struct mlx5_ib_rq*,int,struct mlx5_modify_raw_qp_param const*,int /*<<< orphan*/ ) ; 
 int modify_raw_packet_qp_sq (int /*<<< orphan*/ ,struct mlx5_ib_sq*,int,struct mlx5_modify_raw_qp_param const*,int /*<<< orphan*/ ) ; 
 int modify_raw_packet_tx_affinity (int /*<<< orphan*/ ,struct mlx5_ib_sq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int modify_raw_packet_qp(struct mlx5_ib_dev *dev, struct mlx5_ib_qp *qp,
				const struct mlx5_modify_raw_qp_param *raw_qp_param,
				u8 tx_affinity)
{
	struct mlx5_ib_raw_packet_qp *raw_packet_qp = &qp->raw_packet_qp;
	struct mlx5_ib_rq *rq = &raw_packet_qp->rq;
	struct mlx5_ib_sq *sq = &raw_packet_qp->sq;
	int modify_rq = !!qp->rq.wqe_cnt;
	int modify_sq = !!qp->sq.wqe_cnt;
	int rq_state;
	int sq_state;
	int err;

	switch (raw_qp_param->operation) {
	case MLX5_CMD_OP_RST2INIT_QP:
		rq_state = MLX5_RQC_STATE_RDY;
		sq_state = MLX5_SQC_STATE_RDY;
		break;
	case MLX5_CMD_OP_2ERR_QP:
		rq_state = MLX5_RQC_STATE_ERR;
		sq_state = MLX5_SQC_STATE_ERR;
		break;
	case MLX5_CMD_OP_2RST_QP:
		rq_state = MLX5_RQC_STATE_RST;
		sq_state = MLX5_SQC_STATE_RST;
		break;
	case MLX5_CMD_OP_RTR2RTS_QP:
	case MLX5_CMD_OP_RTS2RTS_QP:
		if (raw_qp_param->set_mask ==
		    MLX5_RAW_QP_RATE_LIMIT) {
			modify_rq = 0;
			sq_state = sq->state;
		} else {
			return raw_qp_param->set_mask ? -EINVAL : 0;
		}
		break;
	case MLX5_CMD_OP_INIT2INIT_QP:
	case MLX5_CMD_OP_INIT2RTR_QP:
		if (raw_qp_param->set_mask)
			return -EINVAL;
		else
			return 0;
	default:
		WARN_ON(1);
		return -EINVAL;
	}

	if (modify_rq) {
		err =  modify_raw_packet_qp_rq(dev, rq, rq_state, raw_qp_param,
					       qp->ibqp.pd);
		if (err)
			return err;
	}

	if (modify_sq) {
		struct mlx5_flow_handle *flow_rule;

		if (tx_affinity) {
			err = modify_raw_packet_tx_affinity(dev->mdev, sq,
							    tx_affinity,
							    qp->ibqp.pd);
			if (err)
				return err;
		}

		flow_rule = create_flow_rule_vport_sq(dev, sq,
						      raw_qp_param->port);
		if (IS_ERR(flow_rule))
			return PTR_ERR(flow_rule);

		err = modify_raw_packet_qp_sq(dev->mdev, sq, sq_state,
					      raw_qp_param, qp->ibqp.pd);
		if (err) {
			if (flow_rule)
				mlx5_del_flow_rules(flow_rule);
			return err;
		}

		if (flow_rule) {
			destroy_flow_rule_vport_sq(sq);
			sq->flow_rule = flow_rule;
		}

		return err;
	}

	return 0;
}