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
 int /*<<< orphan*/  acpi_db_walk_for_execute ; 
 int /*<<< orphan*/  acpi_os_printf (char*,scalar_t__) ; 
 int /*<<< orphan*/  acpi_walk_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 

void acpi_db_evaluate_predefined_names(void)
{
	struct acpi_db_execute_walk info;

	info.count = 0;
	info.max_count = ACPI_UINT32_MAX;

	/* Search all nodes in namespace */

	(void)acpi_walk_namespace(ACPI_TYPE_ANY, ACPI_ROOT_OBJECT,
				  ACPI_UINT32_MAX, acpi_db_walk_for_execute,
				  NULL, (void *)&info, NULL);

	acpi_os_printf("Evaluated %u predefined names in the namespace\n",
		       info.count);
}