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
struct xusb_udc {int /*<<< orphan*/  lock; } ;
struct xusb_req {int dummy; } ;
struct xusb_ep {struct xusb_udc* udc; } ;
struct usb_request {int dummy; } ;
struct usb_ep {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int __xudc_ep0_queue (struct xusb_ep*,struct xusb_req*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct xusb_ep* to_xusb_ep (struct usb_ep*) ; 
 struct xusb_req* to_xusb_req (struct usb_request*) ; 

__attribute__((used)) static int xudc_ep0_queue(struct usb_ep *_ep, struct usb_request *_req,
			  gfp_t gfp_flags)
{
	struct xusb_req *req	= to_xusb_req(_req);
	struct xusb_ep	*ep0	= to_xusb_ep(_ep);
	struct xusb_udc *udc	= ep0->udc;
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&udc->lock, flags);
	ret = __xudc_ep0_queue(ep0, req);
	spin_unlock_irqrestore(&udc->lock, flags);

	return ret;
}