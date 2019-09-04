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
 int /*<<< orphan*/  H3600_EGPIO_LCD_5V_ON ; 
 int /*<<< orphan*/  H3600_EGPIO_LCD_PCI ; 
 int /*<<< orphan*/  H3600_EGPIO_LVDD_ON ; 
 int /*<<< orphan*/  H3XXX_EGPIO_LCD_ON ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  h3600_lcd_request () ; 

__attribute__((used)) static void h3600_lcd_power(int enable)
{
	if (!h3600_lcd_request())
		return;

	gpio_direction_output(H3XXX_EGPIO_LCD_ON, enable);
	gpio_direction_output(H3600_EGPIO_LCD_PCI, enable);
	gpio_direction_output(H3600_EGPIO_LCD_5V_ON, enable);
	gpio_direction_output(H3600_EGPIO_LVDD_ON, enable);
}