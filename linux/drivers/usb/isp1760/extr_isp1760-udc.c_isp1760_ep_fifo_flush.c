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
struct usb_ep {int dummy; } ;
struct isp1760_udc {int /*<<< orphan*/  lock; } ;
struct isp1760_ep {struct isp1760_udc* udc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_CLBUF ; 
 int /*<<< orphan*/  DC_CTRLFUNC ; 
 struct isp1760_ep* ep_to_udc_ep (struct usb_ep*) ; 
 int /*<<< orphan*/  isp1760_udc_select_ep (struct isp1760_ep*) ; 
 int /*<<< orphan*/  isp1760_udc_write (struct isp1760_udc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void isp1760_ep_fifo_flush(struct usb_ep *ep)
{
	struct isp1760_ep *uep = ep_to_udc_ep(ep);
	struct isp1760_udc *udc = uep->udc;
	unsigned long flags;

	spin_lock_irqsave(&udc->lock, flags);

	isp1760_udc_select_ep(uep);

	/*
	 * Set the CLBUF bit twice to flush both buffers in case double
	 * buffering is enabled.
	 */
	isp1760_udc_write(udc, DC_CTRLFUNC, DC_CLBUF);
	isp1760_udc_write(udc, DC_CTRLFUNC, DC_CLBUF);

	spin_unlock_irqrestore(&udc->lock, flags);
}