#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usnic_transport_spec {int dummy; } ;
struct usnic_ib_qp_grp_flow {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  qp_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;} ;
struct usnic_ib_qp_grp {int state; int /*<<< orphan*/  grp_id; int /*<<< orphan*/  lock; TYPE_4__ ibqp; TYPE_2__* vf; } ;
struct TYPE_7__ {TYPE_4__* qp; } ;
struct ib_event {int /*<<< orphan*/  event; TYPE_3__ element; int /*<<< orphan*/ * device; } ;
typedef  enum ib_qp_state { ____Placeholder_ib_qp_state } ib_qp_state ;
struct TYPE_6__ {TYPE_1__* pf; } ;
struct TYPE_5__ {int /*<<< orphan*/  ib_dev; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  IB_EVENT_QP_FATAL ; 
#define  IB_QPS_ERR 132 
#define  IB_QPS_INIT 131 
#define  IB_QPS_RESET 130 
#define  IB_QPS_RTR 129 
#define  IB_QPS_RTS 128 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct usnic_ib_qp_grp_flow*) ; 
 int PTR_ERR (struct usnic_ib_qp_grp_flow*) ; 
 struct usnic_ib_qp_grp_flow* create_and_add_flow (struct usnic_ib_qp_grp*,struct usnic_transport_spec*) ; 
 int disable_qp_grp (struct usnic_ib_qp_grp*) ; 
 int enable_qp_grp (struct usnic_ib_qp_grp*) ; 
 int /*<<< orphan*/  release_and_remove_all_flows (struct usnic_ib_qp_grp*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ib_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ib_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct ib_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usnic_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usnic_ib_qp_grp_state_to_string (int) ; 
 int /*<<< orphan*/  usnic_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int usnic_ib_qp_grp_modify(struct usnic_ib_qp_grp *qp_grp,
				enum ib_qp_state new_state,
				void *data)
{
	int status = 0;
	struct ib_event ib_event;
	enum ib_qp_state old_state;
	struct usnic_transport_spec *trans_spec;
	struct usnic_ib_qp_grp_flow *qp_flow;

	old_state = qp_grp->state;
	trans_spec = (struct usnic_transport_spec *) data;

	spin_lock(&qp_grp->lock);
	switch (new_state) {
	case IB_QPS_RESET:
		switch (old_state) {
		case IB_QPS_RESET:
			/* NO-OP */
			break;
		case IB_QPS_INIT:
			release_and_remove_all_flows(qp_grp);
			status = 0;
			break;
		case IB_QPS_RTR:
		case IB_QPS_RTS:
		case IB_QPS_ERR:
			status = disable_qp_grp(qp_grp);
			release_and_remove_all_flows(qp_grp);
			break;
		default:
			status = -EINVAL;
		}
		break;
	case IB_QPS_INIT:
		switch (old_state) {
		case IB_QPS_RESET:
			if (trans_spec) {
				qp_flow = create_and_add_flow(qp_grp,
								trans_spec);
				if (IS_ERR_OR_NULL(qp_flow)) {
					status = qp_flow ? PTR_ERR(qp_flow) : -EFAULT;
					break;
				}
			} else {
				/*
				 * Optional to specify filters.
				 */
				status = 0;
			}
			break;
		case IB_QPS_INIT:
			if (trans_spec) {
				qp_flow = create_and_add_flow(qp_grp,
								trans_spec);
				if (IS_ERR_OR_NULL(qp_flow)) {
					status = qp_flow ? PTR_ERR(qp_flow) : -EFAULT;
					break;
				}
			} else {
				/*
				 * Doesn't make sense to go into INIT state
				 * from INIT state w/o adding filters.
				 */
				status = -EINVAL;
			}
			break;
		case IB_QPS_RTR:
			status = disable_qp_grp(qp_grp);
			break;
		case IB_QPS_RTS:
			status = disable_qp_grp(qp_grp);
			break;
		default:
			status = -EINVAL;
		}
		break;
	case IB_QPS_RTR:
		switch (old_state) {
		case IB_QPS_INIT:
			status = enable_qp_grp(qp_grp);
			break;
		default:
			status = -EINVAL;
		}
		break;
	case IB_QPS_RTS:
		switch (old_state) {
		case IB_QPS_RTR:
			/* NO-OP FOR NOW */
			break;
		default:
			status = -EINVAL;
		}
		break;
	case IB_QPS_ERR:
		ib_event.device = &qp_grp->vf->pf->ib_dev;
		ib_event.element.qp = &qp_grp->ibqp;
		ib_event.event = IB_EVENT_QP_FATAL;

		switch (old_state) {
		case IB_QPS_RESET:
			qp_grp->ibqp.event_handler(&ib_event,
					qp_grp->ibqp.qp_context);
			break;
		case IB_QPS_INIT:
			release_and_remove_all_flows(qp_grp);
			qp_grp->ibqp.event_handler(&ib_event,
					qp_grp->ibqp.qp_context);
			break;
		case IB_QPS_RTR:
		case IB_QPS_RTS:
			status = disable_qp_grp(qp_grp);
			release_and_remove_all_flows(qp_grp);
			qp_grp->ibqp.event_handler(&ib_event,
					qp_grp->ibqp.qp_context);
			break;
		default:
			status = -EINVAL;
		}
		break;
	default:
		status = -EINVAL;
	}
	spin_unlock(&qp_grp->lock);

	if (!status) {
		qp_grp->state = new_state;
		usnic_info("Transitioned %u from %s to %s",
		qp_grp->grp_id,
		usnic_ib_qp_grp_state_to_string(old_state),
		usnic_ib_qp_grp_state_to_string(new_state));
	} else {
		usnic_err("Failed to transition %u from %s to %s",
		qp_grp->grp_id,
		usnic_ib_qp_grp_state_to_string(old_state),
		usnic_ib_qp_grp_state_to_string(new_state));
	}

	return status;
}