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
struct acpi_device {int /*<<< orphan*/  handle; struct acpi_device* parent; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  METHOD_NAME__CRS ; 
 int /*<<< orphan*/  acpi_walk_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct acpi_device* hv_acpi_dev ; 
 scalar_t__ hyperv_mmio ; 
 int /*<<< orphan*/  probe_event ; 
 int /*<<< orphan*/  vmbus_acpi_remove (struct acpi_device*) ; 
 int /*<<< orphan*/  vmbus_reserve_fb () ; 
 int /*<<< orphan*/  vmbus_walk_resources ; 

__attribute__((used)) static int vmbus_acpi_add(struct acpi_device *device)
{
	acpi_status result;
	int ret_val = -ENODEV;
	struct acpi_device *ancestor;

	hv_acpi_dev = device;

	result = acpi_walk_resources(device->handle, METHOD_NAME__CRS,
					vmbus_walk_resources, NULL);

	if (ACPI_FAILURE(result))
		goto acpi_walk_err;
	/*
	 * Some ancestor of the vmbus acpi device (Gen1 or Gen2
	 * firmware) is the VMOD that has the mmio ranges. Get that.
	 */
	for (ancestor = device->parent; ancestor; ancestor = ancestor->parent) {
		result = acpi_walk_resources(ancestor->handle, METHOD_NAME__CRS,
					     vmbus_walk_resources, NULL);

		if (ACPI_FAILURE(result))
			continue;
		if (hyperv_mmio) {
			vmbus_reserve_fb();
			break;
		}
	}
	ret_val = 0;

acpi_walk_err:
	complete(&probe_event);
	if (ret_val)
		vmbus_acpi_remove(device);
	return ret_val;
}