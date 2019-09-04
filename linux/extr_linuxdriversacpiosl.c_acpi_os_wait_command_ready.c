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
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_OK ; 
 int acpi_debugger_wait_command_ready () ; 

acpi_status acpi_os_wait_command_ready(void)
{
	int ret;

	ret = acpi_debugger_wait_command_ready();
	if (ret < 0)
		return AE_ERROR;
	return AE_OK;
}