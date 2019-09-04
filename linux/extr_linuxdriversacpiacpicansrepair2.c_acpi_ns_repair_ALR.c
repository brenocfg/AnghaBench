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
struct acpi_evaluate_info {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SORT_ASCENDING ; 
 int /*<<< orphan*/  acpi_ns_check_sorted_list (struct acpi_evaluate_info*,union acpi_operand_object*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static acpi_status
acpi_ns_repair_ALR(struct acpi_evaluate_info *info,
		   union acpi_operand_object **return_object_ptr)
{
	union acpi_operand_object *return_object = *return_object_ptr;
	acpi_status status;

	status = acpi_ns_check_sorted_list(info, return_object, 0, 2, 1,
					   ACPI_SORT_ASCENDING,
					   "AmbientIlluminance");

	return (status);
}