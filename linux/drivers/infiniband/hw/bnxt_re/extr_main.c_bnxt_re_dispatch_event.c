#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ib_qp {int /*<<< orphan*/  qp_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  port_num; struct ib_qp* qp; } ;
struct ib_event {int event; TYPE_1__ element; struct ib_device* device; } ;
struct ib_device {int dummy; } ;
typedef  enum ib_event_type { ____Placeholder_ib_event_type } ib_event_type ;

/* Variables and functions */
 int /*<<< orphan*/  ib_dispatch_event (struct ib_event*) ; 
 int /*<<< orphan*/  stub1 (struct ib_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnxt_re_dispatch_event(struct ib_device *ibdev, struct ib_qp *qp,
				   u8 port_num, enum ib_event_type event)
{
	struct ib_event ib_event;

	ib_event.device = ibdev;
	if (qp) {
		ib_event.element.qp = qp;
		ib_event.event = event;
		if (qp->event_handler)
			qp->event_handler(&ib_event, qp->qp_context);

	} else {
		ib_event.element.port_num = port_num;
		ib_event.event = event;
		ib_dispatch_event(&ib_event);
	}
}