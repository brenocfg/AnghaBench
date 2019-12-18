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
struct lvs_rh {unsigned long portnum; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  USB_PORT_FEAT_U1_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int lvs_rh_set_port_feature (struct usb_device*,unsigned long,int /*<<< orphan*/ ) ; 
 struct usb_interface* to_usb_interface (struct device*) ; 
 struct lvs_rh* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static ssize_t u1_timeout_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct usb_interface *intf = to_usb_interface(dev);
	struct usb_device *hdev = interface_to_usbdev(intf);
	struct lvs_rh *lvs = usb_get_intfdata(intf);
	unsigned long val;
	int ret;

	ret = kstrtoul(buf, 10, &val);
	if (ret < 0) {
		dev_err(dev, "couldn't parse string %d\n", ret);
		return ret;
	}

	if (val > 127)
		return -EINVAL;

	ret = lvs_rh_set_port_feature(hdev, lvs->portnum | (val << 8),
			USB_PORT_FEAT_U1_TIMEOUT);
	if (ret < 0) {
		dev_err(dev, "Error %d while setting U1 timeout %ld\n", ret, val);
		return ret;
	}

	return count;
}