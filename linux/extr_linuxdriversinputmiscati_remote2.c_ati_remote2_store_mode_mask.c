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
struct device {int dummy; } ;
struct ati_remote2 {unsigned int mode_mask; } ;
typedef  int ssize_t ;

/* Variables and functions */
 unsigned int ATI_REMOTE2_MAX_MODE_MASK ; 
 int EINVAL ; 
 int kstrtouint (char const*,int /*<<< orphan*/ ,unsigned int*) ; 
 struct usb_device* to_usb_device (struct device*) ; 
 struct ati_remote2* usb_get_intfdata (struct usb_interface*) ; 
 struct usb_interface* usb_ifnum_to_if (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t ati_remote2_store_mode_mask(struct device *dev,
					   struct device_attribute *attr,
					   const char *buf, size_t count)
{
	struct usb_device *udev = to_usb_device(dev);
	struct usb_interface *intf = usb_ifnum_to_if(udev, 0);
	struct ati_remote2 *ar2 = usb_get_intfdata(intf);
	unsigned int mask;
	int err;

	err = kstrtouint(buf, 0, &mask);
	if (err)
		return err;

	if (mask & ~ATI_REMOTE2_MAX_MODE_MASK)
		return -EINVAL;

	ar2->mode_mask = mask;

	return count;
}