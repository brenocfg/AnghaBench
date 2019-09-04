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

/* Variables and functions */
 int /*<<< orphan*/  GPIO_CHARGE_DONE ; 
 int /*<<< orphan*/  gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raumfeld_power_signal_charged () ; 

__attribute__((used)) static int raumfeld_power_resume(void)
{
	/* check if GPIO_CHARGE_DONE went low while we were sleeping */
	if (!gpio_get_value(GPIO_CHARGE_DONE))
		raumfeld_power_signal_charged();

	return 0;
}