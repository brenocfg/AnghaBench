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
struct backlight_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sony_nc_acpi_handle ; 
 scalar_t__ sony_nc_int_call (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int sony_backlight_get_brightness(struct backlight_device *bd)
{
	int value;

	if (sony_nc_int_call(sony_nc_acpi_handle, "GBRT", NULL, &value))
		return 0;
	/* brightness levels are 1-based, while backlight ones are 0-based */
	return value - 1;
}