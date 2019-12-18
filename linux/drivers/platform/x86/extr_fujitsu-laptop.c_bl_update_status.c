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
struct TYPE_2__ {scalar_t__ power; int /*<<< orphan*/  brightness; } ;
struct backlight_device {TYPE_1__ props; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_OFF ; 
 int /*<<< orphan*/  BACKLIGHT_ON ; 
 int /*<<< orphan*/  BACKLIGHT_PARAM_POWER ; 
 scalar_t__ FB_BLANK_POWERDOWN ; 
 int /*<<< orphan*/  FUNC_BACKLIGHT ; 
 struct acpi_device* bl_get_data (struct backlight_device*) ; 
 int /*<<< orphan*/  call_fext_func (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fext ; 
 int set_lcd_level (struct acpi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bl_update_status(struct backlight_device *b)
{
	struct acpi_device *device = bl_get_data(b);

	if (fext) {
		if (b->props.power == FB_BLANK_POWERDOWN)
			call_fext_func(fext, FUNC_BACKLIGHT, 0x1,
				       BACKLIGHT_PARAM_POWER, BACKLIGHT_OFF);
		else
			call_fext_func(fext, FUNC_BACKLIGHT, 0x1,
				       BACKLIGHT_PARAM_POWER, BACKLIGHT_ON);
	}

	return set_lcd_level(device, b->props.brightness);
}