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
struct TYPE_14__ {union acpi_operand_object* handler; union acpi_operand_object** notify_list; } ;
struct TYPE_13__ {union acpi_operand_object* handler; union acpi_operand_object** notify_list; } ;
struct TYPE_12__ {union acpi_operand_object** notify_list; } ;
struct TYPE_11__ {union acpi_operand_object* handler; } ;
struct TYPE_10__ {union acpi_operand_object* handler; union acpi_operand_object** notify_list; } ;
struct TYPE_9__ {size_t count; union acpi_operand_object** elements; } ;
struct TYPE_8__ {size_t type; } ;
union acpi_operand_object {TYPE_7__ thermal_zone; TYPE_6__ processor; TYPE_5__ power_resource; TYPE_4__ region; TYPE_3__ device; TYPE_2__ package; TYPE_1__ common; } ;
typedef  size_t u32 ;

/* Variables and functions */
#define  ACPI_TYPE_BUFFER_FIELD 134 
#define  ACPI_TYPE_DEVICE 133 
 size_t ACPI_TYPE_LOCAL_REGION_FIELD ; 
 size_t ACPI_TYPE_NS_NODE_MAX ; 
#define  ACPI_TYPE_PACKAGE 132 
#define  ACPI_TYPE_POWER 131 
#define  ACPI_TYPE_PROCESSOR 130 
#define  ACPI_TYPE_REGION 129 
#define  ACPI_TYPE_THERMAL 128 
 int /*<<< orphan*/  acpi_gbl_num_objects ; 
 int /*<<< orphan*/ * acpi_gbl_obj_type_count ; 
 int /*<<< orphan*/  acpi_gbl_obj_type_count_misc ; 
 int /*<<< orphan*/  acpi_ns_get_secondary_object (union acpi_operand_object*) ; 

__attribute__((used)) static void acpi_db_enumerate_object(union acpi_operand_object *obj_desc)
{
	u32 i;

	if (!obj_desc) {
		return;
	}

	/* Enumerate this object first */

	acpi_gbl_num_objects++;

	if (obj_desc->common.type > ACPI_TYPE_NS_NODE_MAX) {
		acpi_gbl_obj_type_count_misc++;
	} else {
		acpi_gbl_obj_type_count[obj_desc->common.type]++;
	}

	/* Count the sub-objects */

	switch (obj_desc->common.type) {
	case ACPI_TYPE_PACKAGE:

		for (i = 0; i < obj_desc->package.count; i++) {
			acpi_db_enumerate_object(obj_desc->package.elements[i]);
		}
		break;

	case ACPI_TYPE_DEVICE:

		acpi_db_enumerate_object(obj_desc->device.notify_list[0]);
		acpi_db_enumerate_object(obj_desc->device.notify_list[1]);
		acpi_db_enumerate_object(obj_desc->device.handler);
		break;

	case ACPI_TYPE_BUFFER_FIELD:

		if (acpi_ns_get_secondary_object(obj_desc)) {
			acpi_gbl_obj_type_count[ACPI_TYPE_BUFFER_FIELD]++;
		}
		break;

	case ACPI_TYPE_REGION:

		acpi_gbl_obj_type_count[ACPI_TYPE_LOCAL_REGION_FIELD]++;
		acpi_db_enumerate_object(obj_desc->region.handler);
		break;

	case ACPI_TYPE_POWER:

		acpi_db_enumerate_object(obj_desc->power_resource.
					 notify_list[0]);
		acpi_db_enumerate_object(obj_desc->power_resource.
					 notify_list[1]);
		break;

	case ACPI_TYPE_PROCESSOR:

		acpi_db_enumerate_object(obj_desc->processor.notify_list[0]);
		acpi_db_enumerate_object(obj_desc->processor.notify_list[1]);
		acpi_db_enumerate_object(obj_desc->processor.handler);
		break;

	case ACPI_TYPE_THERMAL:

		acpi_db_enumerate_object(obj_desc->thermal_zone.notify_list[0]);
		acpi_db_enumerate_object(obj_desc->thermal_zone.notify_list[1]);
		acpi_db_enumerate_object(obj_desc->thermal_zone.handler);
		break;

	default:

		break;
	}
}