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
typedef  union acpi_operand_object {int dummy; } acpi_operand_object ;
struct acpi_namespace_node {int dummy; } ;
struct acpi_evaluate_info {int /*<<< orphan*/  node; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_NS_NO_UPSEARCH ; 
 int /*<<< orphan*/  ACPI_SORT_DESCENDING ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ns_check_sorted_list (struct acpi_evaluate_info*,union acpi_operand_object*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  acpi_ns_get_node (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct acpi_namespace_node**) ; 

__attribute__((used)) static acpi_status
acpi_ns_repair_TSS(struct acpi_evaluate_info *info,
		   union acpi_operand_object **return_object_ptr)
{
	union acpi_operand_object *return_object = *return_object_ptr;
	acpi_status status;
	struct acpi_namespace_node *node;

	/*
	 * We can only sort the _TSS return package if there is no _PSS in the
	 * same scope. This is because if _PSS is present, the ACPI specification
	 * dictates that the _TSS Power Dissipation field is to be ignored, and
	 * therefore some BIOSs leave garbage values in the _TSS Power field(s).
	 * In this case, it is best to just return the _TSS package as-is.
	 * (May, 2011)
	 */
	status = acpi_ns_get_node(info->node, "^_PSS",
				  ACPI_NS_NO_UPSEARCH, &node);
	if (ACPI_SUCCESS(status)) {
		return (AE_OK);
	}

	status = acpi_ns_check_sorted_list(info, return_object, 0, 5, 1,
					   ACPI_SORT_DESCENDING,
					   "PowerDissipation");

	return (status);
}