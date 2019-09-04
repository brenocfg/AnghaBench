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

/* Variables and functions */
 char* acpi_db_get_history_by_index (scalar_t__) ; 
 scalar_t__ acpi_gbl_next_cmd_num ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

char *acpi_db_get_from_history(char *command_num_arg)
{
	u32 cmd_num;

	if (command_num_arg == NULL) {
		cmd_num = acpi_gbl_next_cmd_num - 1;
	}

	else {
		cmd_num = strtoul(command_num_arg, NULL, 0);
	}

	return (acpi_db_get_history_by_index(cmd_num));
}