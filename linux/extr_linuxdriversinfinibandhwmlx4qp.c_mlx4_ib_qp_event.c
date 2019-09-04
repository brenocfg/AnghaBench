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
struct mlx4_qp {int /*<<< orphan*/  qpn; } ;
struct ib_qp {int /*<<< orphan*/  qp_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  device; } ;
struct TYPE_3__ {struct ib_qp* qp; } ;
struct ib_event {int /*<<< orphan*/  event; TYPE_1__ element; int /*<<< orphan*/  device; } ;
typedef  enum mlx4_event { ____Placeholder_mlx4_event } mlx4_event ;
struct TYPE_4__ {int /*<<< orphan*/  alt_port; int /*<<< orphan*/  port; struct ib_qp ibqp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_EVENT_COMM_EST ; 
 int /*<<< orphan*/  IB_EVENT_PATH_MIG ; 
 int /*<<< orphan*/  IB_EVENT_PATH_MIG_ERR ; 
 int /*<<< orphan*/  IB_EVENT_QP_ACCESS_ERR ; 
 int /*<<< orphan*/  IB_EVENT_QP_FATAL ; 
 int /*<<< orphan*/  IB_EVENT_QP_LAST_WQE_REACHED ; 
 int /*<<< orphan*/  IB_EVENT_QP_REQ_ERR ; 
 int /*<<< orphan*/  IB_EVENT_SQ_DRAINED ; 
#define  MLX4_EVENT_TYPE_COMM_EST 135 
#define  MLX4_EVENT_TYPE_PATH_MIG 134 
#define  MLX4_EVENT_TYPE_PATH_MIG_FAILED 133 
#define  MLX4_EVENT_TYPE_SQ_DRAINED 132 
#define  MLX4_EVENT_TYPE_SRQ_QP_LAST_WQE 131 
#define  MLX4_EVENT_TYPE_WQ_ACCESS_ERROR 130 
#define  MLX4_EVENT_TYPE_WQ_CATAS_ERROR 129 
#define  MLX4_EVENT_TYPE_WQ_INVAL_REQ_ERROR 128 
 int /*<<< orphan*/  pr_warn (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ib_event*,int /*<<< orphan*/ ) ; 
 TYPE_2__* to_mibqp (struct mlx4_qp*) ; 

__attribute__((used)) static void mlx4_ib_qp_event(struct mlx4_qp *qp, enum mlx4_event type)
{
	struct ib_event event;
	struct ib_qp *ibqp = &to_mibqp(qp)->ibqp;

	if (type == MLX4_EVENT_TYPE_PATH_MIG)
		to_mibqp(qp)->port = to_mibqp(qp)->alt_port;

	if (ibqp->event_handler) {
		event.device     = ibqp->device;
		event.element.qp = ibqp;
		switch (type) {
		case MLX4_EVENT_TYPE_PATH_MIG:
			event.event = IB_EVENT_PATH_MIG;
			break;
		case MLX4_EVENT_TYPE_COMM_EST:
			event.event = IB_EVENT_COMM_EST;
			break;
		case MLX4_EVENT_TYPE_SQ_DRAINED:
			event.event = IB_EVENT_SQ_DRAINED;
			break;
		case MLX4_EVENT_TYPE_SRQ_QP_LAST_WQE:
			event.event = IB_EVENT_QP_LAST_WQE_REACHED;
			break;
		case MLX4_EVENT_TYPE_WQ_CATAS_ERROR:
			event.event = IB_EVENT_QP_FATAL;
			break;
		case MLX4_EVENT_TYPE_PATH_MIG_FAILED:
			event.event = IB_EVENT_PATH_MIG_ERR;
			break;
		case MLX4_EVENT_TYPE_WQ_INVAL_REQ_ERROR:
			event.event = IB_EVENT_QP_REQ_ERR;
			break;
		case MLX4_EVENT_TYPE_WQ_ACCESS_ERROR:
			event.event = IB_EVENT_QP_ACCESS_ERR;
			break;
		default:
			pr_warn("Unexpected event type %d "
			       "on QP %06x\n", type, qp->qpn);
			return;
		}

		ibqp->event_handler(&event, ibqp->qp_context);
	}
}