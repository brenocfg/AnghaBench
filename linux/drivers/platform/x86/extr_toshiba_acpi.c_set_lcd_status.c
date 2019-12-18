#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct toshiba_acpi_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  brightness; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 struct toshiba_acpi_dev* bl_get_data (struct backlight_device*) ; 
 int set_lcd_brightness (struct toshiba_acpi_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_lcd_status(struct backlight_device *bd)
{
	struct toshiba_acpi_dev *dev = bl_get_data(bd);

	return set_lcd_brightness(dev, bd->props.brightness);
}