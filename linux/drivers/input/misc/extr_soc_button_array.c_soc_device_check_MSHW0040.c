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
struct TYPE_2__ {scalar_t__ value; } ;
union acpi_object {TYPE_1__ integer; } ;
typedef  scalar_t__ u64 ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (union acpi_object*) ; 
 int /*<<< orphan*/  ACPI_HANDLE (struct device*) ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int ENODEV ; 
 int /*<<< orphan*/  MSHW0040_DSM_GET_OMPR ; 
 int /*<<< orphan*/  MSHW0040_DSM_REVISION ; 
 int /*<<< orphan*/  MSHW0040_DSM_UUID ; 
 union acpi_object* acpi_evaluate_dsm_typed (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,scalar_t__) ; 

__attribute__((used)) static int soc_device_check_MSHW0040(struct device *dev)
{
	acpi_handle handle = ACPI_HANDLE(dev);
	union acpi_object *result;
	u64 oem_platform_rev = 0;	// valid revisions are nonzero

	// get OEM platform revision
	result = acpi_evaluate_dsm_typed(handle, &MSHW0040_DSM_UUID,
					 MSHW0040_DSM_REVISION,
					 MSHW0040_DSM_GET_OMPR, NULL,
					 ACPI_TYPE_INTEGER);

	if (result) {
		oem_platform_rev = result->integer.value;
		ACPI_FREE(result);
	}

	/*
	 * If the revision is zero here, the _DSM evaluation has failed. This
	 * indicates that we have a Pro 4 or Book 1 and this driver should not
	 * be used.
	 */
	if (oem_platform_rev == 0)
		return -ENODEV;

	dev_dbg(dev, "OEM Platform Revision %llu\n", oem_platform_rev);

	return 0;
}