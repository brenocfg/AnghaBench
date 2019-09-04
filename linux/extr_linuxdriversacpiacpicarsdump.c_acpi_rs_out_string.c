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

/* Variables and functions */
 int /*<<< orphan*/  acpi_os_printf (char*,...) ; 

__attribute__((used)) static void acpi_rs_out_string(const char *title, const char *value)
{

	acpi_os_printf("%27s : %s", title, value);
	if (!*value) {
		acpi_os_printf("[NULL NAMESTRING]");
	}
	acpi_os_printf("\n");
}