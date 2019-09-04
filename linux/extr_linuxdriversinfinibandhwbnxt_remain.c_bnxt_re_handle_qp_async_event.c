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
struct TYPE_6__ {TYPE_3__* qp; } ;
struct ib_event {int /*<<< orphan*/ * device; int /*<<< orphan*/  event; TYPE_2__ element; } ;
struct creq_qp_event {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  qp_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {scalar_t__ state; scalar_t__ srq; } ;
struct bnxt_re_qp {TYPE_3__ ib_qp; TYPE_1__* rdev; TYPE_4__ qplib_qp; } ;
typedef  int /*<<< orphan*/  event ;
struct TYPE_5__ {int /*<<< orphan*/  ibdev; } ;

/* Variables and functions */
 scalar_t__ CMDQ_MODIFY_QP_NEW_STATE_ERR ; 
 int /*<<< orphan*/  IB_EVENT_QP_LAST_WQE_REACHED ; 
 int /*<<< orphan*/  bnxt_qplib_add_flush_qp (TYPE_4__*) ; 
 unsigned int bnxt_re_lock_cqs (struct bnxt_re_qp*) ; 
 int /*<<< orphan*/  bnxt_re_unlock_cqs (struct bnxt_re_qp*,unsigned int) ; 
 int /*<<< orphan*/  memset (struct ib_event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct ib_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_re_handle_qp_async_event(struct creq_qp_event *qp_event,
					 struct bnxt_re_qp *qp)
{
	struct ib_event event;
	unsigned int flags;

	if (qp->qplib_qp.state == CMDQ_MODIFY_QP_NEW_STATE_ERR) {
		flags = bnxt_re_lock_cqs(qp);
		bnxt_qplib_add_flush_qp(&qp->qplib_qp);
		bnxt_re_unlock_cqs(qp, flags);
	}

	memset(&event, 0, sizeof(event));
	if (qp->qplib_qp.srq) {
		event.device = &qp->rdev->ibdev;
		event.element.qp = &qp->ib_qp;
		event.event = IB_EVENT_QP_LAST_WQE_REACHED;
	}

	if (event.device && qp->ib_qp.event_handler)
		qp->ib_qp.event_handler(&event, qp->ib_qp.qp_context);

	return 0;
}