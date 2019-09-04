#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  ascii; } ;
struct acpi_namespace_node {TYPE_1__ name; scalar_t__ parent; } ;
typedef  scalar_t__ acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_CONSOLE_OUTPUT ; 
 int /*<<< orphan*/  ACPI_DB_DUPLICATE_OUTPUT ; 
 int /*<<< orphan*/  ACPI_DB_REDIRECTABLE_OUTPUT ; 
 int /*<<< orphan*/  ACPI_DISPLAY_SUMMARY ; 
 int /*<<< orphan*/  ACPI_NAMESPACE_ROOT ; 
 int /*<<< orphan*/  ACPI_OWNER_ID_MAX ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 scalar_t__ acpi_db_convert_to_node (char*) ; 
 int /*<<< orphan*/  acpi_db_set_output_destination (int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_gbl_root_node ; 
 int /*<<< orphan*/  acpi_ns_dump_objects (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  acpi_os_printf (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void acpi_db_dump_namespace(char *start_arg, char *depth_arg)
{
	acpi_handle subtree_entry = acpi_gbl_root_node;
	u32 max_depth = ACPI_UINT32_MAX;

	/* No argument given, just start at the root and dump entire namespace */

	if (start_arg) {
		subtree_entry = acpi_db_convert_to_node(start_arg);
		if (!subtree_entry) {
			return;
		}

		/* Now we can check for the depth argument */

		if (depth_arg) {
			max_depth = strtoul(depth_arg, NULL, 0);
		}
	}

	acpi_db_set_output_destination(ACPI_DB_DUPLICATE_OUTPUT);

	if (((struct acpi_namespace_node *)subtree_entry)->parent) {
		acpi_os_printf("ACPI Namespace (from %4.4s (%p) subtree):\n",
			       ((struct acpi_namespace_node *)subtree_entry)->
			       name.ascii, subtree_entry);
	} else {
		acpi_os_printf("ACPI Namespace (from %s):\n",
			       ACPI_NAMESPACE_ROOT);
	}

	/* Display the subtree */

	acpi_db_set_output_destination(ACPI_DB_REDIRECTABLE_OUTPUT);
	acpi_ns_dump_objects(ACPI_TYPE_ANY, ACPI_DISPLAY_SUMMARY, max_depth,
			     ACPI_OWNER_ID_MAX, subtree_entry);
	acpi_db_set_output_destination(ACPI_DB_CONSOLE_OUTPUT);
}