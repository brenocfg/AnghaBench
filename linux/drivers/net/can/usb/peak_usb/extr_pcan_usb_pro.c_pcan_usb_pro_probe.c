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
struct usb_interface {struct usb_host_interface* altsetting; } ;
struct TYPE_3__ {int bNumEndpoints; } ;
struct usb_host_interface {TYPE_2__* endpoint; TYPE_1__ desc; } ;
struct usb_endpoint_descriptor {int bEndpointAddress; } ;
struct TYPE_4__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int ENODEV ; 
#define  PCAN_USBPRO_EP_CMDIN 133 
#define  PCAN_USBPRO_EP_CMDOUT 132 
#define  PCAN_USBPRO_EP_MSGIN 131 
#define  PCAN_USBPRO_EP_MSGOUT_0 130 
#define  PCAN_USBPRO_EP_MSGOUT_1 129 
#define  PCAN_USBPRO_EP_UNUSED 128 

int pcan_usb_pro_probe(struct usb_interface *intf)
{
	struct usb_host_interface *if_desc;
	int i;

	if_desc = intf->altsetting;

	/* check interface endpoint addresses */
	for (i = 0; i < if_desc->desc.bNumEndpoints; i++) {
		struct usb_endpoint_descriptor *ep = &if_desc->endpoint[i].desc;

		/*
		 * below is the list of valid ep addreses. Any other ep address
		 * is considered as not-CAN interface address => no dev created
		 */
		switch (ep->bEndpointAddress) {
		case PCAN_USBPRO_EP_CMDOUT:
		case PCAN_USBPRO_EP_CMDIN:
		case PCAN_USBPRO_EP_MSGOUT_0:
		case PCAN_USBPRO_EP_MSGOUT_1:
		case PCAN_USBPRO_EP_MSGIN:
		case PCAN_USBPRO_EP_UNUSED:
			break;
		default:
			return -ENODEV;
		}
	}

	return 0;
}