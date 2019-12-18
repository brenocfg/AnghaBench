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
struct axp20x_usb_power {scalar_t__ axp20x_id; } ;

/* Variables and functions */
 scalar_t__ AXP221_ID ; 

__attribute__((used)) static bool axp20x_usb_vbus_needs_polling(struct axp20x_usb_power *power)
{
	if (power->axp20x_id >= AXP221_ID)
		return true;

	return false;
}