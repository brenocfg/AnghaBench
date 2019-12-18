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
struct TYPE_2__ {int /*<<< orphan*/  value; } ;
union acpi_object {TYPE_1__ integer; int /*<<< orphan*/  type; } ;
struct thermal_cooling_device {struct acpi_device* devdata; } ;
struct acpi_object_list {int count; union acpi_object* pointer; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  AE_OK ; 
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  MEMORY_ARG_MAX_BANDWIDTH ; 
 int /*<<< orphan*/  MEMORY_GET_BANDWIDTH ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_object_list*,unsigned long long*) ; 

__attribute__((used)) static int memory_get_max_bandwidth(struct thermal_cooling_device *cdev,
				    unsigned long *max_state)
{
	struct acpi_device *device = cdev->devdata;
	acpi_handle handle = device->handle;
	unsigned long long value;
	struct acpi_object_list arg_list;
	union acpi_object arg;
	acpi_status status = AE_OK;

	arg_list.count = 1;
	arg_list.pointer = &arg;
	arg.type = ACPI_TYPE_INTEGER;
	arg.integer.value = MEMORY_ARG_MAX_BANDWIDTH;
	status = acpi_evaluate_integer(handle, MEMORY_GET_BANDWIDTH,
				       &arg_list, &value);
	if (ACPI_FAILURE(status))
		return -EFAULT;

	if (!value)
		return -EINVAL;

	*max_state = value - 1;
	return 0;
}