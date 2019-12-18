#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int bNumEndpoints; } ;
struct usb_host_interface {TYPE_3__* endpoint; TYPE_2__ desc; } ;
struct usb_endpoint_descriptor {scalar_t__ bEndpointAddress; } ;
struct kvaser_usb {struct usb_endpoint_descriptor* bulk_out; struct usb_endpoint_descriptor* bulk_in; TYPE_1__* intf; } ;
struct TYPE_6__ {struct usb_endpoint_descriptor desc; } ;
struct TYPE_4__ {struct usb_host_interface* altsetting; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ KVASER_USB_HYDRA_BULK_EP_IN_ADDR ; 
 scalar_t__ KVASER_USB_HYDRA_BULK_EP_OUT_ADDR ; 
 scalar_t__ usb_endpoint_is_bulk_in (struct usb_endpoint_descriptor*) ; 
 scalar_t__ usb_endpoint_is_bulk_out (struct usb_endpoint_descriptor*) ; 

__attribute__((used)) static int kvaser_usb_hydra_setup_endpoints(struct kvaser_usb *dev)
{
	const struct usb_host_interface *iface_desc;
	struct usb_endpoint_descriptor *ep;
	int i;

	iface_desc = &dev->intf->altsetting[0];

	for (i = 0; i < iface_desc->desc.bNumEndpoints; ++i) {
		ep = &iface_desc->endpoint[i].desc;

		if (!dev->bulk_in && usb_endpoint_is_bulk_in(ep) &&
		    ep->bEndpointAddress == KVASER_USB_HYDRA_BULK_EP_IN_ADDR)
			dev->bulk_in = ep;

		if (!dev->bulk_out && usb_endpoint_is_bulk_out(ep) &&
		    ep->bEndpointAddress == KVASER_USB_HYDRA_BULK_EP_OUT_ADDR)
			dev->bulk_out = ep;

		if (dev->bulk_in && dev->bulk_out)
			return 0;
	}

	return -ENODEV;
}