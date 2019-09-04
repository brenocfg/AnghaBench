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
typedef  scalar_t__ uint32_t ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;
struct TYPE_9__ {int /*<<< orphan*/  usStructureSize; } ;
struct TYPE_6__ {scalar_t__ ucVoltageMode; scalar_t__ ucVoltageType; int /*<<< orphan*/  usSize; } ;
struct TYPE_8__ {int ucVoltageControlI2cLine; TYPE_1__ sHeader; } ;
struct TYPE_7__ {int /*<<< orphan*/ * asVoltageObj; } ;
typedef  TYPE_2__ ATOM_VOLTAGE_OBJECT_INFO_V3_1 ;
typedef  TYPE_3__ ATOM_I2C_VOLTAGE_OBJECT_V3 ;
typedef  TYPE_4__ ATOM_COMMON_TABLE_HEADER ;

/* Variables and functions */
 scalar_t__ ATOM_INIT_VOLTAGE_REGULATOR ; 
 int BP_RESULT_NORECORD ; 
 int BP_RESULT_OK ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum bp_result get_voltage_ddc_info_v3(uint8_t *i2c_line,
	uint32_t index,
	ATOM_COMMON_TABLE_HEADER *header,
	uint8_t *address)
{
	enum bp_result result = BP_RESULT_NORECORD;
	ATOM_VOLTAGE_OBJECT_INFO_V3_1 *info =
		(ATOM_VOLTAGE_OBJECT_INFO_V3_1 *) address;

	uint8_t *voltage_current_object =
		(uint8_t *) (&(info->asVoltageObj[0]));

	while ((address + le16_to_cpu(header->usStructureSize)) > voltage_current_object) {
		ATOM_I2C_VOLTAGE_OBJECT_V3 *object =
			(ATOM_I2C_VOLTAGE_OBJECT_V3 *) voltage_current_object;

		if (object->sHeader.ucVoltageMode ==
			ATOM_INIT_VOLTAGE_REGULATOR) {
			if (object->sHeader.ucVoltageType == index) {
				*i2c_line = object->ucVoltageControlI2cLine
						^ 0x90;
				result = BP_RESULT_OK;
				break;
			}
		}

		voltage_current_object += le16_to_cpu(object->sHeader.usSize);
	}
	return result;
}