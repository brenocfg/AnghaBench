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
struct TYPE_4__ {unsigned int bNumEndpoints; } ;
struct usb_host_interface {TYPE_3__* endpoint; TYPE_1__ desc; } ;
struct TYPE_5__ {int bEndpointAddress; int bmAttributes; } ;
struct TYPE_6__ {TYPE_2__ desc; } ;

/* Variables and functions */
 int USB_DIR_IN ; 
 int USB_ENDPOINT_NUMBER_MASK ; 
 int USB_ENDPOINT_XFERTYPE_MASK ; 
 int USB_ENDPOINT_XFER_ISOC ; 

__attribute__((used)) static bool cxusb_medion_check_altsetting(struct usb_host_interface *as)
{
	unsigned int ctr;

	for (ctr = 0; ctr < as->desc.bNumEndpoints; ctr++) {
		if ((as->endpoint[ctr].desc.bEndpointAddress &
		     USB_ENDPOINT_NUMBER_MASK) != 2)
			continue;

		if (as->endpoint[ctr].desc.bEndpointAddress & USB_DIR_IN &&
		    ((as->endpoint[ctr].desc.bmAttributes &
		      USB_ENDPOINT_XFERTYPE_MASK) == USB_ENDPOINT_XFER_ISOC))
			return true;

		break;
	}

	return false;
}