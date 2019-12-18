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
typedef  int /*<<< orphan*/  u32 ;
struct acpi_device_info {int /*<<< orphan*/  param_count; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_get_object_info (int /*<<< orphan*/ ,struct acpi_device_info**) ; 
 int /*<<< orphan*/  kfree (struct acpi_device_info*) ; 
 int /*<<< orphan*/  pr_warn (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status sony_walk_callback(acpi_handle handle, u32 level,
				      void *context, void **return_value)
{
	struct acpi_device_info *info;

	if (ACPI_SUCCESS(acpi_get_object_info(handle, &info))) {
		pr_warn("method: name: %4.4s, args %X\n",
			(char *)&info->name, info->param_count);

		kfree(info);
	}

	return AE_OK;
}