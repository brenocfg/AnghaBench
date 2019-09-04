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
union acpi_object {scalar_t__ type; } ;
struct acpi_fan {char fif; } ;
struct acpi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  handle; } ;
struct acpi_buffer {int member_0; char* member_1; union acpi_object* pointer; } ;
typedef  int acpi_status ;

/* Variables and functions */
 int ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int) ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 int EINVAL ; 
 struct acpi_fan* acpi_driver_data (struct acpi_device*) ; 
 int acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,struct acpi_buffer*) ; 
 int acpi_extract_package (union acpi_object*,struct acpi_buffer*,struct acpi_buffer*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 

__attribute__((used)) static int acpi_fan_get_fif(struct acpi_device *device)
{
	struct acpi_buffer buffer = { ACPI_ALLOCATE_BUFFER, NULL };
	struct acpi_fan *fan = acpi_driver_data(device);
	struct acpi_buffer format = { sizeof("NNNN"), "NNNN" };
	struct acpi_buffer fif = { sizeof(fan->fif), &fan->fif };
	union acpi_object *obj;
	acpi_status status;

	status = acpi_evaluate_object(device->handle, "_FIF", NULL, &buffer);
	if (ACPI_FAILURE(status))
		return status;

	obj = buffer.pointer;
	if (!obj || obj->type != ACPI_TYPE_PACKAGE) {
		dev_err(&device->dev, "Invalid _FIF data\n");
		status = -EINVAL;
		goto err;
	}

	status = acpi_extract_package(obj, &format, &fif);
	if (ACPI_FAILURE(status)) {
		dev_err(&device->dev, "Invalid _FIF element\n");
		status = -EINVAL;
	}

err:
	kfree(obj);
	return status;
}