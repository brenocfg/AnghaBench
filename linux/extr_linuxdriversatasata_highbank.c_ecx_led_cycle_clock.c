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
struct ecx_plat_data {int /*<<< orphan*/ * sgpio_gpio; } ;

/* Variables and functions */
 size_t SCLOCK ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ecx_led_cycle_clock(struct ecx_plat_data *pdata)
{
	gpio_set_value(pdata->sgpio_gpio[SCLOCK], 1);
	udelay(50);
	gpio_set_value(pdata->sgpio_gpio[SCLOCK], 0);
	udelay(50);
}