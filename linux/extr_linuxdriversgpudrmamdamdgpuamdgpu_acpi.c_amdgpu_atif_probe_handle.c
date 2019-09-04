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
struct acpi_buffer {int member_0; char* member_1; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_method_name ;
typedef  int /*<<< orphan*/ * acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FULL_PATHNAME ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,...) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  acpi_get_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct acpi_buffer*) ; 
 int /*<<< orphan*/ * amdgpu_atpx_get_dhandle () ; 
 scalar_t__ amdgpu_has_atpx () ; 

__attribute__((used)) static acpi_handle amdgpu_atif_probe_handle(acpi_handle dhandle)
{
	acpi_handle handle = NULL;
	char acpi_method_name[255] = { 0 };
	struct acpi_buffer buffer = { sizeof(acpi_method_name), acpi_method_name };
	acpi_status status;

	/* For PX/HG systems, ATIF and ATPX are in the iGPU's namespace, on dGPU only
	 * systems, ATIF is in the dGPU's namespace.
	 */
	status = acpi_get_handle(dhandle, "ATIF", &handle);
	if (ACPI_SUCCESS(status))
		goto out;

	if (amdgpu_has_atpx()) {
		status = acpi_get_handle(amdgpu_atpx_get_dhandle(), "ATIF",
					 &handle);
		if (ACPI_SUCCESS(status))
			goto out;
	}

	DRM_DEBUG_DRIVER("No ATIF handle found\n");
	return NULL;
out:
	acpi_get_name(handle, ACPI_FULL_PATHNAME, &buffer);
	DRM_DEBUG_DRIVER("Found ATIF handle %s\n", acpi_method_name);
	return handle;
}