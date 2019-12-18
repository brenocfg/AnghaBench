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
struct usb_interface {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct usb_device {TYPE_3__* actconfig; TYPE_1__ descriptor; } ;
struct TYPE_5__ {int bNumInterfaces; } ;
struct TYPE_6__ {TYPE_2__ desc; } ;

/* Variables and functions */
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool quectel_ec20_detected(struct usb_interface *intf)
{
	struct usb_device *dev = interface_to_usbdev(intf);

	if (dev->actconfig &&
	    le16_to_cpu(dev->descriptor.idVendor) == 0x05c6 &&
	    le16_to_cpu(dev->descriptor.idProduct) == 0x9215 &&
	    dev->actconfig->desc.bNumInterfaces == 5)
		return true;

	return false;
}