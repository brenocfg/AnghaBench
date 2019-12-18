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
struct usb_port {int usb3_lpm_u1_permit; int usb3_lpm_u2_permit; struct usb_device* child; } ;
struct usb_hcd {int /*<<< orphan*/  bandwidth_mutex; } ;
struct usb_device {int /*<<< orphan*/  bus; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 struct usb_hcd* bus_to_hcd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 struct usb_port* to_usb_port (struct device*) ; 
 int /*<<< orphan*/  usb_disable_lpm (struct usb_device*) ; 
 int /*<<< orphan*/  usb_enable_lpm (struct usb_device*) ; 
 int /*<<< orphan*/  usb_lock_device (struct usb_device*) ; 
 int /*<<< orphan*/  usb_unlock_device (struct usb_device*) ; 

__attribute__((used)) static ssize_t usb3_lpm_permit_store(struct device *dev,
			       struct device_attribute *attr,
			       const char *buf, size_t count)
{
	struct usb_port *port_dev = to_usb_port(dev);
	struct usb_device *udev = port_dev->child;
	struct usb_hcd *hcd;

	if (!strncmp(buf, "u1_u2", 5)) {
		port_dev->usb3_lpm_u1_permit = 1;
		port_dev->usb3_lpm_u2_permit = 1;

	} else if (!strncmp(buf, "u1", 2)) {
		port_dev->usb3_lpm_u1_permit = 1;
		port_dev->usb3_lpm_u2_permit = 0;

	} else if (!strncmp(buf, "u2", 2)) {
		port_dev->usb3_lpm_u1_permit = 0;
		port_dev->usb3_lpm_u2_permit = 1;

	} else if (!strncmp(buf, "0", 1)) {
		port_dev->usb3_lpm_u1_permit = 0;
		port_dev->usb3_lpm_u2_permit = 0;
	} else
		return -EINVAL;

	/* If device is connected to the port, disable or enable lpm
	 * to make new u1 u2 setting take effect immediately.
	 */
	if (udev) {
		hcd = bus_to_hcd(udev->bus);
		if (!hcd)
			return -EINVAL;
		usb_lock_device(udev);
		mutex_lock(hcd->bandwidth_mutex);
		if (!usb_disable_lpm(udev))
			usb_enable_lpm(udev);
		mutex_unlock(hcd->bandwidth_mutex);
		usb_unlock_device(udev);
	}

	return count;
}