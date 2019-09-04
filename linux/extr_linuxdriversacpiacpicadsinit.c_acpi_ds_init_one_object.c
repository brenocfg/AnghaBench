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
struct TYPE_2__ {int info_flags; } ;
union acpi_operand_object {TYPE_1__ method; } ;
typedef  int /*<<< orphan*/  u32 ;
struct acpi_namespace_node {scalar_t__ owner_id; } ;
struct acpi_init_walk_info {scalar_t__ owner_id; int /*<<< orphan*/  device_count; int /*<<< orphan*/  non_serial_method_count; int /*<<< orphan*/  serialized_method_count; int /*<<< orphan*/  serial_method_count; int /*<<< orphan*/  method_count; int /*<<< orphan*/  op_region_count; int /*<<< orphan*/  object_count; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 int ACPI_METHOD_SERIALIZED ; 
#define  ACPI_TYPE_DEVICE 130 
#define  ACPI_TYPE_METHOD 129 
#define  ACPI_TYPE_REGION 128 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ds_auto_serialize_method (struct acpi_namespace_node*,union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ds_initialize_region (scalar_t__) ; 
 int /*<<< orphan*/  acpi_gbl_auto_serialize_methods ; 
 union acpi_operand_object* acpi_ns_get_attached_object (struct acpi_namespace_node*) ; 
 int acpi_ns_get_type (scalar_t__) ; 
 int /*<<< orphan*/  acpi_ut_get_node_name (scalar_t__) ; 

__attribute__((used)) static acpi_status
acpi_ds_init_one_object(acpi_handle obj_handle,
			u32 level, void *context, void **return_value)
{
	struct acpi_init_walk_info *info =
	    (struct acpi_init_walk_info *)context;
	struct acpi_namespace_node *node =
	    (struct acpi_namespace_node *)obj_handle;
	acpi_status status;
	union acpi_operand_object *obj_desc;

	ACPI_FUNCTION_ENTRY();

	/*
	 * We are only interested in NS nodes owned by the table that
	 * was just loaded
	 */
	if (node->owner_id != info->owner_id) {
		return (AE_OK);
	}

	info->object_count++;

	/* And even then, we are only interested in a few object types */

	switch (acpi_ns_get_type(obj_handle)) {
	case ACPI_TYPE_REGION:

		status = acpi_ds_initialize_region(obj_handle);
		if (ACPI_FAILURE(status)) {
			ACPI_EXCEPTION((AE_INFO, status,
					"During Region initialization %p [%4.4s]",
					obj_handle,
					acpi_ut_get_node_name(obj_handle)));
		}

		info->op_region_count++;
		break;

	case ACPI_TYPE_METHOD:
		/*
		 * Auto-serialization support. We will examine each method that is
		 * not_serialized to determine if it creates any Named objects. If
		 * it does, it will be marked serialized to prevent problems if
		 * the method is entered by two or more threads and an attempt is
		 * made to create the same named object twice -- which results in
		 * an AE_ALREADY_EXISTS exception and method abort.
		 */
		info->method_count++;
		obj_desc = acpi_ns_get_attached_object(node);
		if (!obj_desc) {
			break;
		}

		/* Ignore if already serialized */

		if (obj_desc->method.info_flags & ACPI_METHOD_SERIALIZED) {
			info->serial_method_count++;
			break;
		}

		if (acpi_gbl_auto_serialize_methods) {

			/* Parse/scan method and serialize it if necessary */

			acpi_ds_auto_serialize_method(node, obj_desc);
			if (obj_desc->method.
			    info_flags & ACPI_METHOD_SERIALIZED) {

				/* Method was just converted to Serialized */

				info->serial_method_count++;
				info->serialized_method_count++;
				break;
			}
		}

		info->non_serial_method_count++;
		break;

	case ACPI_TYPE_DEVICE:

		info->device_count++;
		break;

	default:

		break;
	}

	/*
	 * We ignore errors from above, and always return OK, since
	 * we don't want to abort the walk on a single error.
	 */
	return (AE_OK);
}