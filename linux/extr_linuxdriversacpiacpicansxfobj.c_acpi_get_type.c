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
struct acpi_namespace_node {int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_object_type ;
typedef  scalar_t__ acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MTX_NAMESPACE ; 
 scalar_t__ ACPI_ROOT_OBJECT ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 
 struct acpi_namespace_node* acpi_ns_validate_handle (scalar_t__) ; 
 int /*<<< orphan*/  acpi_ut_acquire_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_release_mutex (int /*<<< orphan*/ ) ; 

acpi_status acpi_get_type(acpi_handle handle, acpi_object_type *ret_type)
{
	struct acpi_namespace_node *node;
	acpi_status status;

	/* Parameter Validation */

	if (!ret_type) {
		return (AE_BAD_PARAMETER);
	}

	/* Special case for the predefined Root Node (return type ANY) */

	if (handle == ACPI_ROOT_OBJECT) {
		*ret_type = ACPI_TYPE_ANY;
		return (AE_OK);
	}

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAILURE(status)) {
		return (status);
	}

	/* Convert and validate the handle */

	node = acpi_ns_validate_handle(handle);
	if (!node) {
		(void)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
		return (AE_BAD_PARAMETER);
	}

	*ret_type = node->type;

	status = acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
	return (status);
}