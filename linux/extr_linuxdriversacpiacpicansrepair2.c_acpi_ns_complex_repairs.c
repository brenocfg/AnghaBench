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
struct acpi_repair_info {int /*<<< orphan*/  (* repair_function ) (struct acpi_evaluate_info*,union acpi_operand_object**) ;} ;
struct acpi_namespace_node {int dummy; } ;
struct acpi_evaluate_info {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 struct acpi_repair_info* acpi_ns_match_complex_repair (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  stub1 (struct acpi_evaluate_info*,union acpi_operand_object**) ; 

acpi_status
acpi_ns_complex_repairs(struct acpi_evaluate_info *info,
			struct acpi_namespace_node *node,
			acpi_status validate_status,
			union acpi_operand_object **return_object_ptr)
{
	const struct acpi_repair_info *predefined;
	acpi_status status;

	/* Check if this name is in the list of repairable names */

	predefined = acpi_ns_match_complex_repair(node);
	if (!predefined) {
		return (validate_status);
	}

	status = predefined->repair_function(info, return_object_ptr);
	return (status);
}