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
struct usb_serial {struct usb_interface* interface; struct usb_device* dev; } ;
struct usb_interface {int dummy; } ;
struct usb_device {int /*<<< orphan*/  dev; TYPE_1__* actconfig; } ;
struct TYPE_2__ {struct usb_interface** interface; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int ftdi_jtag_probe(struct usb_serial *serial)
{
	struct usb_device *udev = serial->dev;
	struct usb_interface *interface = serial->interface;

	if (interface == udev->actconfig->interface[0]) {
		dev_info(&udev->dev,
			 "Ignoring serial port reserved for JTAG\n");
		return -ENODEV;
	}

	return 0;
}