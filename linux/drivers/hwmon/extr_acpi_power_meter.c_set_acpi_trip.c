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
struct TYPE_3__ {scalar_t__ value; } ;
union acpi_object {TYPE_1__ integer; int /*<<< orphan*/  member_0; } ;
struct acpi_power_meter_resource {scalar_t__* trip; TYPE_2__* acpi_dev; } ;
struct acpi_object_list {int member_0; union acpi_object* member_1; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_4__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  AE_INFO ; 
 int EINVAL ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,struct acpi_object_list*,unsigned long long*) ; 

__attribute__((used)) static int set_acpi_trip(struct acpi_power_meter_resource *resource)
{
	union acpi_object arg_objs[] = {
		{ACPI_TYPE_INTEGER},
		{ACPI_TYPE_INTEGER}
	};
	struct acpi_object_list args = { 2, arg_objs };
	unsigned long long data;
	acpi_status status;

	/* Both trip levels must be set */
	if (resource->trip[0] < 0 || resource->trip[1] < 0)
		return 0;

	/* This driver stores min, max; ACPI wants max, min. */
	arg_objs[0].integer.value = resource->trip[1];
	arg_objs[1].integer.value = resource->trip[0];

	status = acpi_evaluate_integer(resource->acpi_dev->handle, "_PTP",
				       &args, &data);
	if (ACPI_FAILURE(status)) {
		ACPI_EXCEPTION((AE_INFO, status, "Evaluating _PTP"));
		return -EINVAL;
	}

	/* _PTP returns 0 on success, nonzero otherwise */
	if (data)
		return -EINVAL;

	return 0;
}