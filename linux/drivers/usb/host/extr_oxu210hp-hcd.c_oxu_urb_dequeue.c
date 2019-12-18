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
struct TYPE_2__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {TYPE_1__ self; int /*<<< orphan*/  state; } ;
struct urb {scalar_t__ hcpriv; int /*<<< orphan*/  pipe; } ;
struct oxu_hcd {int /*<<< orphan*/  lock; } ;
struct ehci_qh {int /*<<< orphan*/  qtd_list; int /*<<< orphan*/  qh_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HC_IS_RUNNING (int /*<<< orphan*/ ) ; 
#define  PIPE_BULK 132 
#define  PIPE_CONTROL 131 
#define  PIPE_INTERRUPT 130 
#define  QH_STATE_IDLE 129 
#define  QH_STATE_LINKED 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,struct ehci_qh*,int) ; 
 struct oxu_hcd* hcd_to_oxu (struct usb_hcd*) ; 
 int /*<<< orphan*/  intr_deschedule (struct oxu_hcd*,struct ehci_qh*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oxu_dbg (struct oxu_hcd*,char*,struct ehci_qh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qh_completions (struct oxu_hcd*,struct ehci_qh*) ; 
 int qh_schedule (struct oxu_hcd*,struct ehci_qh*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  unlink_async (struct oxu_hcd*,struct ehci_qh*) ; 
 int usb_pipetype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int oxu_urb_dequeue(struct usb_hcd *hcd, struct urb *urb, int status)
{
	struct oxu_hcd *oxu = hcd_to_oxu(hcd);
	struct ehci_qh *qh;
	unsigned long flags;

	spin_lock_irqsave(&oxu->lock, flags);
	switch (usb_pipetype(urb->pipe)) {
	case PIPE_CONTROL:
	case PIPE_BULK:
	default:
		qh = (struct ehci_qh *) urb->hcpriv;
		if (!qh)
			break;
		unlink_async(oxu, qh);
		break;

	case PIPE_INTERRUPT:
		qh = (struct ehci_qh *) urb->hcpriv;
		if (!qh)
			break;
		switch (qh->qh_state) {
		case QH_STATE_LINKED:
			intr_deschedule(oxu, qh);
			/* FALL THROUGH */
		case QH_STATE_IDLE:
			qh_completions(oxu, qh);
			break;
		default:
			oxu_dbg(oxu, "bogus qh %p state %d\n",
					qh, qh->qh_state);
			goto done;
		}

		/* reschedule QH iff another request is queued */
		if (!list_empty(&qh->qtd_list)
				&& HC_IS_RUNNING(hcd->state)) {
			int status;

			status = qh_schedule(oxu, qh);
			spin_unlock_irqrestore(&oxu->lock, flags);

			if (status != 0) {
				/* shouldn't happen often, but ...
				 * FIXME kill those tds' urbs
				 */
				dev_err(hcd->self.controller,
					"can't reschedule qh %p, err %d\n", qh,
					status);
			}
			return status;
		}
		break;
	}
done:
	spin_unlock_irqrestore(&oxu->lock, flags);
	return 0;
}