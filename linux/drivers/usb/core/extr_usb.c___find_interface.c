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
struct usb_interface {scalar_t__ minor; } ;
struct find_interface_arg {scalar_t__ drv; scalar_t__ minor; } ;
struct device {scalar_t__ driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_usb_interface (struct device*) ; 
 struct usb_interface* to_usb_interface (struct device*) ; 

__attribute__((used)) static int __find_interface(struct device *dev, const void *data)
{
	const struct find_interface_arg *arg = data;
	struct usb_interface *intf;

	if (!is_usb_interface(dev))
		return 0;

	if (dev->driver != arg->drv)
		return 0;
	intf = to_usb_interface(dev);
	return intf->minor == arg->minor;
}