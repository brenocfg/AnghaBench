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
struct qedr_iw_ep {TYPE_2__* qp; struct qedr_dev* dev; } ;
struct qedr_dev {int dummy; } ;
struct qed_iwarp_cm_event_params {int dummy; } ;
struct ib_qp {int /*<<< orphan*/  qp_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  device; } ;
struct TYPE_3__ {struct ib_qp* qp; } ;
struct ib_event {int event; TYPE_1__ element; int /*<<< orphan*/  device; } ;
typedef  enum ib_event_type { ____Placeholder_ib_event_type } ib_event_type ;
struct TYPE_4__ {struct ib_qp ibqp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qedr_dev*,char*,char*) ; 
 int /*<<< orphan*/  stub1 (struct ib_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qedr_iw_qp_event(void *context,
		 struct qed_iwarp_cm_event_params *params,
		 enum ib_event_type ib_event, char *str)
{
	struct qedr_iw_ep *ep = (struct qedr_iw_ep *)context;
	struct qedr_dev *dev = ep->dev;
	struct ib_qp *ibqp = &ep->qp->ibqp;
	struct ib_event event;

	DP_NOTICE(dev, "QP error received: %s\n", str);

	if (ibqp->event_handler) {
		event.event = ib_event;
		event.device = ibqp->device;
		event.element.qp = ibqp;
		ibqp->event_handler(&event, ibqp->qp_context);
	}
}