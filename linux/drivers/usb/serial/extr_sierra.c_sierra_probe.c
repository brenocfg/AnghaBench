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
typedef  int /*<<< orphan*/  u8 ;
struct usb_serial {struct usb_device* dev; TYPE_1__* interface; } ;
struct usb_device_id {scalar_t__ driver_info; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct sierra_iface_info {int dummy; } ;
struct TYPE_2__ {int num_altsetting; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_blacklisted (int /*<<< orphan*/ ,struct sierra_iface_info*) ; 
 int /*<<< orphan*/  sierra_interface_num (struct usb_serial*) ; 
 int /*<<< orphan*/  usb_set_interface (struct usb_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sierra_probe(struct usb_serial *serial,
			const struct usb_device_id *id)
{
	int result = 0;
	struct usb_device *udev;
	u8 ifnum;

	udev = serial->dev;
	ifnum = sierra_interface_num(serial);

	/*
	 * If this interface supports more than 1 alternate
	 * select the 2nd one
	 */
	if (serial->interface->num_altsetting == 2) {
		dev_dbg(&udev->dev, "Selecting alt setting for interface %d\n",
			ifnum);
		/* We know the alternate setting is 1 for the MC8785 */
		usb_set_interface(udev, ifnum, 1);
	}

	if (is_blacklisted(ifnum,
				(struct sierra_iface_info *)id->driver_info)) {
		dev_dbg(&serial->dev->dev,
			"Ignoring blacklisted interface #%d\n", ifnum);
		return -ENODEV;
	}

	return result;
}