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
struct usb_hcd {int /*<<< orphan*/  flags; } ;
struct usb_device {int /*<<< orphan*/  bus; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HCD_FLAG_INTF_AUTHORIZED ; 
 struct usb_hcd* bus_to_hcd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strtobool (char const*,int*) ; 
 struct usb_device* to_usb_device (struct device*) ; 

__attribute__((used)) static ssize_t interface_authorized_default_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct usb_device *usb_dev = to_usb_device(dev);
	struct usb_hcd *hcd = bus_to_hcd(usb_dev->bus);
	int rc = count;
	bool val;

	if (strtobool(buf, &val) != 0)
		return -EINVAL;

	if (val)
		set_bit(HCD_FLAG_INTF_AUTHORIZED, &hcd->flags);
	else
		clear_bit(HCD_FLAG_INTF_AUTHORIZED, &hcd->flags);

	return rc;
}