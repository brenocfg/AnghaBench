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
struct lvs_rh {int /*<<< orphan*/  portnum; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  USB_PORT_FEAT_SUSPEND ; 
 struct usb_device* create_lvs_device (struct usb_interface*) ; 
 int /*<<< orphan*/  destroy_lvs_device (struct usb_device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int lvs_rh_clear_port_feature (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usb_interface* to_usb_interface (struct device*) ; 
 struct lvs_rh* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static ssize_t u3_exit_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct usb_interface *intf = to_usb_interface(dev);
	struct usb_device *hdev = interface_to_usbdev(intf);
	struct lvs_rh *lvs = usb_get_intfdata(intf);
	struct usb_device *udev;
	int ret;

	udev = create_lvs_device(intf);
	if (!udev) {
		dev_err(dev, "failed to create lvs device\n");
		return -ENOMEM;
	}

	ret = lvs_rh_clear_port_feature(hdev, lvs->portnum,
			USB_PORT_FEAT_SUSPEND);
	if (ret < 0)
		dev_err(dev, "can't issue U3 exit %d\n", ret);

	destroy_lvs_device(udev);

	if (ret < 0)
		return ret;

	return count;
}