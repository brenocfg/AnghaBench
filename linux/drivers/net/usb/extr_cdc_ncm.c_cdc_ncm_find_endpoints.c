#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct usbnet {int /*<<< orphan*/  udev; int /*<<< orphan*/  out; int /*<<< orphan*/  in; struct usb_host_endpoint* status; } ;
struct usb_interface {TYPE_2__* cur_altsetting; } ;
struct TYPE_7__ {int bmAttributes; int bEndpointAddress; } ;
struct usb_host_endpoint {TYPE_3__ desc; } ;
struct TYPE_5__ {scalar_t__ bNumEndpoints; } ;
struct TYPE_6__ {struct usb_host_endpoint* endpoint; TYPE_1__ desc; } ;

/* Variables and functions */
 int USB_ENDPOINT_NUMBER_MASK ; 
 int USB_ENDPOINT_XFERTYPE_MASK ; 
#define  USB_ENDPOINT_XFER_BULK 129 
#define  USB_ENDPOINT_XFER_INT 128 
 int /*<<< orphan*/  usb_endpoint_dir_in (TYPE_3__*) ; 
 int /*<<< orphan*/  usb_endpoint_maxp (TYPE_3__*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
cdc_ncm_find_endpoints(struct usbnet *dev, struct usb_interface *intf)
{
	struct usb_host_endpoint *e, *in = NULL, *out = NULL;
	u8 ep;

	for (ep = 0; ep < intf->cur_altsetting->desc.bNumEndpoints; ep++) {
		e = intf->cur_altsetting->endpoint + ep;

		/* ignore endpoints which cannot transfer data */
		if (!usb_endpoint_maxp(&e->desc))
			continue;

		switch (e->desc.bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) {
		case USB_ENDPOINT_XFER_INT:
			if (usb_endpoint_dir_in(&e->desc)) {
				if (!dev->status)
					dev->status = e;
			}
			break;

		case USB_ENDPOINT_XFER_BULK:
			if (usb_endpoint_dir_in(&e->desc)) {
				if (!in)
					in = e;
			} else {
				if (!out)
					out = e;
			}
			break;

		default:
			break;
		}
	}
	if (in && !dev->in)
		dev->in = usb_rcvbulkpipe(dev->udev,
					  in->desc.bEndpointAddress &
					  USB_ENDPOINT_NUMBER_MASK);
	if (out && !dev->out)
		dev->out = usb_sndbulkpipe(dev->udev,
					   out->desc.bEndpointAddress &
					   USB_ENDPOINT_NUMBER_MASK);
}