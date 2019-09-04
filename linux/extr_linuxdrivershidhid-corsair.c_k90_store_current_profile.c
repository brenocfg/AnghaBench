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
struct usb_interface {int dummy; } ;
struct usb_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  K90_REQUEST_PROFILE ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 scalar_t__ kstrtoint (char const*,int,int*) ; 
 struct usb_interface* to_usb_interface (int /*<<< orphan*/ ) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t k90_store_current_profile(struct device *dev,
					 struct device_attribute *attr,
					 const char *buf, size_t count)
{
	int ret;
	struct usb_interface *usbif = to_usb_interface(dev->parent);
	struct usb_device *usbdev = interface_to_usbdev(usbif);
	int profile;

	if (kstrtoint(buf, 10, &profile))
		return -EINVAL;
	if (profile < 1 || profile > 3)
		return -EINVAL;

	ret = usb_control_msg(usbdev, usb_sndctrlpipe(usbdev, 0),
			      K90_REQUEST_PROFILE,
			      USB_DIR_OUT | USB_TYPE_VENDOR |
			      USB_RECIP_DEVICE, profile, 0, NULL, 0,
			      USB_CTRL_SET_TIMEOUT);
	if (ret != 0) {
		dev_warn(dev, "Failed to change current profile (error %d).\n",
			 ret);
		return ret;
	}

	return count;
}