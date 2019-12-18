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
struct usb_gadget {int dummy; } ;
struct usb_composite_dev {int suspended; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct usb_gadget* dev_to_usb_gadget (struct device*) ; 
 struct usb_composite_dev* get_gadget_data (struct usb_gadget*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t suspended_show(struct device *dev, struct device_attribute *attr,
			      char *buf)
{
	struct usb_gadget *gadget = dev_to_usb_gadget(dev);
	struct usb_composite_dev *cdev = get_gadget_data(gadget);

	return sprintf(buf, "%d\n", cdev->suspended);
}