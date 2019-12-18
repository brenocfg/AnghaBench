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
struct TYPE_2__ {unsigned int bMaxPower; } ;
struct usb_host_config {TYPE_1__ desc; } ;
struct usb_device {scalar_t__ speed; } ;

/* Variables and functions */
 scalar_t__ USB_SPEED_SUPER ; 

__attribute__((used)) static inline unsigned usb_get_max_power(struct usb_device *udev,
		struct usb_host_config *c)
{
	/* SuperSpeed power is in 8 mA units; others are in 2 mA units */
	unsigned mul = (udev->speed >= USB_SPEED_SUPER ? 8 : 2);

	return c->desc.bMaxPower * mul;
}