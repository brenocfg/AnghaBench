#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct urb {TYPE_2__* ep; } ;
struct list_head {int dummy; } ;
struct fotg210_qh {scalar_t__ qh_state; } ;
struct fotg210_hcd {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_10__ {int /*<<< orphan*/  bandwidth_int_reqs; } ;
struct TYPE_11__ {TYPE_3__ self; } ;
struct TYPE_8__ {unsigned int bEndpointAddress; } ;
struct TYPE_9__ {int /*<<< orphan*/  hcpriv; TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  HCD_HW_ACCESSIBLE (TYPE_4__*) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 scalar_t__ QH_STATE_IDLE ; 
 TYPE_4__* fotg210_to_hcd (struct fotg210_hcd*) ; 
 struct fotg210_qh* qh_append_tds (struct fotg210_hcd*,struct urb*,struct list_head*,unsigned int,int /*<<< orphan*/ *) ; 
 int qh_schedule (struct fotg210_hcd*,struct fotg210_qh*) ; 
 int /*<<< orphan*/  qtd_list_free (struct fotg210_hcd*,struct urb*,struct list_head*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int usb_hcd_link_urb_to_ep (TYPE_4__*,struct urb*) ; 
 int /*<<< orphan*/  usb_hcd_unlink_urb_from_ep (TYPE_4__*,struct urb*) ; 

__attribute__((used)) static int intr_submit(struct fotg210_hcd *fotg210, struct urb *urb,
		struct list_head *qtd_list, gfp_t mem_flags)
{
	unsigned epnum;
	unsigned long flags;
	struct fotg210_qh *qh;
	int status;
	struct list_head empty;

	/* get endpoint and transfer/schedule data */
	epnum = urb->ep->desc.bEndpointAddress;

	spin_lock_irqsave(&fotg210->lock, flags);

	if (unlikely(!HCD_HW_ACCESSIBLE(fotg210_to_hcd(fotg210)))) {
		status = -ESHUTDOWN;
		goto done_not_linked;
	}
	status = usb_hcd_link_urb_to_ep(fotg210_to_hcd(fotg210), urb);
	if (unlikely(status))
		goto done_not_linked;

	/* get qh and force any scheduling errors */
	INIT_LIST_HEAD(&empty);
	qh = qh_append_tds(fotg210, urb, &empty, epnum, &urb->ep->hcpriv);
	if (qh == NULL) {
		status = -ENOMEM;
		goto done;
	}
	if (qh->qh_state == QH_STATE_IDLE) {
		status = qh_schedule(fotg210, qh);
		if (status)
			goto done;
	}

	/* then queue the urb's tds to the qh */
	qh = qh_append_tds(fotg210, urb, qtd_list, epnum, &urb->ep->hcpriv);
	BUG_ON(qh == NULL);

	/* ... update usbfs periodic stats */
	fotg210_to_hcd(fotg210)->self.bandwidth_int_reqs++;

done:
	if (unlikely(status))
		usb_hcd_unlink_urb_from_ep(fotg210_to_hcd(fotg210), urb);
done_not_linked:
	spin_unlock_irqrestore(&fotg210->lock, flags);
	if (status)
		qtd_list_free(fotg210, urb, qtd_list);

	return status;
}