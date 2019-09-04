#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int lcd; } ;
struct acpi_video_device {TYPE_2__ flags; TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_video_device_in_dod (struct acpi_video_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ only_lcd ; 

__attribute__((used)) static bool acpi_video_should_register_backlight(struct acpi_video_device *dev)
{
	/*
	 * Do not create backlight device for video output
	 * device that is not in the enumerated list.
	 */
	if (!acpi_video_device_in_dod(dev)) {
		dev_dbg(&dev->dev->dev, "not in _DOD list, ignore\n");
		return false;
	}

	if (only_lcd)
		return dev->flags.lcd;
	return true;
}