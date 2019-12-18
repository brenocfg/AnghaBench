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
struct TYPE_3__ {scalar_t__ speed; } ;
struct usba_udc {int /*<<< orphan*/  lock; TYPE_1__ gadget; } ;
struct TYPE_4__ {int /*<<< orphan*/ * desc; int /*<<< orphan*/  name; } ;
struct usba_ep {int index; scalar_t__ can_dma; int /*<<< orphan*/  queue; TYPE_2__ ep; struct usba_udc* udc; } ;
struct usb_ep {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDRESS ; 
 int /*<<< orphan*/  CONTROL ; 
 int /*<<< orphan*/  CTL_DIS ; 
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_ERR ; 
 int /*<<< orphan*/  DBG_GADGET ; 
 int EINVAL ; 
 int /*<<< orphan*/  EPT_INT ; 
 int /*<<< orphan*/  ESHUTDOWN ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  USBA_BF (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USBA_EPT_ENABLE ; 
 scalar_t__ USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  req_list ; 
 int /*<<< orphan*/  request_complete_list (struct usba_ep*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct usba_ep* to_usba_ep (struct usb_ep*) ; 
 int /*<<< orphan*/  usba_dma_readl (struct usba_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usba_dma_writel (struct usba_ep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usba_ep_writel (struct usba_ep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usba_int_enb_clear (struct usba_udc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usba_ep_disable(struct usb_ep *_ep)
{
	struct usba_ep *ep = to_usba_ep(_ep);
	struct usba_udc *udc = ep->udc;
	LIST_HEAD(req_list);
	unsigned long flags;

	DBG(DBG_GADGET, "ep_disable: %s\n", ep->ep.name);

	spin_lock_irqsave(&udc->lock, flags);

	if (!ep->ep.desc) {
		spin_unlock_irqrestore(&udc->lock, flags);
		/* REVISIT because this driver disables endpoints in
		 * reset_all_endpoints() before calling disconnect(),
		 * most gadget drivers would trigger this non-error ...
		 */
		if (udc->gadget.speed != USB_SPEED_UNKNOWN)
			DBG(DBG_ERR, "ep_disable: %s not enabled\n",
					ep->ep.name);
		return -EINVAL;
	}
	ep->ep.desc = NULL;

	list_splice_init(&ep->queue, &req_list);
	if (ep->can_dma) {
		usba_dma_writel(ep, CONTROL, 0);
		usba_dma_writel(ep, ADDRESS, 0);
		usba_dma_readl(ep, STATUS);
	}
	usba_ep_writel(ep, CTL_DIS, USBA_EPT_ENABLE);
	usba_int_enb_clear(udc, USBA_BF(EPT_INT, 1 << ep->index));

	request_complete_list(ep, &req_list, -ESHUTDOWN);

	spin_unlock_irqrestore(&udc->lock, flags);

	return 0;
}