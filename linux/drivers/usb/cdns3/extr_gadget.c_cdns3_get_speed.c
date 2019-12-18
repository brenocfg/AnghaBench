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
typedef  int /*<<< orphan*/  u32 ;
struct cdns3_device {TYPE_1__* regs; } ;
typedef  enum usb_device_speed { ____Placeholder_usb_device_speed } usb_device_speed ;
struct TYPE_2__ {int /*<<< orphan*/  usb_sts; } ;

/* Variables and functions */
 scalar_t__ DEV_FULLSPEED (int /*<<< orphan*/ ) ; 
 scalar_t__ DEV_HIGHSPEED (int /*<<< orphan*/ ) ; 
 scalar_t__ DEV_LOWSPEED (int /*<<< orphan*/ ) ; 
 scalar_t__ DEV_SUPERSPEED (int /*<<< orphan*/ ) ; 
 int USB_SPEED_FULL ; 
 int USB_SPEED_HIGH ; 
 int USB_SPEED_LOW ; 
 int USB_SPEED_SUPER ; 
 int USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 

enum usb_device_speed cdns3_get_speed(struct cdns3_device *priv_dev)
{
	u32 reg;

	reg = readl(&priv_dev->regs->usb_sts);

	if (DEV_SUPERSPEED(reg))
		return USB_SPEED_SUPER;
	else if (DEV_HIGHSPEED(reg))
		return USB_SPEED_HIGH;
	else if (DEV_FULLSPEED(reg))
		return USB_SPEED_FULL;
	else if (DEV_LOWSPEED(reg))
		return USB_SPEED_LOW;
	return USB_SPEED_UNKNOWN;
}