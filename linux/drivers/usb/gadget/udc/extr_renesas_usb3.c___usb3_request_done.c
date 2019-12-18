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
struct TYPE_2__ {int status; int /*<<< orphan*/  actual; int /*<<< orphan*/  length; } ;
struct renesas_usb3_request {TYPE_1__ req; int /*<<< orphan*/  queue; } ;
struct renesas_usb3_ep {int started; int /*<<< orphan*/  ep; int /*<<< orphan*/  num; } ;
struct renesas_usb3 {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct renesas_usb3* usb3_ep_to_usb3 (struct renesas_usb3_ep*) ; 
 int /*<<< orphan*/  usb3_to_dev (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb_gadget_giveback_request (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void __usb3_request_done(struct renesas_usb3_ep *usb3_ep,
				struct renesas_usb3_request *usb3_req,
				int status)
{
	struct renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);

	dev_dbg(usb3_to_dev(usb3), "giveback: ep%2d, %u, %u, %d\n",
		usb3_ep->num, usb3_req->req.length, usb3_req->req.actual,
		status);
	usb3_req->req.status = status;
	usb3_ep->started = false;
	list_del_init(&usb3_req->queue);
	spin_unlock(&usb3->lock);
	usb_gadget_giveback_request(&usb3_ep->ep, &usb3_req->req);
	spin_lock(&usb3->lock);
}