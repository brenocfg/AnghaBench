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
struct TYPE_6__ {scalar_t__ value; } ;
union acpi_object {TYPE_3__ integer; void* type; } ;
struct acpi_object_list {int count; union acpi_object* pointer; } ;
struct acpi_namespace_node {scalar_t__ type; TYPE_2__* object; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;
struct TYPE_4__ {scalar_t__ space_id; } ;
struct TYPE_5__ {TYPE_1__ region; } ;

/* Variables and functions */
 scalar_t__ ACPI_ADR_SPACE_EC ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MTX_NAMESPACE ; 
 scalar_t__ ACPI_REG_CONNECT ; 
 void* ACPI_TYPE_INTEGER ; 
 scalar_t__ ACPI_TYPE_REGION ; 
 int /*<<< orphan*/  METHOD_NAME__REG ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct acpi_object_list*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_get_handle (struct acpi_namespace_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct acpi_namespace_node* acpi_ns_get_next_node (struct acpi_namespace_node*,struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  acpi_ut_acquire_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_release_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_orphan_ec_reg_method ; 
 int /*<<< orphan*/  return_VOID ; 

__attribute__((used)) static void
acpi_ev_orphan_ec_reg_method(struct acpi_namespace_node *ec_device_node)
{
	acpi_handle reg_method;
	struct acpi_namespace_node *next_node;
	acpi_status status;
	struct acpi_object_list args;
	union acpi_object objects[2];

	ACPI_FUNCTION_TRACE(ev_orphan_ec_reg_method);

	if (!ec_device_node) {
		return_VOID;
	}

	/* Namespace is currently locked, must release */

	(void)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);

	/* Get a handle to a _REG method immediately under the EC device */

	status = acpi_get_handle(ec_device_node, METHOD_NAME__REG, &reg_method);
	if (ACPI_FAILURE(status)) {
		goto exit;	/* There is no _REG method present */
	}

	/*
	 * Execute the _REG method only if there is no Operation Region in
	 * this scope with the Embedded Controller space ID. Otherwise, it
	 * will already have been executed. Note, this allows for Regions
	 * with other space IDs to be present; but the code below will then
	 * execute the _REG method with the embedded_control space_ID argument.
	 */
	next_node = acpi_ns_get_next_node(ec_device_node, NULL);
	while (next_node) {
		if ((next_node->type == ACPI_TYPE_REGION) &&
		    (next_node->object) &&
		    (next_node->object->region.space_id == ACPI_ADR_SPACE_EC)) {
			goto exit;	/* Do not execute the _REG */
		}

		next_node = acpi_ns_get_next_node(ec_device_node, next_node);
	}

	/* Evaluate the _REG(embedded_control,Connect) method */

	args.count = 2;
	args.pointer = objects;
	objects[0].type = ACPI_TYPE_INTEGER;
	objects[0].integer.value = ACPI_ADR_SPACE_EC;
	objects[1].type = ACPI_TYPE_INTEGER;
	objects[1].integer.value = ACPI_REG_CONNECT;

	status = acpi_evaluate_object(reg_method, NULL, &args, NULL);

exit:
	/* We ignore all errors from above, don't care */

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	return_VOID;
}