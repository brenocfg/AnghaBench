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
struct TYPE_6__ {int argument_list; } ;
union acpi_predefined_info {TYPE_3__ info; } ;
typedef  scalar_t__ u32 ;
struct acpi_namespace_node {int flags; scalar_t__ type; TYPE_2__* object; } ;
struct TYPE_4__ {scalar_t__ param_count; } ;
struct TYPE_5__ {TYPE_1__ method; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_INFO_PREDEFINED (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_METHOD ; 
 int /*<<< orphan*/  ACPI_WARN_ALWAYS ; 
 int /*<<< orphan*/  ACPI_WARN_PREDEFINED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int ANOBJ_EVALUATED ; 
 int ARG_COUNT_IS_MINIMUM ; 
 scalar_t__ METHOD_GET_ARG_COUNT (int) ; 
 int /*<<< orphan*/  acpi_ut_get_type_name (scalar_t__) ; 

void
acpi_ns_check_argument_count(char *pathname,
			     struct acpi_namespace_node *node,
			     u32 user_param_count,
			     const union acpi_predefined_info *predefined)
{
	u32 aml_param_count;
	u32 required_param_count;

	if (node->flags & ANOBJ_EVALUATED) {
		return;
	}

	if (!predefined) {
		/*
		 * Not a predefined name. Check the incoming user argument count
		 * against the count that is specified in the method/object.
		 */
		if (node->type != ACPI_TYPE_METHOD) {
			if (user_param_count) {
				ACPI_INFO_PREDEFINED((AE_INFO, pathname,
						      ACPI_WARN_ALWAYS,
						      "%u arguments were passed to a non-method ACPI object (%s)",
						      user_param_count,
						      acpi_ut_get_type_name
						      (node->type)));
			}

			return;
		}

		/*
		 * This is a control method. Check the parameter count.
		 * We can only check the incoming argument count against the
		 * argument count declared for the method in the ASL/AML.
		 *
		 * Emit a message if too few or too many arguments have been passed
		 * by the caller.
		 *
		 * Note: Too many arguments will not cause the method to
		 * fail. However, the method will fail if there are too few
		 * arguments and the method attempts to use one of the missing ones.
		 */
		aml_param_count = node->object->method.param_count;

		if (user_param_count < aml_param_count) {
			ACPI_WARN_PREDEFINED((AE_INFO, pathname,
					      ACPI_WARN_ALWAYS,
					      "Insufficient arguments - "
					      "Caller passed %u, method requires %u",
					      user_param_count,
					      aml_param_count));
		} else if (user_param_count > aml_param_count) {
			ACPI_INFO_PREDEFINED((AE_INFO, pathname,
					      ACPI_WARN_ALWAYS,
					      "Excess arguments - "
					      "Caller passed %u, method requires %u",
					      user_param_count,
					      aml_param_count));
		}

		return;
	}

	/*
	 * This is a predefined name. Validate the user-supplied parameter
	 * count against the ACPI specification. We don't validate against
	 * the method itself because what is important here is that the
	 * caller is in conformance with the spec. (The arg count for the
	 * method was checked against the ACPI spec earlier.)
	 *
	 * Some methods are allowed to have a "minimum" number of args (_SCP)
	 * because their definition in ACPI has changed over time.
	 */
	required_param_count =
	    METHOD_GET_ARG_COUNT(predefined->info.argument_list);

	if (user_param_count < required_param_count) {
		ACPI_WARN_PREDEFINED((AE_INFO, pathname, ACPI_WARN_ALWAYS,
				      "Insufficient arguments - "
				      "Caller passed %u, ACPI requires %u",
				      user_param_count, required_param_count));
	} else if ((user_param_count > required_param_count) &&
		   !(predefined->info.argument_list & ARG_COUNT_IS_MINIMUM)) {
		ACPI_INFO_PREDEFINED((AE_INFO, pathname, ACPI_WARN_ALWAYS,
				      "Excess arguments - "
				      "Caller passed %u, ACPI requires %u",
				      user_param_count, required_param_count));
	}
}