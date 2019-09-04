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
struct dmi_system_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_backlight_dmi ; 
 int /*<<< orphan*/  acpi_backlight_video ; 

__attribute__((used)) static int video_detect_force_video(const struct dmi_system_id *d)
{
	acpi_backlight_dmi = acpi_backlight_video;
	return 0;
}