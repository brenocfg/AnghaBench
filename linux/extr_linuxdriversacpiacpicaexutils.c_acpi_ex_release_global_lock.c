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
typedef  int u32 ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int AML_FIELD_LOCK_RULE_MASK ; 
 int /*<<< orphan*/  acpi_ex_release_mutex_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_gbl_global_lock_mutex ; 
 int /*<<< orphan*/  ex_release_global_lock ; 
 int /*<<< orphan*/  return_VOID ; 

void acpi_ex_release_global_lock(u32 field_flags)
{
	acpi_status status;

	ACPI_FUNCTION_TRACE(ex_release_global_lock);

	/* Only use the lock if the always_lock bit is set */

	if (!(field_flags & AML_FIELD_LOCK_RULE_MASK)) {
		return_VOID;
	}

	/* Release the global lock */

	status = acpi_ex_release_mutex_object(acpi_gbl_global_lock_mutex);
	if (ACPI_FAILURE(status)) {

		/* Report the error, but there isn't much else we can do */

		ACPI_EXCEPTION((AE_INFO, status,
				"Could not release Global Lock"));
	}

	return_VOID;
}