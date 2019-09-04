#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ascii; } ;
union acpi_operand_object {scalar_t__ type; TYPE_1__ name; scalar_t__ object; } ;
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct acpi_namespace_node {scalar_t__ type; TYPE_1__ name; scalar_t__ object; } ;
struct acpi_integrity_info {int /*<<< orphan*/  objects; int /*<<< orphan*/  nodes; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_DESC_TYPE_NAMED ; 
 scalar_t__ ACPI_DESC_TYPE_OPERAND ; 
 scalar_t__ ACPI_GET_DESCRIPTOR_TYPE (union acpi_operand_object*) ; 
 scalar_t__ ACPI_TYPE_LOCAL_ALIAS ; 
 scalar_t__ ACPI_TYPE_LOCAL_MAX ; 
 scalar_t__ ACPI_TYPE_LOCAL_METHOD_ALIAS ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 union acpi_operand_object* acpi_ns_get_attached_object (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_os_printf (char*,union acpi_operand_object*,...) ; 
 scalar_t__ acpi_ut_get_descriptor_name (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ut_valid_nameseg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status
acpi_db_integrity_walk(acpi_handle obj_handle,
		       u32 nesting_level, void *context, void **return_value)
{
	struct acpi_integrity_info *info =
	    (struct acpi_integrity_info *)context;
	struct acpi_namespace_node *node =
	    (struct acpi_namespace_node *)obj_handle;
	union acpi_operand_object *object;
	u8 alias = TRUE;

	info->nodes++;

	/* Verify the NS node, and dereference aliases */

	while (alias) {
		if (ACPI_GET_DESCRIPTOR_TYPE(node) != ACPI_DESC_TYPE_NAMED) {
			acpi_os_printf
			    ("Invalid Descriptor Type for Node %p [%s] - "
			     "is %2.2X should be %2.2X\n", node,
			     acpi_ut_get_descriptor_name(node),
			     ACPI_GET_DESCRIPTOR_TYPE(node),
			     ACPI_DESC_TYPE_NAMED);
			return (AE_OK);
		}

		if ((node->type == ACPI_TYPE_LOCAL_ALIAS) ||
		    (node->type == ACPI_TYPE_LOCAL_METHOD_ALIAS)) {
			node = (struct acpi_namespace_node *)node->object;
		} else {
			alias = FALSE;
		}
	}

	if (node->type > ACPI_TYPE_LOCAL_MAX) {
		acpi_os_printf("Invalid Object Type for Node %p, Type = %X\n",
			       node, node->type);
		return (AE_OK);
	}

	if (!acpi_ut_valid_nameseg(node->name.ascii)) {
		acpi_os_printf("Invalid AcpiName for Node %p\n", node);
		return (AE_OK);
	}

	object = acpi_ns_get_attached_object(node);
	if (object) {
		info->objects++;
		if (ACPI_GET_DESCRIPTOR_TYPE(object) != ACPI_DESC_TYPE_OPERAND) {
			acpi_os_printf
			    ("Invalid Descriptor Type for Object %p [%s]\n",
			     object, acpi_ut_get_descriptor_name(object));
		}
	}

	return (AE_OK);
}