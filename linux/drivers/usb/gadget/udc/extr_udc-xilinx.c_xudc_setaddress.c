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
struct xusb_udc {int /*<<< orphan*/  dev; struct xusb_req* req; struct xusb_ep* ep; } ;
struct TYPE_2__ {scalar_t__ length; } ;
struct xusb_req {TYPE_1__ usb_req; } ;
struct xusb_ep {int dummy; } ;

/* Variables and functions */
 int __xudc_ep0_queue (struct xusb_ep*,struct xusb_req*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xudc_ep0_stall (struct xusb_udc*) ; 

__attribute__((used)) static void xudc_setaddress(struct xusb_udc *udc)
{
	struct xusb_ep *ep0	= &udc->ep[0];
	struct xusb_req *req	= udc->req;
	int ret;

	req->usb_req.length = 0;
	ret = __xudc_ep0_queue(ep0, req);
	if (ret == 0)
		return;

	dev_err(udc->dev, "Can't respond to SET ADDRESS request\n");
	xudc_ep0_stall(udc);
}