#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ value; } ;
struct TYPE_3__ {scalar_t__ count; union acpi_operand_object** elements; } ;
union acpi_operand_object {TYPE_2__ integer; TYPE_1__ package; } ;
typedef  scalar_t__ u32 ;
struct acpi_evaluate_info {int /*<<< orphan*/  node_flags; int /*<<< orphan*/  full_pathname; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SORT_DESCENDING ; 
 scalar_t__ ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  ACPI_WARN_PREDEFINED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ns_check_sorted_list (struct acpi_evaluate_info*,union acpi_operand_object*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static acpi_status
acpi_ns_repair_PSS(struct acpi_evaluate_info *info,
		   union acpi_operand_object **return_object_ptr)
{
	union acpi_operand_object *return_object = *return_object_ptr;
	union acpi_operand_object **outer_elements;
	u32 outer_element_count;
	union acpi_operand_object **elements;
	union acpi_operand_object *obj_desc;
	u32 previous_value;
	acpi_status status;
	u32 i;

	/*
	 * Entries (subpackages) in the _PSS Package must be sorted by power
	 * dissipation, in descending order. If it appears that the list is
	 * incorrectly sorted, sort it. We sort by cpu_frequency, since this
	 * should be proportional to the power.
	 */
	status = acpi_ns_check_sorted_list(info, return_object, 0, 6, 0,
					   ACPI_SORT_DESCENDING,
					   "CpuFrequency");
	if (ACPI_FAILURE(status)) {
		return (status);
	}

	/*
	 * We now know the list is correctly sorted by CPU frequency. Check if
	 * the power dissipation values are proportional.
	 */
	previous_value = ACPI_UINT32_MAX;
	outer_elements = return_object->package.elements;
	outer_element_count = return_object->package.count;

	for (i = 0; i < outer_element_count; i++) {
		elements = (*outer_elements)->package.elements;
		obj_desc = elements[1];	/* Index1 = power_dissipation */

		if ((u32)obj_desc->integer.value > previous_value) {
			ACPI_WARN_PREDEFINED((AE_INFO,
					      info->full_pathname,
					      info->node_flags,
					      "SubPackage[%u,%u] - suspicious power dissipation values",
					      i - 1, i));
		}

		previous_value = (u32) obj_desc->integer.value;
		outer_elements++;
	}

	return (AE_OK);
}