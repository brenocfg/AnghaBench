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
struct TYPE_6__ {int argument_list; int /*<<< orphan*/  expected_btypes; } ;
union acpi_predefined_info {TYPE_3__ info; } ;
typedef  scalar_t__ u32 ;
struct acpi_namespace_node {int flags; scalar_t__ type; TYPE_2__* object; } ;
struct TYPE_4__ {scalar_t__ param_count; } ;
struct TYPE_5__ {TYPE_1__ method; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BIOS_ERROR_PREDEFINED (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_METHOD ; 
 int /*<<< orphan*/  ACPI_WARN_ALWAYS ; 
 int /*<<< orphan*/  AE_INFO ; 
 int ANOBJ_EVALUATED ; 
 int ARG_COUNT_IS_MINIMUM ; 
 scalar_t__ METHOD_GET_ARG_COUNT (int) ; 
 int /*<<< orphan*/  acpi_ut_get_type_name (scalar_t__) ; 

void
acpi_ns_check_acpi_compliance(char *pathname,
			      struct acpi_namespace_node *node,
			      const union acpi_predefined_info *predefined)
{
	u32 aml_param_count;
	u32 required_param_count;

	if (!predefined || (node->flags & ANOBJ_EVALUATED)) {
		return;
	}

	/* Get the ACPI-required arg count from the predefined info table */

	required_param_count =
	    METHOD_GET_ARG_COUNT(predefined->info.argument_list);

	/*
	 * If this object is not a control method, we can check if the ACPI
	 * spec requires that it be a method.
	 */
	if (node->type != ACPI_TYPE_METHOD) {
		if (required_param_count > 0) {

			/* Object requires args, must be implemented as a method */

			ACPI_BIOS_ERROR_PREDEFINED((AE_INFO, pathname,
						    ACPI_WARN_ALWAYS,
						    "Object (%s) must be a control method with %u arguments",
						    acpi_ut_get_type_name(node->
									  type),
						    required_param_count));
		} else if (!required_param_count
			   && !predefined->info.expected_btypes) {

			/* Object requires no args and no return value, must be a method */

			ACPI_BIOS_ERROR_PREDEFINED((AE_INFO, pathname,
						    ACPI_WARN_ALWAYS,
						    "Object (%s) must be a control method "
						    "with no arguments and no return value",
						    acpi_ut_get_type_name(node->
									  type)));
		}

		return;
	}

	/*
	 * This is a control method.
	 * Check that the ASL/AML-defined parameter count for this method
	 * matches the ACPI-required parameter count
	 *
	 * Some methods are allowed to have a "minimum" number of args (_SCP)
	 * because their definition in ACPI has changed over time.
	 *
	 * Note: These are BIOS errors in the declaration of the object
	 */
	aml_param_count = node->object->method.param_count;

	if (aml_param_count < required_param_count) {
		ACPI_BIOS_ERROR_PREDEFINED((AE_INFO, pathname, ACPI_WARN_ALWAYS,
					    "Insufficient arguments - "
					    "ASL declared %u, ACPI requires %u",
					    aml_param_count,
					    required_param_count));
	} else if ((aml_param_count > required_param_count)
		   && !(predefined->info.
			argument_list & ARG_COUNT_IS_MINIMUM)) {
		ACPI_BIOS_ERROR_PREDEFINED((AE_INFO, pathname, ACPI_WARN_ALWAYS,
					    "Excess arguments - "
					    "ASL declared %u, ACPI requires %u",
					    aml_param_count,
					    required_param_count));
	}
}