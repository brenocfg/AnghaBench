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
struct usb_device {int removable; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
#define  USB_DEVICE_FIXED 129 
#define  USB_DEVICE_REMOVABLE 128 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct usb_device* to_usb_device (struct device*) ; 

__attribute__((used)) static ssize_t removable_show(struct device *dev, struct device_attribute *attr,
			      char *buf)
{
	struct usb_device *udev;
	char *state;

	udev = to_usb_device(dev);

	switch (udev->removable) {
	case USB_DEVICE_REMOVABLE:
		state = "removable";
		break;
	case USB_DEVICE_FIXED:
		state = "fixed";
		break;
	default:
		state = "unknown";
	}

	return sprintf(buf, "%s\n", state);
}