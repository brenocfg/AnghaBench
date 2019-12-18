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
struct usb_request {int dummy; } ;
struct usb_composite_dev {int setup_pending; int os_desc_pending; struct usb_request* os_desc_req; struct usb_request* req; TYPE_1__* gadget; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  ep0; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,struct usb_request*) ; 
 int usb_ep_queue (int /*<<< orphan*/ ,struct usb_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int composite_ep0_queue(struct usb_composite_dev *cdev,
		struct usb_request *req, gfp_t gfp_flags)
{
	int ret;

	ret = usb_ep_queue(cdev->gadget->ep0, req, gfp_flags);
	if (ret == 0) {
		if (cdev->req == req)
			cdev->setup_pending = true;
		else if (cdev->os_desc_req == req)
			cdev->os_desc_pending = true;
		else
			WARN(1, "unknown request %p\n", req);
	}

	return ret;
}