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
typedef  int /*<<< orphan*/  acpi_string ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */

__attribute__((used)) static void
acpi_util_eval_error(acpi_handle h, acpi_string p, acpi_status s)
{
#ifdef ACPI_DEBUG_OUTPUT
	char prefix[80] = {'\0'};
	struct acpi_buffer buffer = {sizeof(prefix), prefix};
	acpi_get_name(h, ACPI_FULL_PATHNAME, &buffer);
	ACPI_DEBUG_PRINT((ACPI_DB_INFO, "Evaluate [%s.%s]: %s\n",
		(char *) prefix, p, acpi_format_exception(s)));
#else
	return;
#endif
}