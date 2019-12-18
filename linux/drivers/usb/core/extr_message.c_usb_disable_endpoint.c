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
struct usb_host_endpoint {scalar_t__ enabled; } ;
struct usb_device {struct usb_host_endpoint** ep_in; struct usb_host_endpoint** ep_out; } ;

/* Variables and functions */
 unsigned int USB_ENDPOINT_NUMBER_MASK ; 
 scalar_t__ usb_endpoint_out (unsigned int) ; 
 int /*<<< orphan*/  usb_hcd_disable_endpoint (struct usb_device*,struct usb_host_endpoint*) ; 
 int /*<<< orphan*/  usb_hcd_flush_endpoint (struct usb_device*,struct usb_host_endpoint*) ; 

void usb_disable_endpoint(struct usb_device *dev, unsigned int epaddr,
		bool reset_hardware)
{
	unsigned int epnum = epaddr & USB_ENDPOINT_NUMBER_MASK;
	struct usb_host_endpoint *ep;

	if (!dev)
		return;

	if (usb_endpoint_out(epaddr)) {
		ep = dev->ep_out[epnum];
		if (reset_hardware)
			dev->ep_out[epnum] = NULL;
	} else {
		ep = dev->ep_in[epnum];
		if (reset_hardware)
			dev->ep_in[epnum] = NULL;
	}
	if (ep) {
		ep->enabled = 0;
		usb_hcd_flush_endpoint(dev, ep);
		if (reset_hardware)
			usb_hcd_disable_endpoint(dev, ep);
	}
}