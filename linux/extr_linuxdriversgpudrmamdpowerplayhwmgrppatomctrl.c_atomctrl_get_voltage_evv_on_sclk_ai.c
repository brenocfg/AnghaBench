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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct pp_hwmgr {struct amdgpu_device* adev; } ;
struct TYPE_4__ {int /*<<< orphan*/  atom_context; } ;
struct amdgpu_device {TYPE_1__ mode_info; } ;
struct TYPE_6__ {int /*<<< orphan*/  ulVoltageLevel; } ;
struct TYPE_5__ {int /*<<< orphan*/  ulSCLKFreq; int /*<<< orphan*/  usVoltageLevel; int /*<<< orphan*/  ucVoltageMode; int /*<<< orphan*/  ucVoltageType; } ;
typedef  TYPE_2__ GET_VOLTAGE_INFO_INPUT_PARAMETER_V1_3 ;
typedef  TYPE_3__ GET_EVV_VOLTAGE_INFO_OUTPUT_PARAMETER_V1_3 ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_GET_VOLTAGE_EVV_VOLTAGE ; 
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetVoltageInfo ; 
 int amdgpu_atom_execute_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

int atomctrl_get_voltage_evv_on_sclk_ai(struct pp_hwmgr *hwmgr, uint8_t voltage_type,
				uint32_t sclk, uint16_t virtual_voltage_Id, uint32_t *voltage)
{
	struct amdgpu_device *adev = hwmgr->adev;
	int result;
	GET_VOLTAGE_INFO_INPUT_PARAMETER_V1_3 get_voltage_info_param_space;

	get_voltage_info_param_space.ucVoltageType = voltage_type;
	get_voltage_info_param_space.ucVoltageMode = ATOM_GET_VOLTAGE_EVV_VOLTAGE;
	get_voltage_info_param_space.usVoltageLevel = cpu_to_le16(virtual_voltage_Id);
	get_voltage_info_param_space.ulSCLKFreq = cpu_to_le32(sclk);

	result = amdgpu_atom_execute_table(adev->mode_info.atom_context,
			GetIndexIntoMasterTable(COMMAND, GetVoltageInfo),
			(uint32_t *)&get_voltage_info_param_space);

	*voltage = result ? 0 :
		le32_to_cpu(((GET_EVV_VOLTAGE_INFO_OUTPUT_PARAMETER_V1_3 *)(&get_voltage_info_param_space))->ulVoltageLevel);

	return result;
}