#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int flags; } ;
struct TYPE_13__ {int /*<<< orphan*/ * handler; struct acpi_namespace_node* node; scalar_t__ length; scalar_t__ address; int /*<<< orphan*/  space_id; } ;
struct TYPE_12__ {struct acpi_namespace_node* scope_node; int /*<<< orphan*/ * method_REG; int /*<<< orphan*/  aml_length; int /*<<< orphan*/ * aml_start; } ;
union acpi_operand_object {TYPE_7__ common; TYPE_6__ region; TYPE_5__ extra; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct acpi_walk_state {TYPE_4__* scope_info; TYPE_2__* op; } ;
struct acpi_namespace_node {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_10__ {struct acpi_namespace_node* node; } ;
struct TYPE_11__ {TYPE_3__ scope; } ;
struct TYPE_8__ {struct acpi_namespace_node* node; } ;
struct TYPE_9__ {TYPE_1__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_LOAD ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_REGION ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int AOPOBJ_OBJECT_INITIALIZED ; 
 int AOPOBJ_REG_CONNECTED ; 
 int AOPOBJ_SETUP_COMPLETE ; 
 int /*<<< orphan*/  acpi_is_valid_space_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ns_attach_object (struct acpi_namespace_node*,union acpi_operand_object*,int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_ns_get_attached_object (struct acpi_namespace_node*) ; 
 union acpi_operand_object* acpi_ns_get_secondary_object (union acpi_operand_object*) ; 
 union acpi_operand_object* acpi_ut_create_internal_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_get_region_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_remove_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ex_create_region ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ex_create_region(u8 * aml_start,
		      u32 aml_length,
		      u8 space_id, struct acpi_walk_state *walk_state)
{
	acpi_status status;
	union acpi_operand_object *obj_desc;
	struct acpi_namespace_node *node;
	union acpi_operand_object *region_obj2;

	ACPI_FUNCTION_TRACE(ex_create_region);

	/* Get the Namespace Node */

	node = walk_state->op->common.node;

	/*
	 * If the region object is already attached to this node,
	 * just return
	 */
	if (acpi_ns_get_attached_object(node)) {
		return_ACPI_STATUS(AE_OK);
	}

	/*
	 * Space ID must be one of the predefined IDs, or in the user-defined
	 * range
	 */
	if (!acpi_is_valid_space_id(space_id)) {
		/*
		 * Print an error message, but continue. We don't want to abort
		 * a table load for this exception. Instead, if the region is
		 * actually used at runtime, abort the executing method.
		 */
		ACPI_ERROR((AE_INFO,
			    "Invalid/unknown Address Space ID: 0x%2.2X",
			    space_id));
	}

	ACPI_DEBUG_PRINT((ACPI_DB_LOAD, "Region Type - %s (0x%X)\n",
			  acpi_ut_get_region_name(space_id), space_id));

	/* Create the region descriptor */

	obj_desc = acpi_ut_create_internal_object(ACPI_TYPE_REGION);
	if (!obj_desc) {
		status = AE_NO_MEMORY;
		goto cleanup;
	}

	/*
	 * Remember location in AML stream of address & length
	 * operands since they need to be evaluated at run time.
	 */
	region_obj2 = acpi_ns_get_secondary_object(obj_desc);
	region_obj2->extra.aml_start = aml_start;
	region_obj2->extra.aml_length = aml_length;
	region_obj2->extra.method_REG = NULL;
	if (walk_state->scope_info) {
		region_obj2->extra.scope_node =
		    walk_state->scope_info->scope.node;
	} else {
		region_obj2->extra.scope_node = node;
	}

	/* Init the region from the operands */

	obj_desc->region.space_id = space_id;
	obj_desc->region.address = 0;
	obj_desc->region.length = 0;
	obj_desc->region.node = node;
	obj_desc->region.handler = NULL;
	obj_desc->common.flags &=
	    ~(AOPOBJ_SETUP_COMPLETE | AOPOBJ_REG_CONNECTED |
	      AOPOBJ_OBJECT_INITIALIZED);

	/* Install the new region object in the parent Node */

	status = acpi_ns_attach_object(node, obj_desc, ACPI_TYPE_REGION);

cleanup:

	/* Remove local reference to the object */

	acpi_ut_remove_reference(obj_desc);
	return_ACPI_STATUS(status);
}