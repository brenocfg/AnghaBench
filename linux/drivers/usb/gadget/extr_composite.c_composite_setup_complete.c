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
struct usb_request {scalar_t__ actual; scalar_t__ length; struct usb_composite_dev* context; scalar_t__ status; } ;
struct usb_ep {scalar_t__ driver_data; } ;
struct usb_composite_dev {int setup_pending; int os_desc_pending; struct usb_request* os_desc_req; struct usb_request* req; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct usb_composite_dev*,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  WARN (int,char*,struct usb_request*) ; 

__attribute__((used)) static void composite_setup_complete(struct usb_ep *ep, struct usb_request *req)
{
	struct usb_composite_dev *cdev;

	if (req->status || req->actual != req->length)
		DBG((struct usb_composite_dev *) ep->driver_data,
				"setup complete --> %d, %d/%d\n",
				req->status, req->actual, req->length);

	/*
	 * REVIST The same ep0 requests are shared with function drivers
	 * so they don't have to maintain the same ->complete() stubs.
	 *
	 * Because of that, we need to check for the validity of ->context
	 * here, even though we know we've set it to something useful.
	 */
	if (!req->context)
		return;

	cdev = req->context;

	if (cdev->req == req)
		cdev->setup_pending = false;
	else if (cdev->os_desc_req == req)
		cdev->os_desc_pending = false;
	else
		WARN(1, "unknown request %p\n", req);
}