#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int dummy; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; int /*<<< orphan*/  iManufacturer; } ;
struct usb_device {int /*<<< orphan*/  dev; TYPE_1__ descriptor; } ;
typedef  int /*<<< orphan*/  manufacturer ;

/* Variables and functions */
 int ENODEV ; 
 int USB_VID_TERRATEC ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int dvb_usbv2_probe (struct usb_interface*,struct usb_device_id const*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  usb_string (struct usb_device*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int af9035_probe(struct usb_interface *intf,
		const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(intf);
	char manufacturer[sizeof("Afatech")];

	memset(manufacturer, 0, sizeof(manufacturer));
	usb_string(udev, udev->descriptor.iManufacturer,
			manufacturer, sizeof(manufacturer));
	/*
	 * There is two devices having same ID but different chipset. One uses
	 * AF9015 and the other IT9135 chipset. Only difference seen on lsusb
	 * is iManufacturer string.
	 *
	 * idVendor           0x0ccd TerraTec Electronic GmbH
	 * idProduct          0x0099
	 * bcdDevice            2.00
	 * iManufacturer           1 Afatech
	 * iProduct                2 DVB-T 2
	 *
	 * idVendor           0x0ccd TerraTec Electronic GmbH
	 * idProduct          0x0099
	 * bcdDevice            2.00
	 * iManufacturer           1 ITE Technologies, Inc.
	 * iProduct                2 DVB-T TV Stick
	 */
	if ((le16_to_cpu(udev->descriptor.idVendor) == USB_VID_TERRATEC) &&
			(le16_to_cpu(udev->descriptor.idProduct) == 0x0099)) {
		if (!strcmp("Afatech", manufacturer)) {
			dev_dbg(&udev->dev, "rejecting device\n");
			return -ENODEV;
		}
	}

	return dvb_usbv2_probe(intf, id);
}