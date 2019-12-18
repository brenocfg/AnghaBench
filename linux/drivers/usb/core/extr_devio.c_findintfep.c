#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {unsigned int num_altsetting; struct usb_host_interface* altsetting; } ;
struct TYPE_8__ {unsigned int bNumEndpoints; int bInterfaceNumber; } ;
struct usb_host_interface {TYPE_4__ desc; TYPE_3__* endpoint; } ;
struct usb_endpoint_descriptor {unsigned int bEndpointAddress; } ;
struct usb_device {TYPE_2__* actconfig; } ;
struct TYPE_7__ {struct usb_endpoint_descriptor desc; } ;
struct TYPE_5__ {unsigned int bNumInterfaces; } ;
struct TYPE_6__ {struct usb_interface** interface; TYPE_1__ desc; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ESRCH ; 
 int USB_DIR_IN ; 

__attribute__((used)) static int findintfep(struct usb_device *dev, unsigned int ep)
{
	unsigned int i, j, e;
	struct usb_interface *intf;
	struct usb_host_interface *alts;
	struct usb_endpoint_descriptor *endpt;

	if (ep & ~(USB_DIR_IN|0xf))
		return -EINVAL;
	if (!dev->actconfig)
		return -ESRCH;
	for (i = 0; i < dev->actconfig->desc.bNumInterfaces; i++) {
		intf = dev->actconfig->interface[i];
		for (j = 0; j < intf->num_altsetting; j++) {
			alts = &intf->altsetting[j];
			for (e = 0; e < alts->desc.bNumEndpoints; e++) {
				endpt = &alts->endpoint[e].desc;
				if (endpt->bEndpointAddress == ep)
					return alts->desc.bInterfaceNumber;
			}
		}
	}
	return -ENOENT;
}