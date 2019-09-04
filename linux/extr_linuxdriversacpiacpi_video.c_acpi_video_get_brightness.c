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
struct backlight_device {int dummy; } ;
struct acpi_video_device {TYPE_1__* brightness; } ;
struct TYPE_2__ {int count; unsigned long long* levels; } ;

/* Variables and functions */
 int ACPI_VIDEO_FIRST_LEVEL ; 
 int EINVAL ; 
 scalar_t__ acpi_video_device_lcd_get_level_current (struct acpi_video_device*,unsigned long long*,int) ; 
 struct acpi_video_device* bl_get_data (struct backlight_device*) ; 

__attribute__((used)) static int acpi_video_get_brightness(struct backlight_device *bd)
{
	unsigned long long cur_level;
	int i;
	struct acpi_video_device *vd = bl_get_data(bd);

	if (acpi_video_device_lcd_get_level_current(vd, &cur_level, false))
		return -EINVAL;
	for (i = ACPI_VIDEO_FIRST_LEVEL; i < vd->brightness->count; i++) {
		if (vd->brightness->levels[i] == cur_level)
			return i - ACPI_VIDEO_FIRST_LEVEL;
	}
	return 0;
}