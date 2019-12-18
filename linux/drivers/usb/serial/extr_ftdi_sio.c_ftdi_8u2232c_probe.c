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
struct usb_serial {struct usb_device* dev; } ;
struct usb_device {scalar_t__ product; scalar_t__ manufacturer; } ;

/* Variables and functions */
 int ftdi_jtag_probe (struct usb_serial*) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char*) ; 

__attribute__((used)) static int ftdi_8u2232c_probe(struct usb_serial *serial)
{
	struct usb_device *udev = serial->dev;

	if (udev->manufacturer && !strcmp(udev->manufacturer, "CALAO Systems"))
		return ftdi_jtag_probe(serial);

	if (udev->product &&
		(!strcmp(udev->product, "Arrow USB Blaster") ||
		 !strcmp(udev->product, "BeagleBone/XDS100V2") ||
		 !strcmp(udev->product, "SNAP Connect E10")))
		return ftdi_jtag_probe(serial);

	return 0;
}