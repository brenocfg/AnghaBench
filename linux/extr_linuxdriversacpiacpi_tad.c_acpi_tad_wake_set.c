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
struct TYPE_2__ {void* value; } ;
union acpi_object {TYPE_1__ integer; int /*<<< orphan*/  type; } ;
typedef  void* u32 ;
struct device {int dummy; } ;
struct acpi_object_list {int /*<<< orphan*/  count; union acpi_object* pointer; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_HANDLE (struct device*) ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  ARRAY_SIZE (union acpi_object*) ; 
 int EIO ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,struct acpi_object_list*,unsigned long long*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 

__attribute__((used)) static int acpi_tad_wake_set(struct device *dev, char *method, u32 timer_id,
			     u32 value)
{
	acpi_handle handle = ACPI_HANDLE(dev);
	union acpi_object args[] = {
		{ .type = ACPI_TYPE_INTEGER, },
		{ .type = ACPI_TYPE_INTEGER, },
	};
	struct acpi_object_list arg_list = {
		.pointer = args,
		.count = ARRAY_SIZE(args),
	};
	unsigned long long retval;
	acpi_status status;

	args[0].integer.value = timer_id;
	args[1].integer.value = value;

	pm_runtime_get_sync(dev);

	status = acpi_evaluate_integer(handle, method, &arg_list, &retval);

	pm_runtime_put_sync(dev);

	if (ACPI_FAILURE(status) || retval)
		return -EIO;

	return 0;
}