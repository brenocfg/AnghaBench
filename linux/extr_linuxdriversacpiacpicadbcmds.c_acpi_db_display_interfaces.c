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
struct acpi_interface_info {int flags; char* name; struct acpi_interface_info* next; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ACPI_OSI_INVALID ; 
 int /*<<< orphan*/  ACPI_WAIT_FOREVER ; 
 int /*<<< orphan*/  acpi_format_exception (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_gbl_osi_mutex ; 
 struct acpi_interface_info* acpi_gbl_supported_interfaces ; 
 int /*<<< orphan*/  acpi_install_interface (char*) ; 
 int /*<<< orphan*/  acpi_os_acquire_mutex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_printf (char*,...) ; 
 int /*<<< orphan*/  acpi_os_release_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_remove_interface (char*) ; 
 int /*<<< orphan*/  acpi_ut_strupr (char*) ; 
 char* strstr (char*,char*) ; 

void acpi_db_display_interfaces(char *action_arg, char *interface_name_arg)
{
	struct acpi_interface_info *next_interface;
	char *sub_string;
	acpi_status status;

	/* If no arguments, just display current interface list */

	if (!action_arg) {
		(void)acpi_os_acquire_mutex(acpi_gbl_osi_mutex,
					    ACPI_WAIT_FOREVER);

		next_interface = acpi_gbl_supported_interfaces;
		while (next_interface) {
			if (!(next_interface->flags & ACPI_OSI_INVALID)) {
				acpi_os_printf("%s\n", next_interface->name);
			}

			next_interface = next_interface->next;
		}

		acpi_os_release_mutex(acpi_gbl_osi_mutex);
		return;
	}

	/* If action_arg exists, so must interface_name_arg */

	if (!interface_name_arg) {
		acpi_os_printf("Missing Interface Name argument\n");
		return;
	}

	/* Uppercase the action for match below */

	acpi_ut_strupr(action_arg);

	/* install - install an interface */

	sub_string = strstr("INSTALL", action_arg);
	if (sub_string) {
		status = acpi_install_interface(interface_name_arg);
		if (ACPI_FAILURE(status)) {
			acpi_os_printf("%s, while installing \"%s\"\n",
				       acpi_format_exception(status),
				       interface_name_arg);
		}
		return;
	}

	/* remove - remove an interface */

	sub_string = strstr("REMOVE", action_arg);
	if (sub_string) {
		status = acpi_remove_interface(interface_name_arg);
		if (ACPI_FAILURE(status)) {
			acpi_os_printf("%s, while removing \"%s\"\n",
				       acpi_format_exception(status),
				       interface_name_arg);
		}
		return;
	}

	/* Invalid action_arg */

	acpi_os_printf("Invalid action argument: %s\n", action_arg);
	return;
}