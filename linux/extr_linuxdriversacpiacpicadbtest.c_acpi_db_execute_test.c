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

/* Variables and functions */
 int ACPI_TYPE_NOT_FOUND ; 
#define  CMD_TEST_OBJECTS 129 
#define  CMD_TEST_PREDEFINED 128 
 int /*<<< orphan*/  acpi_db_evaluate_all_predefined_names (int /*<<< orphan*/ *) ; 
 int acpi_db_match_argument (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_db_test_all_objects () ; 
 int /*<<< orphan*/  acpi_db_test_types ; 
 int /*<<< orphan*/  acpi_os_printf (char*) ; 
 int /*<<< orphan*/  acpi_ut_strupr (char*) ; 

void acpi_db_execute_test(char *type_arg)
{
	u32 temp;

	acpi_ut_strupr(type_arg);
	temp = acpi_db_match_argument(type_arg, acpi_db_test_types);
	if (temp == ACPI_TYPE_NOT_FOUND) {
		acpi_os_printf("Invalid or unsupported argument\n");
		return;
	}

	switch (temp) {
	case CMD_TEST_OBJECTS:

		acpi_db_test_all_objects();
		break;

	case CMD_TEST_PREDEFINED:

		acpi_db_evaluate_all_predefined_names(NULL);
		break;

	default:
		break;
	}
}