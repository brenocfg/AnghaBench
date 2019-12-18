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
struct usb_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINTR ; 
 int EINVAL ; 
 int sscanf (char const*,char*,int*) ; 
 struct usb_device* to_usb_device (struct device*) ; 
 int usb_lock_device_interruptible (struct usb_device*) ; 
 int usb_set_configuration (struct usb_device*,int) ; 
 int /*<<< orphan*/  usb_unlock_device (struct usb_device*) ; 

__attribute__((used)) static ssize_t bConfigurationValue_store(struct device *dev,
					 struct device_attribute *attr,
					 const char *buf, size_t count)
{
	struct usb_device	*udev = to_usb_device(dev);
	int			config, value, rc;

	if (sscanf(buf, "%d", &config) != 1 || config < -1 || config > 255)
		return -EINVAL;
	rc = usb_lock_device_interruptible(udev);
	if (rc < 0)
		return -EINTR;
	value = usb_set_configuration(udev, config);
	usb_unlock_device(udev);
	return (value < 0) ? value : count;
}