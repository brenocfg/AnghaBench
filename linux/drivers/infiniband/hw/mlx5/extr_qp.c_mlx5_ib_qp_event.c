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
struct mlx5_core_qp {int /*<<< orphan*/  qpn; } ;
struct ib_qp {int /*<<< orphan*/  qp_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  device; } ;
struct TYPE_5__ {struct ib_qp* qp; } ;
struct ib_event {int /*<<< orphan*/  event; TYPE_2__ element; int /*<<< orphan*/  device; } ;
struct TYPE_4__ {int /*<<< orphan*/  alt_port; } ;
struct TYPE_6__ {TYPE_1__ trans_qp; int /*<<< orphan*/  port; struct ib_qp ibqp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_EVENT_COMM_EST ; 
 int /*<<< orphan*/  IB_EVENT_PATH_MIG ; 
 int /*<<< orphan*/  IB_EVENT_PATH_MIG_ERR ; 
 int /*<<< orphan*/  IB_EVENT_QP_ACCESS_ERR ; 
 int /*<<< orphan*/  IB_EVENT_QP_FATAL ; 
 int /*<<< orphan*/  IB_EVENT_QP_LAST_WQE_REACHED ; 
 int /*<<< orphan*/  IB_EVENT_QP_REQ_ERR ; 
 int /*<<< orphan*/  IB_EVENT_SQ_DRAINED ; 
#define  MLX5_EVENT_TYPE_COMM_EST 135 
#define  MLX5_EVENT_TYPE_PATH_MIG 134 
#define  MLX5_EVENT_TYPE_PATH_MIG_FAILED 133 
#define  MLX5_EVENT_TYPE_SQ_DRAINED 132 
#define  MLX5_EVENT_TYPE_SRQ_LAST_WQE 131 
#define  MLX5_EVENT_TYPE_WQ_ACCESS_ERROR 130 
#define  MLX5_EVENT_TYPE_WQ_CATAS_ERROR 129 
#define  MLX5_EVENT_TYPE_WQ_INVAL_REQ_ERROR 128 
 int /*<<< orphan*/  pr_warn (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ib_event*,int /*<<< orphan*/ ) ; 
 TYPE_3__* to_mibqp (struct mlx5_core_qp*) ; 

__attribute__((used)) static void mlx5_ib_qp_event(struct mlx5_core_qp *qp, int type)
{
	struct ib_qp *ibqp = &to_mibqp(qp)->ibqp;
	struct ib_event event;

	if (type == MLX5_EVENT_TYPE_PATH_MIG) {
		/* This event is only valid for trans_qps */
		to_mibqp(qp)->port = to_mibqp(qp)->trans_qp.alt_port;
	}

	if (ibqp->event_handler) {
		event.device     = ibqp->device;
		event.element.qp = ibqp;
		switch (type) {
		case MLX5_EVENT_TYPE_PATH_MIG:
			event.event = IB_EVENT_PATH_MIG;
			break;
		case MLX5_EVENT_TYPE_COMM_EST:
			event.event = IB_EVENT_COMM_EST;
			break;
		case MLX5_EVENT_TYPE_SQ_DRAINED:
			event.event = IB_EVENT_SQ_DRAINED;
			break;
		case MLX5_EVENT_TYPE_SRQ_LAST_WQE:
			event.event = IB_EVENT_QP_LAST_WQE_REACHED;
			break;
		case MLX5_EVENT_TYPE_WQ_CATAS_ERROR:
			event.event = IB_EVENT_QP_FATAL;
			break;
		case MLX5_EVENT_TYPE_PATH_MIG_FAILED:
			event.event = IB_EVENT_PATH_MIG_ERR;
			break;
		case MLX5_EVENT_TYPE_WQ_INVAL_REQ_ERROR:
			event.event = IB_EVENT_QP_REQ_ERR;
			break;
		case MLX5_EVENT_TYPE_WQ_ACCESS_ERROR:
			event.event = IB_EVENT_QP_ACCESS_ERR;
			break;
		default:
			pr_warn("mlx5_ib: Unexpected event type %d on QP %06x\n", type, qp->qpn);
			return;
		}

		ibqp->event_handler(&event, ibqp->qp_context);
	}
}