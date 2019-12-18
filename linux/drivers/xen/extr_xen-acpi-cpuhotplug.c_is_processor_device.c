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
struct TYPE_2__ {char* string; } ;
struct acpi_device_info {scalar_t__ type; int valid; TYPE_1__ hardware_id; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_PROCESSOR_DEVICE_HID ; 
 scalar_t__ ACPI_TYPE_PROCESSOR ; 
 int ACPI_VALID_HID ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_get_object_info (int /*<<< orphan*/ ,struct acpi_device_info**) ; 
 int /*<<< orphan*/  kfree (struct acpi_device_info*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status is_processor_device(acpi_handle handle)
{
	struct acpi_device_info *info;
	char *hid;
	acpi_status status;

	status = acpi_get_object_info(handle, &info);
	if (ACPI_FAILURE(status))
		return status;

	if (info->type == ACPI_TYPE_PROCESSOR) {
		kfree(info);
		return AE_OK;	/* found a processor object */
	}

	if (!(info->valid & ACPI_VALID_HID)) {
		kfree(info);
		return AE_ERROR;
	}

	hid = info->hardware_id.string;
	if ((hid == NULL) || strcmp(hid, ACPI_PROCESSOR_DEVICE_HID)) {
		kfree(info);
		return AE_ERROR;
	}

	kfree(info);
	return AE_OK;	/* found a processor device object */
}