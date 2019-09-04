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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct acpi_evaluate_info {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ns_check_object_type (struct acpi_evaluate_info*,union acpi_operand_object**,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static acpi_status
acpi_ns_check_package_elements(struct acpi_evaluate_info *info,
			       union acpi_operand_object **elements,
			       u8 type1,
			       u32 count1,
			       u8 type2, u32 count2, u32 start_index)
{
	union acpi_operand_object **this_element = elements;
	acpi_status status;
	u32 i;

	/*
	 * Up to two groups of package elements are supported by the data
	 * structure. All elements in each group must be of the same type.
	 * The second group can have a count of zero.
	 */
	for (i = 0; i < count1; i++) {
		status = acpi_ns_check_object_type(info, this_element,
						   type1, i + start_index);
		if (ACPI_FAILURE(status)) {
			return (status);
		}

		this_element++;
	}

	for (i = 0; i < count2; i++) {
		status = acpi_ns_check_object_type(info, this_element,
						   type2,
						   (i + count1 + start_index));
		if (ACPI_FAILURE(status)) {
			return (status);
		}

		this_element++;
	}

	return (AE_OK);
}