#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  union acpi_operand_object {int dummy; } acpi_operand_object ;
struct acpi_namespace_node {TYPE_2__* object; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct TYPE_5__ {TYPE_1__ common; } ;

/* Variables and functions */
 scalar_t__ ACPI_DESC_TYPE_NAMED ; 
 scalar_t__ ACPI_DESC_TYPE_OPERAND ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,struct acpi_namespace_node*) ; 
 scalar_t__ ACPI_GET_DESCRIPTOR_TYPE (TYPE_2__*) ; 
 scalar_t__ ACPI_TYPE_LOCAL_DATA ; 
 int /*<<< orphan*/  ACPI_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  ns_get_attached_object ; 
 int /*<<< orphan*/  return_PTR (TYPE_2__*) ; 

union acpi_operand_object *acpi_ns_get_attached_object(struct
						       acpi_namespace_node
						       *node)
{
	ACPI_FUNCTION_TRACE_PTR(ns_get_attached_object, node);

	if (!node) {
		ACPI_WARNING((AE_INFO, "Null Node ptr"));
		return_PTR(NULL);
	}

	if (!node->object ||
	    ((ACPI_GET_DESCRIPTOR_TYPE(node->object) != ACPI_DESC_TYPE_OPERAND)
	     && (ACPI_GET_DESCRIPTOR_TYPE(node->object) !=
		 ACPI_DESC_TYPE_NAMED))
	    || ((node->object)->common.type == ACPI_TYPE_LOCAL_DATA)) {
		return_PTR(NULL);
	}

	return_PTR(node->object);
}