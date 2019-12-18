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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 scalar_t__ strtobool (char const*,int*) ; 
 struct usb_interface* to_usb_interface (struct device*) ; 
 int /*<<< orphan*/  usb_authorize_interface (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_deauthorize_interface (struct usb_interface*) ; 

__attribute__((used)) static ssize_t interface_authorized_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct usb_interface *intf = to_usb_interface(dev);
	bool val;

	if (strtobool(buf, &val) != 0)
		return -EINVAL;

	if (val)
		usb_authorize_interface(intf);
	else
		usb_deauthorize_interface(intf);

	return count;
}