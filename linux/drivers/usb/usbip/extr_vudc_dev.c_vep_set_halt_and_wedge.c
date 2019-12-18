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
struct vudc {int /*<<< orphan*/  lock; int /*<<< orphan*/  driver; } ;
struct vep {int halted; int wedged; int /*<<< orphan*/  req_queue; TYPE_1__* desc; } ;
struct usb_ep {int dummy; } ;
struct TYPE_2__ {int bEndpointAddress; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int ESHUTDOWN ; 
 int USB_DIR_IN ; 
 struct vudc* ep_to_vudc (struct vep*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vep* to_vep (struct usb_ep*) ; 

__attribute__((used)) static int
vep_set_halt_and_wedge(struct usb_ep *_ep, int value, int wedged)
{
	struct vep *ep;
	struct vudc *udc;
	unsigned long flags;
	int ret = 0;

	ep = to_vep(_ep);
	if (!_ep)
		return -EINVAL;

	udc = ep_to_vudc(ep);
	if (!udc->driver)
		return -ESHUTDOWN;

	spin_lock_irqsave(&udc->lock, flags);
	if (!value)
		ep->halted = ep->wedged = 0;
	else if (ep->desc && (ep->desc->bEndpointAddress & USB_DIR_IN) &&
			!list_empty(&ep->req_queue))
		ret = -EAGAIN;
	else {
		ep->halted = 1;
		if (wedged)
			ep->wedged = 1;
	}

	spin_unlock_irqrestore(&udc->lock, flags);
	return ret;
}