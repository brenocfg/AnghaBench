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
typedef  int /*<<< orphan*/  u8 ;
struct usb_configuration {int MaxPower; } ;
typedef  enum usb_device_speed { ____Placeholder_usb_device_speed } usb_device_speed ;

/* Variables and functions */
 unsigned int CONFIG_USB_GADGET_VBUS_DRAW ; 
 int /*<<< orphan*/  DIV_ROUND_UP (unsigned int,int) ; 
#define  USB_SPEED_SUPER 128 

__attribute__((used)) static u8 encode_bMaxPower(enum usb_device_speed speed,
		struct usb_configuration *c)
{
	unsigned val;

	if (c->MaxPower)
		val = c->MaxPower;
	else
		val = CONFIG_USB_GADGET_VBUS_DRAW;
	if (!val)
		return 0;
	switch (speed) {
	case USB_SPEED_SUPER:
		return DIV_ROUND_UP(val, 8);
	default:
		return DIV_ROUND_UP(val, 2);
	}
}