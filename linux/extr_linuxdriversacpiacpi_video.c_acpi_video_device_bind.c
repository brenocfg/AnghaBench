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
struct TYPE_2__ {int int_val; } ;
struct acpi_video_enumerated_device {struct acpi_video_device* bind_info; TYPE_1__ value; } ;
struct acpi_video_device {int device_id; } ;
struct acpi_video_bus {int attached_count; struct acpi_video_enumerated_device* attached_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
acpi_video_device_bind(struct acpi_video_bus *video,
		       struct acpi_video_device *device)
{
	struct acpi_video_enumerated_device *ids;
	int i;

	for (i = 0; i < video->attached_count; i++) {
		ids = &video->attached_array[i];
		if (device->device_id == (ids->value.int_val & 0xffff)) {
			ids->bind_info = device;
			ACPI_DEBUG_PRINT((ACPI_DB_INFO, "device_bind %d\n", i));
		}
	}
}