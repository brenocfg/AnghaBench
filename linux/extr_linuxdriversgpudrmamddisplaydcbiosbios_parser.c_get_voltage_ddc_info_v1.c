#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;
struct TYPE_9__ {int /*<<< orphan*/  usStructureSize; } ;
struct TYPE_6__ {int ucVoltageControlI2cLine; } ;
struct TYPE_8__ {int ucVoltageType; int /*<<< orphan*/  ucSize; TYPE_1__ asControl; } ;
struct TYPE_7__ {int /*<<< orphan*/ * asVoltageObj; } ;
typedef  TYPE_2__ ATOM_VOLTAGE_OBJECT_INFO ;
typedef  TYPE_3__ ATOM_VOLTAGE_OBJECT ;
typedef  TYPE_4__ ATOM_COMMON_TABLE_HEADER ;

/* Variables and functions */
 int BP_RESULT_NORECORD ; 
 int BP_RESULT_OK ; 
 int SET_VOLTAGE_INIT_MODE ; 
 int VOLTAGE_CONTROLLED_BY_I2C_MASK ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum bp_result get_voltage_ddc_info_v1(uint8_t *i2c_line,
	ATOM_COMMON_TABLE_HEADER *header,
	uint8_t *address)
{
	enum bp_result result = BP_RESULT_NORECORD;
	ATOM_VOLTAGE_OBJECT_INFO *info =
		(ATOM_VOLTAGE_OBJECT_INFO *) address;

	uint8_t *voltage_current_object = (uint8_t *) &info->asVoltageObj[0];

	while ((address + le16_to_cpu(header->usStructureSize)) > voltage_current_object) {
		ATOM_VOLTAGE_OBJECT *object =
			(ATOM_VOLTAGE_OBJECT *) voltage_current_object;

		if ((object->ucVoltageType == SET_VOLTAGE_INIT_MODE) &&
			(object->ucVoltageType &
				VOLTAGE_CONTROLLED_BY_I2C_MASK)) {

			*i2c_line = object->asControl.ucVoltageControlI2cLine
					^ 0x90;
			result = BP_RESULT_OK;
			break;
		}

		voltage_current_object += object->ucSize;
	}
	return result;
}