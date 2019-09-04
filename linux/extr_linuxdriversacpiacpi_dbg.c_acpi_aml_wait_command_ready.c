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

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DEBUGGER_COMMAND_PROMPT ; 
 int /*<<< orphan*/  ACPI_DEBUGGER_EXECUTE_PROMPT ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  acpi_os_get_line (char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_os_printf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acpi_aml_wait_command_ready(bool single_step,
				       char *buffer, size_t length)
{
	acpi_status status;

	if (single_step)
		acpi_os_printf("\n%1c ", ACPI_DEBUGGER_EXECUTE_PROMPT);
	else
		acpi_os_printf("\n%1c ", ACPI_DEBUGGER_COMMAND_PROMPT);

	status = acpi_os_get_line(buffer, length, NULL);
	if (ACPI_FAILURE(status))
		return -EINVAL;
	return 0;
}