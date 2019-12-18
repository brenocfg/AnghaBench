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
struct acpi_memory_device {TYPE_1__* device; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 unsigned long long ACPI_STA_DEVICE_ENABLED ; 
 unsigned long long ACPI_STA_DEVICE_FUNCTIONING ; 
 unsigned long long ACPI_STA_DEVICE_PRESENT ; 
 int ENODEV ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 

__attribute__((used)) static int acpi_memory_check_device(struct acpi_memory_device *mem_device)
{
	unsigned long long current_status;

	/* Get device present/absent information from the _STA */
	if (ACPI_FAILURE(acpi_evaluate_integer(mem_device->device->handle,
				"_STA", NULL, &current_status)))
		return -ENODEV;
	/*
	 * Check for device status. Device should be
	 * present/enabled/functioning.
	 */
	if (!((current_status & ACPI_STA_DEVICE_PRESENT)
	      && (current_status & ACPI_STA_DEVICE_ENABLED)
	      && (current_status & ACPI_STA_DEVICE_FUNCTIONING)))
		return -ENODEV;

	return 0;
}