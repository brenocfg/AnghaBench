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
 int /*<<< orphan*/  DA850_LCD_BL_PIN ; 
 int /*<<< orphan*/  DA850_LCD_PWR_PIN ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void da850_panel_power_ctrl(int val)
{
	/* lcd backlight */
	gpio_set_value(DA850_LCD_BL_PIN, val);

	/* lcd power */
	gpio_set_value(DA850_LCD_PWR_PIN, val);
}