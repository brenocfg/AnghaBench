#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_ep {int dummy; } ;
struct usb_composite_dev {TYPE_1__* os_desc_req; } ;
struct TYPE_3__ {int /*<<< orphan*/  complete; struct usb_composite_dev* context; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USB_COMP_EP0_OS_DESC_BUFSIZ ; 
 int /*<<< orphan*/  composite_setup_complete ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* usb_ep_alloc_request (struct usb_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_ep_free_request (struct usb_ep*,TYPE_1__*) ; 

int composite_os_desc_req_prepare(struct usb_composite_dev *cdev,
				  struct usb_ep *ep0)
{
	int ret = 0;

	cdev->os_desc_req = usb_ep_alloc_request(ep0, GFP_KERNEL);
	if (!cdev->os_desc_req) {
		ret = -ENOMEM;
		goto end;
	}

	cdev->os_desc_req->buf = kmalloc(USB_COMP_EP0_OS_DESC_BUFSIZ,
					 GFP_KERNEL);
	if (!cdev->os_desc_req->buf) {
		ret = -ENOMEM;
		usb_ep_free_request(ep0, cdev->os_desc_req);
		goto end;
	}
	cdev->os_desc_req->context = cdev;
	cdev->os_desc_req->complete = composite_setup_complete;
end:
	return ret;
}