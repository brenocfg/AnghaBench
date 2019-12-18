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
struct usb_request {int actual; int length; int /*<<< orphan*/  zero; } ;
struct renesas_usb3_request {struct usb_request req; } ;
struct TYPE_2__ {int maxpacket; } ;
struct renesas_usb3_ep {TYPE_1__ ep; } ;

/* Variables and functions */

__attribute__((used)) static bool usb3_is_transfer_complete(struct renesas_usb3_ep *usb3_ep,
				      struct renesas_usb3_request *usb3_req)
{
	struct usb_request *req = &usb3_req->req;

	if ((!req->zero && req->actual == req->length) ||
	    (req->actual % usb3_ep->ep.maxpacket) || (req->length == 0))
		return true;
	else
		return false;
}