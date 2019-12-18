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
struct usb_ctrlrequest {int wValue; scalar_t__ wLength; scalar_t__ wIndex; int /*<<< orphan*/  bRequest; scalar_t__ bRequestType; } ;
struct pxa_udc {int config; int /*<<< orphan*/ * pxa_ep; int /*<<< orphan*/  gadget; TYPE_1__* driver; scalar_t__ last_alternate; scalar_t__ last_interface; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* setup ) (int /*<<< orphan*/ *,struct usb_ctrlrequest*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  UDCCSR0_AREN ; 
 int /*<<< orphan*/  USB_REQ_SET_CONFIGURATION ; 
 int /*<<< orphan*/  WAIT_ACK_SET_CONF_INTERF ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ep_write_UDCCSR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ep0state (struct pxa_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct usb_ctrlrequest*) ; 

__attribute__((used)) static void pxa27x_change_configuration(struct pxa_udc *udc, int config)
{
	struct usb_ctrlrequest req ;

	dev_dbg(udc->dev, "config=%d\n", config);

	udc->config = config;
	udc->last_interface = 0;
	udc->last_alternate = 0;

	req.bRequestType = 0;
	req.bRequest = USB_REQ_SET_CONFIGURATION;
	req.wValue = config;
	req.wIndex = 0;
	req.wLength = 0;

	set_ep0state(udc, WAIT_ACK_SET_CONF_INTERF);
	udc->driver->setup(&udc->gadget, &req);
	ep_write_UDCCSR(&udc->pxa_ep[0], UDCCSR0_AREN);
}