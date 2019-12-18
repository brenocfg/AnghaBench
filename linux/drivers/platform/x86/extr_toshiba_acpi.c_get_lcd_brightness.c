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
struct toshiba_acpi_dev {int dummy; } ;
struct backlight_device {int dummy; } ;

/* Variables and functions */
 int __get_lcd_brightness (struct toshiba_acpi_dev*) ; 
 struct toshiba_acpi_dev* bl_get_data (struct backlight_device*) ; 

__attribute__((used)) static int get_lcd_brightness(struct backlight_device *bd)
{
	struct toshiba_acpi_dev *dev = bl_get_data(bd);

	return __get_lcd_brightness(dev);
}