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
typedef  char acpi_namespace_node ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_CAST_PTR (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 char* acpi_db_convert_to_node (char*) ; 
 char* acpi_format_exception (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_handle ; 
 int /*<<< orphan*/  acpi_os_printf (char*,char*,char*) ; 
 int /*<<< orphan*/  acpi_unload_parent_table (int /*<<< orphan*/ ) ; 

void acpi_db_unload_acpi_table(char *object_name)
{
	struct acpi_namespace_node *node;
	acpi_status status;

	/* Translate name to an Named object */

	node = acpi_db_convert_to_node(object_name);
	if (!node) {
		return;
	}

	status = acpi_unload_parent_table(ACPI_CAST_PTR(acpi_handle, node));
	if (ACPI_SUCCESS(status)) {
		acpi_os_printf("Parent of [%s] (%p) unloaded and uninstalled\n",
			       object_name, node);
	} else {
		acpi_os_printf("%s, while unloading parent table of [%s]\n",
			       acpi_format_exception(status), object_name);
	}
}