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
struct TYPE_3__ {scalar_t__ expected_btypes; } ;
union acpi_predefined_info {TYPE_1__ info; } ;
struct TYPE_4__ {scalar_t__ type; } ;
union acpi_operand_object {TYPE_2__ common; } ;
typedef  int /*<<< orphan*/  u32 ;
struct acpi_namespace_node {int /*<<< orphan*/  flags; } ;
struct acpi_evaluate_info {int return_flags; union acpi_operand_object* parent_package; union acpi_predefined_info* predefined; } ;
typedef  scalar_t__ acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_NOT_PACKAGE_ELEMENT ; 
 int ACPI_OBJECT_REPAIRED ; 
 scalar_t__ ACPI_RTYPE_ALL ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 scalar_t__ AE_AML_OPERAND_TYPE ; 
 scalar_t__ AE_AML_OPERAND_VALUE ; 
 scalar_t__ AE_CTRL_RETURN_VALUE ; 
 scalar_t__ AE_OK ; 
 int /*<<< orphan*/  ANOBJ_EVALUATED ; 
 scalar_t__ acpi_gbl_disable_auto_repair ; 
 scalar_t__ acpi_ns_check_object_type (struct acpi_evaluate_info*,union acpi_operand_object**,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_ns_check_package (struct acpi_evaluate_info*,union acpi_operand_object**) ; 
 scalar_t__ acpi_ns_complex_repairs (struct acpi_evaluate_info*,struct acpi_namespace_node*,scalar_t__,union acpi_operand_object**) ; 

acpi_status
acpi_ns_check_return_value(struct acpi_namespace_node *node,
			   struct acpi_evaluate_info *info,
			   u32 user_param_count,
			   acpi_status return_status,
			   union acpi_operand_object **return_object_ptr)
{
	acpi_status status;
	const union acpi_predefined_info *predefined;

	/* If not a predefined name, we cannot validate the return object */

	predefined = info->predefined;
	if (!predefined) {
		return (AE_OK);
	}

	/*
	 * If the method failed or did not actually return an object, we cannot
	 * validate the return object
	 */
	if ((return_status != AE_OK) && (return_status != AE_CTRL_RETURN_VALUE)) {
		return (AE_OK);
	}

	/*
	 * Return value validation and possible repair.
	 *
	 * 1) Don't perform return value validation/repair if this feature
	 * has been disabled via a global option.
	 *
	 * 2) We have a return value, but if one wasn't expected, just exit,
	 * this is not a problem. For example, if the "Implicit Return"
	 * feature is enabled, methods will always return a value.
	 *
	 * 3) If the return value can be of any type, then we cannot perform
	 * any validation, just exit.
	 */
	if (acpi_gbl_disable_auto_repair ||
	    (!predefined->info.expected_btypes) ||
	    (predefined->info.expected_btypes == ACPI_RTYPE_ALL)) {
		return (AE_OK);
	}

	/*
	 * Check that the type of the main return object is what is expected
	 * for this predefined name
	 */
	status = acpi_ns_check_object_type(info, return_object_ptr,
					   predefined->info.expected_btypes,
					   ACPI_NOT_PACKAGE_ELEMENT);
	if (ACPI_FAILURE(status)) {
		goto exit;
	}

	/*
	 *
	 * 4) If there is no return value and it is optional, just return
	 * AE_OK (_WAK).
	 */
	if (!(*return_object_ptr)) {
		goto exit;
	}

	/*
	 * For returned Package objects, check the type of all sub-objects.
	 * Note: Package may have been newly created by call above.
	 */
	if ((*return_object_ptr)->common.type == ACPI_TYPE_PACKAGE) {
		info->parent_package = *return_object_ptr;
		status = acpi_ns_check_package(info, return_object_ptr);
		if (ACPI_FAILURE(status)) {

			/* We might be able to fix some errors */

			if ((status != AE_AML_OPERAND_TYPE) &&
			    (status != AE_AML_OPERAND_VALUE)) {
				goto exit;
			}
		}
	}

	/*
	 * The return object was OK, or it was successfully repaired above.
	 * Now make some additional checks such as verifying that package
	 * objects are sorted correctly (if required) or buffer objects have
	 * the correct data width (bytes vs. dwords). These repairs are
	 * performed on a per-name basis, i.e., the code is specific to
	 * particular predefined names.
	 */
	status = acpi_ns_complex_repairs(info, node, status, return_object_ptr);

exit:
	/*
	 * If the object validation failed or if we successfully repaired one
	 * or more objects, mark the parent node to suppress further warning
	 * messages during the next evaluation of the same method/object.
	 */
	if (ACPI_FAILURE(status) || (info->return_flags & ACPI_OBJECT_REPAIRED)) {
		node->flags |= ANOBJ_EVALUATED;
	}

	return (status);
}