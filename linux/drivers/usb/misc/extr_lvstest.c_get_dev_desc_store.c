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
struct usb_device_descriptor {int dummy; } ;
struct usb_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PIPE_CONTROL ; 
 int /*<<< orphan*/  USB_CTRL_GET_TIMEOUT ; 
 int USB_DIR_IN ; 
 int USB_DT_DEVICE ; 
 int /*<<< orphan*/  USB_REQ_GET_DESCRIPTOR ; 
 struct usb_device* create_lvs_device (struct usb_interface*) ; 
 int /*<<< orphan*/  destroy_lvs_device (struct usb_device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  kfree (struct usb_device_descriptor*) ; 
 struct usb_device_descriptor* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct usb_interface* to_usb_interface (struct device*) ; 
 int usb_control_msg (struct usb_device*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,struct usb_device_descriptor*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t get_dev_desc_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct usb_interface *intf = to_usb_interface(dev);
	struct usb_device *udev;
	struct usb_device_descriptor *descriptor;
	int ret;

	descriptor = kmalloc(sizeof(*descriptor), GFP_KERNEL);
	if (!descriptor)
		return -ENOMEM;

	udev = create_lvs_device(intf);
	if (!udev) {
		dev_err(dev, "failed to create lvs device\n");
		ret = -ENOMEM;
		goto free_desc;
	}

	ret = usb_control_msg(udev, (PIPE_CONTROL << 30) | USB_DIR_IN,
			USB_REQ_GET_DESCRIPTOR, USB_DIR_IN, USB_DT_DEVICE << 8,
			0, descriptor, sizeof(*descriptor),
			USB_CTRL_GET_TIMEOUT);
	if (ret < 0)
		dev_err(dev, "can't read device descriptor %d\n", ret);

	destroy_lvs_device(udev);

free_desc:
	kfree(descriptor);

	if (ret < 0)
		return ret;

	return count;
}