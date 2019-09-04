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
typedef  union acpi_operand_object {int dummy; } acpi_operand_object ;
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;
struct acpi_walk_state {TYPE_3__* arguments; union acpi_operand_object* method_desc; struct acpi_namespace_node* method_node; } ;
struct acpi_namespace_node {scalar_t__ type; TYPE_2__* object; } ;
struct TYPE_6__ {union acpi_operand_object* object; } ;
struct TYPE_4__ {int /*<<< orphan*/  param_count; } ;
struct TYPE_5__ {TYPE_1__ method; } ;

/* Variables and functions */
 size_t ACPI_METHOD_NUM_ARGS ; 
 scalar_t__ ACPI_TYPE_METHOD ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  acpi_db_display_internal_object (union acpi_operand_object*,struct acpi_walk_state*) ; 
 struct acpi_namespace_node* acpi_gbl_root_node ; 
 int /*<<< orphan*/  acpi_os_printf (char*,...) ; 
 size_t acpi_ut_get_node_name (struct acpi_namespace_node*) ; 

void acpi_db_decode_arguments(struct acpi_walk_state *walk_state)
{
	u32 i;
	union acpi_operand_object *obj_desc;
	struct acpi_namespace_node *node;
	u8 display_args = FALSE;

	node = walk_state->method_node;
	obj_desc = walk_state->method_desc;

	/* There are no arguments for the module-level code case */

	if (node == acpi_gbl_root_node) {
		return;
	}

	if (!node) {
		acpi_os_printf
		    ("No method node (Executing subtree for buffer or opregion)\n");
		return;
	}

	if (node->type != ACPI_TYPE_METHOD) {
		acpi_os_printf("Executing subtree for Buffer/Package/Region\n");
		return;
	}

	/* Are any arguments actually set? */

	for (i = 0; i < ACPI_METHOD_NUM_ARGS; i++) {
		obj_desc = walk_state->arguments[i].object;
		if (obj_desc) {
			display_args = TRUE;
			break;
		}
	}

	/* If any are set, only display the ones that are set */

	if (display_args) {
		acpi_os_printf("Initialized Arguments for Method [%4.4s]:  "
			       "(%X arguments defined for method invocation)\n",
			       acpi_ut_get_node_name(node),
			       node->object->method.param_count);

		for (i = 0; i < ACPI_METHOD_NUM_ARGS; i++) {
			obj_desc = walk_state->arguments[i].object;
			if (obj_desc) {
				acpi_os_printf("  Arg%u:   ", i);
				acpi_db_display_internal_object(obj_desc,
								walk_state);
			}
		}
	} else {
		acpi_os_printf
		    ("No Arguments are initialized for method [%4.4s]\n",
		     acpi_ut_get_node_name(node));
	}
}