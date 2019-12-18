#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct uvc_device {int quirks; int /*<<< orphan*/ * status; TYPE_2__* udev; int /*<<< orphan*/ * int_urb; struct usb_host_endpoint* int_ep; } ;
struct TYPE_4__ {int bInterval; int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_host_endpoint {TYPE_1__ desc; } ;
struct TYPE_5__ {scalar_t__ speed; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int /*<<< orphan*/  UVC_MAX_STATUS_SIZE ; 
 int UVC_QUIRK_STATUS_INTERVAL ; 
 int fls (int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_int_urb (int /*<<< orphan*/ *,TYPE_2__*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uvc_device*,int) ; 
 unsigned int usb_rcvintpipe (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvc_input_init (struct uvc_device*) ; 
 int /*<<< orphan*/  uvc_status_complete ; 

int uvc_status_init(struct uvc_device *dev)
{
	struct usb_host_endpoint *ep = dev->int_ep;
	unsigned int pipe;
	int interval;

	if (ep == NULL)
		return 0;

	uvc_input_init(dev);

	dev->status = kzalloc(UVC_MAX_STATUS_SIZE, GFP_KERNEL);
	if (dev->status == NULL)
		return -ENOMEM;

	dev->int_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (dev->int_urb == NULL) {
		kfree(dev->status);
		return -ENOMEM;
	}

	pipe = usb_rcvintpipe(dev->udev, ep->desc.bEndpointAddress);

	/* For high-speed interrupt endpoints, the bInterval value is used as
	 * an exponent of two. Some developers forgot about it.
	 */
	interval = ep->desc.bInterval;
	if (interval > 16 && dev->udev->speed == USB_SPEED_HIGH &&
	    (dev->quirks & UVC_QUIRK_STATUS_INTERVAL))
		interval = fls(interval) - 1;

	usb_fill_int_urb(dev->int_urb, dev->udev, pipe,
		dev->status, UVC_MAX_STATUS_SIZE, uvc_status_complete,
		dev, interval);

	return 0;
}