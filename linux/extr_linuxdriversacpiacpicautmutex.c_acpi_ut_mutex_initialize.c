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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_NUM_MUTEX ; 
 int /*<<< orphan*/  acpi_gbl_gpe_lock ; 
 int /*<<< orphan*/  acpi_gbl_hardware_lock ; 
 int /*<<< orphan*/  acpi_gbl_namespace_rw_lock ; 
 int /*<<< orphan*/  acpi_gbl_osi_mutex ; 
 int /*<<< orphan*/  acpi_gbl_reference_count_lock ; 
 int /*<<< orphan*/  acpi_os_create_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_os_create_mutex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_os_create_raw_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ut_create_mutex (scalar_t__) ; 
 int /*<<< orphan*/  acpi_ut_create_rw_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ut_mutex_initialize ; 

acpi_status acpi_ut_mutex_initialize(void)
{
	u32 i;
	acpi_status status;

	ACPI_FUNCTION_TRACE(ut_mutex_initialize);

	/* Create each of the predefined mutex objects */

	for (i = 0; i < ACPI_NUM_MUTEX; i++) {
		status = acpi_ut_create_mutex(i);
		if (ACPI_FAILURE(status)) {
			return_ACPI_STATUS(status);
		}
	}

	/* Create the spinlocks for use at interrupt level or for speed */

	status = acpi_os_create_lock (&acpi_gbl_gpe_lock);
	if (ACPI_FAILURE (status)) {
		return_ACPI_STATUS (status);
	}

	status = acpi_os_create_raw_lock(&acpi_gbl_hardware_lock);
	if (ACPI_FAILURE (status)) {
		return_ACPI_STATUS (status);
	}

	status = acpi_os_create_lock(&acpi_gbl_reference_count_lock);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/* Mutex for _OSI support */

	status = acpi_os_create_mutex(&acpi_gbl_osi_mutex);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/* Create the reader/writer lock for namespace access */

	status = acpi_ut_create_rw_lock(&acpi_gbl_namespace_rw_lock);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	return_ACPI_STATUS(status);
}