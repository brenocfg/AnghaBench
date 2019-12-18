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
typedef  int /*<<< orphan*/  u32 ;
struct tx2_uncore_pmu {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  present; } ;
struct acpi_device {TYPE_1__ status; } ;
typedef  enum tx2_uncore_type { ____Placeholder_tx2_uncore_type } tx2_uncore_type ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_OK ; 
 int PMU_TYPE_INVALID ; 
 scalar_t__ acpi_bus_get_device (int /*<<< orphan*/ ,struct acpi_device**) ; 
 scalar_t__ acpi_bus_get_status (struct acpi_device*) ; 
 int get_tx2_pmu_type (struct acpi_device*) ; 
 scalar_t__ tx2_uncore_pmu_add_dev (struct tx2_uncore_pmu*) ; 
 struct tx2_uncore_pmu* tx2_uncore_pmu_init_dev (struct device*,int /*<<< orphan*/ ,struct acpi_device*,int) ; 

__attribute__((used)) static acpi_status tx2_uncore_pmu_add(acpi_handle handle, u32 level,
				    void *data, void **return_value)
{
	struct tx2_uncore_pmu *tx2_pmu;
	struct acpi_device *adev;
	enum tx2_uncore_type type;

	if (acpi_bus_get_device(handle, &adev))
		return AE_OK;
	if (acpi_bus_get_status(adev) || !adev->status.present)
		return AE_OK;

	type = get_tx2_pmu_type(adev);
	if (type == PMU_TYPE_INVALID)
		return AE_OK;

	tx2_pmu = tx2_uncore_pmu_init_dev((struct device *)data,
			handle, adev, type);

	if (!tx2_pmu)
		return AE_ERROR;

	if (tx2_uncore_pmu_add_dev(tx2_pmu)) {
		/* Can't add the PMU device, abort */
		return AE_ERROR;
	}
	return AE_OK;
}