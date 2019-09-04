#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  count1; int /*<<< orphan*/  object_type1; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int expected_btypes; int /*<<< orphan*/  argument_list; } ;
union acpi_predefined_info {TYPE_3__ ret_info; TYPE_2__ info; } ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  ascii; } ;
struct acpi_namespace_node {TYPE_1__ name; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (char*) ; 
 int ACPI_RTYPE_PACKAGE ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  METHOD_GET_ARG_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acpi_ns_check_acpi_compliance (char*,struct acpi_namespace_node*,union acpi_predefined_info const*) ; 
 char* acpi_ns_get_normalized_pathname (struct acpi_namespace_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_os_printf (char*,...) ; 
 int /*<<< orphan*/  acpi_ut_get_expected_return_types (char*,int) ; 
 union acpi_predefined_info* acpi_ut_match_predefined_method (int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status
acpi_db_walk_for_predefined_names(acpi_handle obj_handle,
				  u32 nesting_level,
				  void *context, void **return_value)
{
	struct acpi_namespace_node *node =
	    (struct acpi_namespace_node *)obj_handle;
	u32 *count = (u32 *)context;
	const union acpi_predefined_info *predefined;
	const union acpi_predefined_info *package = NULL;
	char *pathname;
	char string_buffer[48];

	predefined = acpi_ut_match_predefined_method(node->name.ascii);
	if (!predefined) {
		return (AE_OK);
	}

	pathname = acpi_ns_get_normalized_pathname(node, TRUE);
	if (!pathname) {
		return (AE_OK);
	}

	/* If method returns a package, the info is in the next table entry */

	if (predefined->info.expected_btypes & ACPI_RTYPE_PACKAGE) {
		package = predefined + 1;
	}

	acpi_ut_get_expected_return_types(string_buffer,
					  predefined->info.expected_btypes);

	acpi_os_printf("%-32s Arguments %X, Return Types: %s", pathname,
		       METHOD_GET_ARG_COUNT(predefined->info.argument_list),
		       string_buffer);

	if (package) {
		acpi_os_printf(" (PkgType %2.2X, ObjType %2.2X, Count %2.2X)",
			       package->ret_info.type,
			       package->ret_info.object_type1,
			       package->ret_info.count1);
	}

	acpi_os_printf("\n");

	/* Check that the declared argument count matches the ACPI spec */

	acpi_ns_check_acpi_compliance(pathname, node, predefined);

	ACPI_FREE(pathname);
	(*count)++;
	return (AE_OK);
}