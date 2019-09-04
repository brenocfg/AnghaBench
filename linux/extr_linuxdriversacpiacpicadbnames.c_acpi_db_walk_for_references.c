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
typedef  int /*<<< orphan*/  u32 ;
typedef  void acpi_namespace_node ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  AE_OK ; 
 union acpi_operand_object* acpi_ns_get_attached_object (void*) ; 
 int /*<<< orphan*/  acpi_os_printf (char*,void*,...) ; 
 int /*<<< orphan*/  acpi_ut_get_node_name (void*) ; 

__attribute__((used)) static acpi_status
acpi_db_walk_for_references(acpi_handle obj_handle,
			    u32 nesting_level,
			    void *context, void **return_value)
{
	union acpi_operand_object *obj_desc =
	    (union acpi_operand_object *)context;
	struct acpi_namespace_node *node =
	    (struct acpi_namespace_node *)obj_handle;

	/* Check for match against the namespace node itself */

	if (node == (void *)obj_desc) {
		acpi_os_printf("Object is a Node [%4.4s]\n",
			       acpi_ut_get_node_name(node));
	}

	/* Check for match against the object attached to the node */

	if (acpi_ns_get_attached_object(node) == obj_desc) {
		acpi_os_printf("Reference at Node->Object %p [%4.4s]\n",
			       node, acpi_ut_get_node_name(node));
	}

	return (AE_OK);
}