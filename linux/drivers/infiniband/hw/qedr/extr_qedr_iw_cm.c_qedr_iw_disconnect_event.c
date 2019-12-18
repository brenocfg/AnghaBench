#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct qedr_qp {int /*<<< orphan*/  ibqp; } ;
struct qedr_iw_ep {struct qedr_qp* qp; struct qedr_dev* dev; } ;
struct qedr_discon_work {int /*<<< orphan*/  work; int /*<<< orphan*/  status; int /*<<< orphan*/  event; struct qedr_iw_ep* ep; } ;
struct qedr_dev {int /*<<< orphan*/  iwarp_wq; } ;
struct qed_iwarp_cm_event_params {int /*<<< orphan*/  status; int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct qedr_discon_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedr_iw_disconnect_worker ; 
 int /*<<< orphan*/  qedr_iw_qp_add_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qedr_iw_disconnect_event(void *context,
			 struct qed_iwarp_cm_event_params *params)
{
	struct qedr_discon_work *work;
	struct qedr_iw_ep *ep = (struct qedr_iw_ep *)context;
	struct qedr_dev *dev = ep->dev;
	struct qedr_qp *qp = ep->qp;

	work = kzalloc(sizeof(*work), GFP_ATOMIC);
	if (!work)
		return;

	qedr_iw_qp_add_ref(&qp->ibqp);
	work->ep = ep;
	work->event = params->event;
	work->status = params->status;

	INIT_WORK(&work->work, qedr_iw_disconnect_worker);
	queue_work(dev->iwarp_wq, &work->work);
}