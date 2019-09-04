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
typedef  enum acpi_backlight_type { ____Placeholder_acpi_backlight_type } acpi_backlight_type ;

/* Variables and functions */
 int acpi_backlight_dmi ; 
 scalar_t__ acpi_backlight_video ; 
 scalar_t__ acpi_video_get_backlight_type () ; 
 int /*<<< orphan*/  acpi_video_unregister_backlight () ; 

void acpi_video_set_dmi_backlight_type(enum acpi_backlight_type type)
{
	acpi_backlight_dmi = type;
	/* Remove acpi-video backlight interface if it is no longer desired */
	if (acpi_video_get_backlight_type() != acpi_backlight_video)
		acpi_video_unregister_backlight();
}