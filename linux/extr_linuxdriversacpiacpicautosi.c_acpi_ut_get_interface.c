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
struct acpi_interface_info {struct acpi_interface_info* next; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  acpi_string ;

/* Variables and functions */
 struct acpi_interface_info* acpi_gbl_supported_interfaces ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct acpi_interface_info *acpi_ut_get_interface(acpi_string interface_name)
{
	struct acpi_interface_info *next_interface;

	next_interface = acpi_gbl_supported_interfaces;
	while (next_interface) {
		if (!strcmp(interface_name, next_interface->name)) {
			return (next_interface);
		}

		next_interface = next_interface->next;
	}

	return (NULL);
}