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
struct usb_sevsegdev {int shadow_power; int textmode; int mode_msb; int mode_lsb; scalar_t__ has_interface_pm; struct usb_interface* intf; int /*<<< orphan*/  udev; } ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 struct usb_sevsegdev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_get_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct usb_sevsegdev*) ; 

__attribute__((used)) static int sevseg_probe(struct usb_interface *interface,
	const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(interface);
	struct usb_sevsegdev *mydev = NULL;
	int rc = -ENOMEM;

	mydev = kzalloc(sizeof(struct usb_sevsegdev), GFP_KERNEL);
	if (!mydev)
		goto error_mem;

	mydev->udev = usb_get_dev(udev);
	mydev->intf = interface;
	usb_set_intfdata(interface, mydev);

	/* PM */
	mydev->shadow_power = 1; /* currently active */
	mydev->has_interface_pm = 0; /* have not issued autopm_get */

	/*set defaults */
	mydev->textmode = 0x02; /* ascii mode */
	mydev->mode_msb = 0x06; /* 6 characters */
	mydev->mode_lsb = 0x3f; /* scanmode for 6 chars */

	dev_info(&interface->dev, "USB 7 Segment device now attached\n");
	return 0;

error_mem:
	return rc;
}