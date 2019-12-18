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
struct usb_request {int actual; } ;
struct bcm63xx_udc {struct usb_request* ep0_request; scalar_t__ ep0_req_completed; } ;

/* Variables and functions */

__attribute__((used)) static int bcm63xx_ep0_read_complete(struct bcm63xx_udc *udc)
{
	struct usb_request *req = udc->ep0_request;

	udc->ep0_req_completed = 0;
	udc->ep0_request = NULL;

	return req->actual;
}