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
struct tosa_lcd_data {int lcd_power; } ;
struct lcd_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ POWER_IS_ON (int) ; 
 struct tosa_lcd_data* lcd_get_data (struct lcd_device*) ; 
 int /*<<< orphan*/  tosa_lcd_tg_off (struct tosa_lcd_data*) ; 
 int /*<<< orphan*/  tosa_lcd_tg_on (struct tosa_lcd_data*) ; 

int tosa_lcd_set_power(struct lcd_device *lcd, int power)
{
	struct tosa_lcd_data *data = lcd_get_data(lcd);

	if (POWER_IS_ON(power) && !POWER_IS_ON(data->lcd_power))
		tosa_lcd_tg_on(data);

	if (!POWER_IS_ON(power) && POWER_IS_ON(data->lcd_power))
		tosa_lcd_tg_off(data);

	data->lcd_power = power;
	return 0;
}