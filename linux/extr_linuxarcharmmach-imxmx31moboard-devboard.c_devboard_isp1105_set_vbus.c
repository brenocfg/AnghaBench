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
struct usb_otg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBH1_VBUSEN_B ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int devboard_isp1105_set_vbus(struct usb_otg *otg, bool on)
{
	if (on)
		gpio_set_value(USBH1_VBUSEN_B, 0);
	else
		gpio_set_value(USBH1_VBUSEN_B, 1);

	return 0;
}