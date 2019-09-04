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
struct acpi_buffer {scalar_t__ pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FULL_PATHNAME ; 
 unsigned long long ACPI_STA_DEVICE_PRESENT ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 int /*<<< orphan*/  acpi_get_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_buffer*) ; 
 scalar_t__ check_sta_before_sun ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,...) ; 

__attribute__((used)) static int
check_slot(acpi_handle handle, unsigned long long *sun)
{
	int device = -1;
	unsigned long long adr, sta;
	acpi_status status;
	struct acpi_buffer buffer = { ACPI_ALLOCATE_BUFFER, NULL };

	acpi_get_name(handle, ACPI_FULL_PATHNAME, &buffer);
	pr_debug("Checking slot on path: %s\n", (char *)buffer.pointer);

	if (check_sta_before_sun) {
		/* If SxFy doesn't have _STA, we just assume it's there */
		status = acpi_evaluate_integer(handle, "_STA", NULL, &sta);
		if (ACPI_SUCCESS(status) && !(sta & ACPI_STA_DEVICE_PRESENT))
			goto out;
	}

	status = acpi_evaluate_integer(handle, "_ADR", NULL, &adr);
	if (ACPI_FAILURE(status)) {
		pr_debug("_ADR returned %d on %s\n",
			 status, (char *)buffer.pointer);
		goto out;
	}

	/* No _SUN == not a slot == bail */
	status = acpi_evaluate_integer(handle, "_SUN", NULL, sun);
	if (ACPI_FAILURE(status)) {
		pr_debug("_SUN returned %d on %s\n",
			 status, (char *)buffer.pointer);
		goto out;
	}

	device = (adr >> 16) & 0xffff;
out:
	kfree(buffer.pointer);
	return device;
}