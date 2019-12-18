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
struct usb_interface {struct usb_host_interface* cur_altsetting; } ;
struct TYPE_3__ {int bNumEndpoints; } ;
struct usb_host_interface {TYPE_2__* endpoint; TYPE_1__ desc; } ;
struct usb_endpoint_descriptor {int bEndpointAddress; } ;
struct TYPE_4__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int USB_ENDPOINT_DIR_MASK ; 
 int usb_endpoint_type (struct usb_endpoint_descriptor*) ; 

__attribute__((used)) static struct usb_endpoint_descriptor *hso_get_ep(struct usb_interface *intf,
						  int type, int dir)
{
	int i;
	struct usb_host_interface *iface = intf->cur_altsetting;
	struct usb_endpoint_descriptor *endp;

	for (i = 0; i < iface->desc.bNumEndpoints; i++) {
		endp = &iface->endpoint[i].desc;
		if (((endp->bEndpointAddress & USB_ENDPOINT_DIR_MASK) == dir) &&
		    (usb_endpoint_type(endp) == type))
			return endp;
	}

	return NULL;
}