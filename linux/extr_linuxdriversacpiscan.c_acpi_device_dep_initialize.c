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
struct acpi_handle_list {int count; int /*<<< orphan*/ * handles; } ;
struct TYPE_2__ {int /*<<< orphan*/  string; } ;
struct acpi_device_info {int valid; TYPE_1__ hardware_id; } ;
struct acpi_device {scalar_t__ dep_unmet; int /*<<< orphan*/  handle; int /*<<< orphan*/  dev; } ;
struct acpi_dep_data {int /*<<< orphan*/  node; int /*<<< orphan*/  slave; int /*<<< orphan*/  master; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ACPI_VALID_HID ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  acpi_dep_list ; 
 int /*<<< orphan*/  acpi_dep_list_lock ; 
 int /*<<< orphan*/  acpi_evaluate_reference (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,struct acpi_handle_list*) ; 
 int /*<<< orphan*/  acpi_get_object_info (int /*<<< orphan*/ ,struct acpi_device_info**) ; 
 int /*<<< orphan*/  acpi_has_method (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (struct acpi_device_info*) ; 
 struct acpi_dep_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void acpi_device_dep_initialize(struct acpi_device *adev)
{
	struct acpi_dep_data *dep;
	struct acpi_handle_list dep_devices;
	acpi_status status;
	int i;

	adev->dep_unmet = 0;

	if (!acpi_has_method(adev->handle, "_DEP"))
		return;

	status = acpi_evaluate_reference(adev->handle, "_DEP", NULL,
					&dep_devices);
	if (ACPI_FAILURE(status)) {
		dev_dbg(&adev->dev, "Failed to evaluate _DEP.\n");
		return;
	}

	for (i = 0; i < dep_devices.count; i++) {
		struct acpi_device_info *info;
		int skip;

		status = acpi_get_object_info(dep_devices.handles[i], &info);
		if (ACPI_FAILURE(status)) {
			dev_dbg(&adev->dev, "Error reading _DEP device info\n");
			continue;
		}

		/*
		 * Skip the dependency of Windows System Power
		 * Management Controller
		 */
		skip = info->valid & ACPI_VALID_HID &&
			!strcmp(info->hardware_id.string, "INT3396");

		kfree(info);

		if (skip)
			continue;

		dep = kzalloc(sizeof(struct acpi_dep_data), GFP_KERNEL);
		if (!dep)
			return;

		dep->master = dep_devices.handles[i];
		dep->slave  = adev->handle;
		adev->dep_unmet++;

		mutex_lock(&acpi_dep_list_lock);
		list_add_tail(&dep->node , &acpi_dep_list);
		mutex_unlock(&acpi_dep_list_lock);
	}
}