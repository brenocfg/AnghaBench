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
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/ * acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_DEVICE ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  DMAR_DSM_FUNC_DRHD ; 
 int ENXIO ; 
 int /*<<< orphan*/  acpi_walk_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ dmar_detect_dsm (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmar_get_dsm_handle ; 
 int /*<<< orphan*/  dmar_global_lock ; 
 int dmar_hotplug_insert (int /*<<< orphan*/ *) ; 
 int dmar_hotplug_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmar_in_use () ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dmar_device_hotplug(acpi_handle handle, bool insert)
{
	int ret;
	acpi_handle tmp = NULL;
	acpi_status status;

	if (!dmar_in_use())
		return 0;

	if (dmar_detect_dsm(handle, DMAR_DSM_FUNC_DRHD)) {
		tmp = handle;
	} else {
		status = acpi_walk_namespace(ACPI_TYPE_DEVICE, handle,
					     ACPI_UINT32_MAX,
					     dmar_get_dsm_handle,
					     NULL, NULL, &tmp);
		if (ACPI_FAILURE(status)) {
			pr_warn("Failed to locate _DSM method.\n");
			return -ENXIO;
		}
	}
	if (tmp == NULL)
		return 0;

	down_write(&dmar_global_lock);
	if (insert)
		ret = dmar_hotplug_insert(tmp);
	else
		ret = dmar_hotplug_remove(tmp);
	up_write(&dmar_global_lock);

	return ret;
}