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
struct TYPE_3__ {int flags; } ;
struct siw_qp {TYPE_1__ attrs; struct ib_qp* ib_qp; } ;
struct ib_qp {int /*<<< orphan*/  qp_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  device; } ;
struct TYPE_4__ {struct ib_qp* qp; } ;
struct ib_event {int event; TYPE_2__ element; int /*<<< orphan*/  device; } ;
typedef  enum ib_event_type { ____Placeholder_ib_event_type } ib_event_type ;

/* Variables and functions */
 int SIW_QP_IN_DESTROY ; 
 int /*<<< orphan*/  siw_dbg_qp (struct siw_qp*,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct ib_event*,int /*<<< orphan*/ ) ; 

void siw_qp_event(struct siw_qp *qp, enum ib_event_type etype)
{
	struct ib_event event;
	struct ib_qp *base_qp = qp->ib_qp;

	/*
	 * Do not report asynchronous errors on QP which gets
	 * destroyed via verbs interface (siw_destroy_qp())
	 */
	if (qp->attrs.flags & SIW_QP_IN_DESTROY)
		return;

	event.event = etype;
	event.device = base_qp->device;
	event.element.qp = base_qp;

	if (base_qp->event_handler) {
		siw_dbg_qp(qp, "reporting event %d\n", etype);
		base_qp->event_handler(&event, base_qp->qp_context);
	}
}