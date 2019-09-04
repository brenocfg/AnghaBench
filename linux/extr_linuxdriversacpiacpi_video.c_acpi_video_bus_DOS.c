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
struct TYPE_4__ {int /*<<< orphan*/  _DOS; } ;
struct acpi_video_bus {int dos_setting; TYPE_1__* device; TYPE_2__ cap; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  acpi_execute_simple_method (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
acpi_video_bus_DOS(struct acpi_video_bus *video, int bios_flag, int lcd_flag)
{
	acpi_status status;

	if (!video->cap._DOS)
		return 0;

	if (bios_flag < 0 || bios_flag > 3 || lcd_flag < 0 || lcd_flag > 1)
		return -EINVAL;
	video->dos_setting = (lcd_flag << 2) | bios_flag;
	status = acpi_execute_simple_method(video->device->handle, "_DOS",
					    (lcd_flag << 2) | bios_flag);
	if (ACPI_FAILURE(status))
		return -EIO;

	return 0;
}