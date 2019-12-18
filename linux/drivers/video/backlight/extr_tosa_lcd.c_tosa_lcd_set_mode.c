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
struct tosa_lcd_data {int is_vga; int /*<<< orphan*/  lcd_power; } ;
struct lcd_device {int dummy; } ;
struct fb_videomode {int xres; int yres; } ;

/* Variables and functions */
 scalar_t__ POWER_IS_ON (int /*<<< orphan*/ ) ; 
 struct tosa_lcd_data* lcd_get_data (struct lcd_device*) ; 
 int /*<<< orphan*/  tosa_lcd_tg_on (struct tosa_lcd_data*) ; 

__attribute__((used)) static int tosa_lcd_set_mode(struct lcd_device *lcd, struct fb_videomode *mode)
{
	struct tosa_lcd_data *data = lcd_get_data(lcd);

	if (mode->xres == 320 || mode->yres == 320)
		data->is_vga = false;
	else
		data->is_vga = true;

	if (POWER_IS_ON(data->lcd_power))
		tosa_lcd_tg_on(data);

	return 0;
}