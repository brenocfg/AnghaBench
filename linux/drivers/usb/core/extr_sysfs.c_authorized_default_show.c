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
struct usb_hcd {int dev_policy; } ;
struct usb_device {struct usb_bus* bus; } ;
struct usb_bus {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct usb_hcd* bus_to_hcd (struct usb_bus*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 struct usb_device* to_usb_device (struct device*) ; 

__attribute__((used)) static ssize_t authorized_default_show(struct device *dev,
				       struct device_attribute *attr, char *buf)
{
	struct usb_device *rh_usb_dev = to_usb_device(dev);
	struct usb_bus *usb_bus = rh_usb_dev->bus;
	struct usb_hcd *hcd;

	hcd = bus_to_hcd(usb_bus);
	return snprintf(buf, PAGE_SIZE, "%u\n", hcd->dev_policy);
}