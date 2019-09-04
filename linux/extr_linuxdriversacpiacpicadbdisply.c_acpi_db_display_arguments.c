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
struct acpi_walk_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_db_decode_arguments (struct acpi_walk_state*) ; 
 struct acpi_walk_state* acpi_ds_get_current_walk_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_gbl_current_walk_list ; 
 int /*<<< orphan*/  acpi_os_printf (char*) ; 

void acpi_db_display_arguments(void)
{
	struct acpi_walk_state *walk_state;

	walk_state = acpi_ds_get_current_walk_state(acpi_gbl_current_walk_list);
	if (!walk_state) {
		acpi_os_printf("There is no method currently executing\n");
		return;
	}

	acpi_db_decode_arguments(walk_state);
}