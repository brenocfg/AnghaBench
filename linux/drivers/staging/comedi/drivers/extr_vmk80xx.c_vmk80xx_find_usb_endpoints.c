#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vmk80xx_private {struct usb_endpoint_descriptor* ep_tx; struct usb_endpoint_descriptor* ep_rx; } ;
struct usb_interface {struct usb_host_interface* cur_altsetting; } ;
struct TYPE_3__ {int bNumEndpoints; } ;
struct usb_host_interface {TYPE_2__* endpoint; TYPE_1__ desc; } ;
struct usb_endpoint_descriptor {int dummy; } ;
struct comedi_device {struct vmk80xx_private* private; } ;
struct TYPE_4__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int ENODEV ; 
 struct usb_interface* comedi_to_usb_interface (struct comedi_device*) ; 
 scalar_t__ usb_endpoint_is_bulk_in (struct usb_endpoint_descriptor*) ; 
 scalar_t__ usb_endpoint_is_bulk_out (struct usb_endpoint_descriptor*) ; 
 scalar_t__ usb_endpoint_is_int_in (struct usb_endpoint_descriptor*) ; 
 scalar_t__ usb_endpoint_is_int_out (struct usb_endpoint_descriptor*) ; 

__attribute__((used)) static int vmk80xx_find_usb_endpoints(struct comedi_device *dev)
{
	struct vmk80xx_private *devpriv = dev->private;
	struct usb_interface *intf = comedi_to_usb_interface(dev);
	struct usb_host_interface *iface_desc = intf->cur_altsetting;
	struct usb_endpoint_descriptor *ep_desc;
	int i;

	if (iface_desc->desc.bNumEndpoints != 2)
		return -ENODEV;

	for (i = 0; i < iface_desc->desc.bNumEndpoints; i++) {
		ep_desc = &iface_desc->endpoint[i].desc;

		if (usb_endpoint_is_int_in(ep_desc) ||
		    usb_endpoint_is_bulk_in(ep_desc)) {
			if (!devpriv->ep_rx)
				devpriv->ep_rx = ep_desc;
			continue;
		}

		if (usb_endpoint_is_int_out(ep_desc) ||
		    usb_endpoint_is_bulk_out(ep_desc)) {
			if (!devpriv->ep_tx)
				devpriv->ep_tx = ep_desc;
			continue;
		}
	}

	if (!devpriv->ep_rx || !devpriv->ep_tx)
		return -ENODEV;

	return 0;
}