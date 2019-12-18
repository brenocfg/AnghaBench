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
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  K90_REQUEST_STATUS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int USB_DIR_IN ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,char) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 struct usb_interface* to_usb_interface (int /*<<< orphan*/ ) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t k90_show_current_profile(struct device *dev,
					struct device_attribute *attr,
					char *buf)
{
	int ret;
	struct usb_interface *usbif = to_usb_interface(dev->parent);
	struct usb_device *usbdev = interface_to_usbdev(usbif);
	int current_profile;
	char *data;

	data = kmalloc(8, GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	ret = usb_control_msg(usbdev, usb_rcvctrlpipe(usbdev, 0),
			      K90_REQUEST_STATUS,
			      USB_DIR_IN | USB_TYPE_VENDOR |
			      USB_RECIP_DEVICE, 0, 0, data, 8,
			      USB_CTRL_SET_TIMEOUT);
	if (ret < 8) {
		dev_warn(dev, "Failed to get K90 initial state (error %d).\n",
			 ret);
		ret = -EIO;
		goto out;
	}
	current_profile = data[7];
	if (current_profile < 1 || current_profile > 3) {
		dev_warn(dev, "Read invalid current profile: %02hhx.\n",
			 data[7]);
		ret = -EIO;
		goto out;
	}

	ret = snprintf(buf, PAGE_SIZE, "%d\n", current_profile);
out:
	kfree(data);

	return ret;
}