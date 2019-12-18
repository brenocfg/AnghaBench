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
struct TYPE_2__ {char* pointer; } ;
union acpi_object {scalar_t__ type; TYPE_1__ string; } ;
struct icn8505_data {int /*<<< orphan*/  firmware_name; } ;
struct device {int dummy; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;
struct acpi_buffer {union acpi_object* pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 struct acpi_device* ACPI_COMPANION (struct device*) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_STRING ; 
 int ENODEV ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,struct acpi_buffer*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char const*) ; 

__attribute__((used)) static int icn8505_probe_acpi(struct icn8505_data *icn8505, struct device *dev)
{
	struct acpi_buffer buffer = { ACPI_ALLOCATE_BUFFER, NULL };
	const char *subsys = "unknown";
	struct acpi_device *adev;
	union acpi_object *obj;
	acpi_status status;

	adev = ACPI_COMPANION(dev);
	if (!adev)
		return -ENODEV;

	status = acpi_evaluate_object(adev->handle, "_SUB", NULL, &buffer);
	if (ACPI_SUCCESS(status)) {
		obj = buffer.pointer;
		if (obj->type == ACPI_TYPE_STRING)
			subsys = obj->string.pointer;
		else
			dev_warn(dev, "Warning ACPI _SUB did not return a string\n");
	} else {
		dev_warn(dev, "Warning ACPI _SUB failed: %#x\n", status);
		buffer.pointer = NULL;
	}

	snprintf(icn8505->firmware_name, sizeof(icn8505->firmware_name),
		 "chipone/icn8505-%s.fw", subsys);

	kfree(buffer.pointer);
	return 0;
}