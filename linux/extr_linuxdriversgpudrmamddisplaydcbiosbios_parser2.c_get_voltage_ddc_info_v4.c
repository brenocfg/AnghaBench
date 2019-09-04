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
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct atom_voltage_objects_info_v4_1 {int /*<<< orphan*/ * voltage_object; } ;
struct TYPE_2__ {scalar_t__ voltage_mode; scalar_t__ voltage_type; int /*<<< orphan*/  object_size; } ;
struct atom_i2c_voltage_object_v4 {int i2c_id; TYPE_1__ header; } ;
struct atom_common_table_header {int /*<<< orphan*/  structuresize; } ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;

/* Variables and functions */
 scalar_t__ ATOM_INIT_VOLTAGE_REGULATOR ; 
 int BP_RESULT_NORECORD ; 
 int BP_RESULT_OK ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum bp_result get_voltage_ddc_info_v4(
	uint8_t *i2c_line,
	uint32_t index,
	struct atom_common_table_header *header,
	uint8_t *address)
{
	enum bp_result result = BP_RESULT_NORECORD;
	struct atom_voltage_objects_info_v4_1 *info =
		(struct atom_voltage_objects_info_v4_1 *) address;

	uint8_t *voltage_current_object =
		(uint8_t *) (&(info->voltage_object[0]));

	while ((address + le16_to_cpu(header->structuresize)) >
						voltage_current_object) {
		struct atom_i2c_voltage_object_v4 *object =
			(struct atom_i2c_voltage_object_v4 *)
						voltage_current_object;

		if (object->header.voltage_mode ==
			ATOM_INIT_VOLTAGE_REGULATOR) {
			if (object->header.voltage_type == index) {
				*i2c_line = object->i2c_id ^ 0x90;
				result = BP_RESULT_OK;
				break;
			}
		}

		voltage_current_object +=
				le16_to_cpu(object->header.object_size);
	}
	return result;
}