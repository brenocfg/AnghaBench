#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_device {TYPE_1__* bus; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int busnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct usb_device* to_usb_device (struct device*) ; 

__attribute__((used)) static ssize_t busnum_show(struct device *dev, struct device_attribute *attr,
			   char *buf)
{
	struct usb_device *udev;

	udev = to_usb_device(dev);
	return sprintf(buf, "%d\n", udev->bus->busnum);
}