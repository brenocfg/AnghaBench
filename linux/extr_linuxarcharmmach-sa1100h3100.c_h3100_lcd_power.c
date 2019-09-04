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
 int /*<<< orphan*/  H3100_GPIO_LCD_3V_ON ; 
 int /*<<< orphan*/  H3XXX_EGPIO_LCD_ON ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  h3100_lcd_request () ; 

__attribute__((used)) static void h3100_lcd_power(int enable)
{
	if (!h3100_lcd_request())
		return;

	gpio_set_value(H3100_GPIO_LCD_3V_ON, enable);
	gpio_set_value(H3XXX_EGPIO_LCD_ON, enable);
}