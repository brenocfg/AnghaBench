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
struct acpi_db_execute_walk {scalar_t__ count; int /*<<< orphan*/  max_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ROOT_OBJECT ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  acpi_db_evaluate_one_predefined_name ; 
 int /*<<< orphan*/  acpi_os_printf (char*,scalar_t__) ; 
 int /*<<< orphan*/  acpi_walk_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acpi_db_evaluate_all_predefined_names(char *count_arg)
{
	struct acpi_db_execute_walk info;

	info.count = 0;
	info.max_count = ACPI_UINT32_MAX;

	if (count_arg) {
		info.max_count = strtoul(count_arg, NULL, 0);
	}

	/* Search all nodes in namespace */

	(void)acpi_walk_namespace(ACPI_TYPE_ANY, ACPI_ROOT_OBJECT,
				  ACPI_UINT32_MAX,
				  acpi_db_evaluate_one_predefined_name, NULL,
				  (void *)&info, NULL);

	acpi_os_printf("Evaluated %u predefined names in the namespace\n",
		       info.count);
}