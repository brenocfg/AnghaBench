#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_gadget {TYPE_1__* ep0; int /*<<< orphan*/  dev; } ;
struct usb_composite_driver {int dummy; } ;
struct usb_composite_dev {TYPE_2__* req; struct usb_composite_driver* driver; struct usb_gadget* gadget; } ;
struct TYPE_6__ {int /*<<< orphan*/  buf; struct usb_composite_dev* context; int /*<<< orphan*/  complete; } ;
struct TYPE_5__ {struct usb_composite_dev* driver_data; } ;

/* Variables and functions */
 scalar_t__ CONFIG_USB_GADGET_VBUS_DRAW ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USB_COMP_EP0_BUFSIZ ; 
 scalar_t__ USB_SELF_POWER_VBUS_MAX_DRAW ; 
 int /*<<< orphan*/  composite_setup_complete ; 
 int /*<<< orphan*/  dev_attr_suspended ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* usb_ep_alloc_request (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_ep_autoconfig_reset (struct usb_gadget*) ; 
 int /*<<< orphan*/  usb_ep_free_request (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  usb_gadget_set_selfpowered (struct usb_gadget*) ; 

int composite_dev_prepare(struct usb_composite_driver *composite,
		struct usb_composite_dev *cdev)
{
	struct usb_gadget *gadget = cdev->gadget;
	int ret = -ENOMEM;

	/* preallocate control response and buffer */
	cdev->req = usb_ep_alloc_request(gadget->ep0, GFP_KERNEL);
	if (!cdev->req)
		return -ENOMEM;

	cdev->req->buf = kmalloc(USB_COMP_EP0_BUFSIZ, GFP_KERNEL);
	if (!cdev->req->buf)
		goto fail;

	ret = device_create_file(&gadget->dev, &dev_attr_suspended);
	if (ret)
		goto fail_dev;

	cdev->req->complete = composite_setup_complete;
	cdev->req->context = cdev;
	gadget->ep0->driver_data = cdev;

	cdev->driver = composite;

	/*
	 * As per USB compliance update, a device that is actively drawing
	 * more than 100mA from USB must report itself as bus-powered in
	 * the GetStatus(DEVICE) call.
	 */
	if (CONFIG_USB_GADGET_VBUS_DRAW <= USB_SELF_POWER_VBUS_MAX_DRAW)
		usb_gadget_set_selfpowered(gadget);

	/* interface and string IDs start at zero via kzalloc.
	 * we force endpoints to start unassigned; few controller
	 * drivers will zero ep->driver_data.
	 */
	usb_ep_autoconfig_reset(gadget);
	return 0;
fail_dev:
	kfree(cdev->req->buf);
fail:
	usb_ep_free_request(gadget->ep0, cdev->req);
	cdev->req = NULL;
	return ret;
}