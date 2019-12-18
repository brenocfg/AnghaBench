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
struct acpi_buffer {int member_0; int* member_1; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSIWMI_BIOS_GUID ; 
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 
 int /*<<< orphan*/  wmi_set_block (int /*<<< orphan*/ ,int,struct acpi_buffer*) ; 

__attribute__((used)) static int msi_wmi_set_block(int instance, int value)
{
	acpi_status status;

	struct acpi_buffer input = { sizeof(int), &value };

	pr_debug("Going to set block of instance: %d - value: %d\n",
		 instance, value);

	status = wmi_set_block(MSIWMI_BIOS_GUID, instance, &input);

	return ACPI_SUCCESS(status) ? 0 : 1;
}