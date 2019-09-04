#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {TYPE_2__* cur_altsetting; } ;
struct usb_device_id {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct TYPE_8__ {int bNumConfigurations; } ;
struct usb_device {TYPE_4__* actconfig; TYPE_3__ descriptor; } ;
struct sd_desc {int dummy; } ;
struct module {int dummy; } ;
struct TYPE_10__ {int bNumInterfaces; } ;
struct TYPE_9__ {TYPE_5__ desc; } ;
struct TYPE_6__ {scalar_t__ bInterfaceNumber; } ;
struct TYPE_7__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int ENODEV ; 
 int gspca_dev_probe2 (struct usb_interface*,struct usb_device_id const*,struct sd_desc const*,int,struct module*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int gspca_dev_probe(struct usb_interface *intf,
		const struct usb_device_id *id,
		const struct sd_desc *sd_desc,
		int dev_size,
		struct module *module)
{
	struct usb_device *dev = interface_to_usbdev(intf);

	/* we don't handle multi-config cameras */
	if (dev->descriptor.bNumConfigurations != 1) {
		pr_err("%04x:%04x too many config\n",
		       id->idVendor, id->idProduct);
		return -ENODEV;
	}

	/* the USB video interface must be the first one */
	if (dev->actconfig->desc.bNumInterfaces != 1
	 && intf->cur_altsetting->desc.bInterfaceNumber != 0)
		return -ENODEV;

	return gspca_dev_probe2(intf, id, sd_desc, dev_size, module);
}