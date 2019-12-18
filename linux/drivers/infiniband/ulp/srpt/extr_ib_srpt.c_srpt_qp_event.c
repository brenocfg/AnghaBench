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
struct TYPE_5__ {int /*<<< orphan*/  cm_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  cm_id; } ;
struct srpt_rdma_ch {int /*<<< orphan*/  state; TYPE_3__* qp; int /*<<< orphan*/  sess_name; TYPE_2__ ib_cm; TYPE_1__ rdma_cm; int /*<<< orphan*/  using_rdma_cm; } ;
struct ib_event {int event; } ;
struct TYPE_6__ {int /*<<< orphan*/  qp_num; } ;

/* Variables and functions */
#define  IB_EVENT_COMM_EST 129 
#define  IB_EVENT_QP_LAST_WQE_REACHED 128 
 int /*<<< orphan*/  get_ch_state_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_cm_notify (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,struct srpt_rdma_ch*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  rdma_notify (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void srpt_qp_event(struct ib_event *event, struct srpt_rdma_ch *ch)
{
	pr_debug("QP event %d on ch=%p sess_name=%s state=%d\n",
		 event->event, ch, ch->sess_name, ch->state);

	switch (event->event) {
	case IB_EVENT_COMM_EST:
		if (ch->using_rdma_cm)
			rdma_notify(ch->rdma_cm.cm_id, event->event);
		else
			ib_cm_notify(ch->ib_cm.cm_id, event->event);
		break;
	case IB_EVENT_QP_LAST_WQE_REACHED:
		pr_debug("%s-%d, state %s: received Last WQE event.\n",
			 ch->sess_name, ch->qp->qp_num,
			 get_ch_state_name(ch->state));
		break;
	default:
		pr_err("received unrecognized IB QP event %d\n", event->event);
		break;
	}
}