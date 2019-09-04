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
struct fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VISION_LCD_ENABLE ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vision_lcd_blank(int blank_mode, struct fb_info *info)
{
	if (blank_mode)
		gpio_set_value(VISION_LCD_ENABLE, 0);
	else
		gpio_set_value(VISION_LCD_ENABLE, 1);
}