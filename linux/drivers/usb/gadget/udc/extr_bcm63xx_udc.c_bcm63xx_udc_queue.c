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
struct usb_request {scalar_t__ status; scalar_t__ actual; int /*<<< orphan*/  buf; int /*<<< orphan*/  complete; } ;
struct usb_ep {int dummy; } ;
struct bcm63xx_udc {int /*<<< orphan*/  lock; int /*<<< orphan*/  gadget; int /*<<< orphan*/  ep0_wq; struct usb_request* ep0_reply; struct bcm63xx_ep* bep; } ;
struct bcm63xx_req {int /*<<< orphan*/  queue; scalar_t__ offset; } ;
struct bcm63xx_ep {TYPE_1__* iudma; int /*<<< orphan*/  queue; struct bcm63xx_udc* udc; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  is_tx; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int EINVAL ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  iudma_write (struct bcm63xx_udc*,TYPE_1__*,struct bcm63xx_req*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_is_singular (int /*<<< orphan*/ *) ; 
 struct bcm63xx_ep* our_ep (struct usb_ep*) ; 
 struct bcm63xx_req* our_req (struct usb_request*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int usb_gadget_map_request (int /*<<< orphan*/ *,struct usb_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm63xx_udc_queue(struct usb_ep *ep, struct usb_request *req,
	gfp_t mem_flags)
{
	struct bcm63xx_ep *bep = our_ep(ep);
	struct bcm63xx_udc *udc = bep->udc;
	struct bcm63xx_req *breq = our_req(req);
	unsigned long flags;
	int rc = 0;

	if (unlikely(!req || !req->complete || !req->buf || !ep))
		return -EINVAL;

	req->actual = 0;
	req->status = 0;
	breq->offset = 0;

	if (bep == &udc->bep[0]) {
		/* only one reply per request, please */
		if (udc->ep0_reply)
			return -EINVAL;

		udc->ep0_reply = req;
		schedule_work(&udc->ep0_wq);
		return 0;
	}

	spin_lock_irqsave(&udc->lock, flags);
	if (!bep->iudma->enabled) {
		rc = -ESHUTDOWN;
		goto out;
	}

	rc = usb_gadget_map_request(&udc->gadget, req, bep->iudma->is_tx);
	if (rc == 0) {
		list_add_tail(&breq->queue, &bep->queue);
		if (list_is_singular(&bep->queue))
			iudma_write(udc, bep->iudma, breq);
	}

out:
	spin_unlock_irqrestore(&udc->lock, flags);
	return rc;
}