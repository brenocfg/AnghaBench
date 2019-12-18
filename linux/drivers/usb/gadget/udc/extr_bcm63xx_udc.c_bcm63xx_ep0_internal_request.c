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
struct usb_request {int length; int /*<<< orphan*/ * complete; int /*<<< orphan*/  buf; } ;
struct TYPE_2__ {struct usb_request req; } ;
struct bcm63xx_udc {int /*<<< orphan*/  ep0_ctrl_buf; TYPE_1__ ep0_ctrl_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm63xx_ep0_map_write (struct bcm63xx_udc*,int,struct usb_request*) ; 

__attribute__((used)) static void bcm63xx_ep0_internal_request(struct bcm63xx_udc *udc, int ch_idx,
	int length)
{
	struct usb_request *req = &udc->ep0_ctrl_req.req;

	req->buf = udc->ep0_ctrl_buf;
	req->length = length;
	req->complete = NULL;

	bcm63xx_ep0_map_write(udc, ch_idx, req);
}