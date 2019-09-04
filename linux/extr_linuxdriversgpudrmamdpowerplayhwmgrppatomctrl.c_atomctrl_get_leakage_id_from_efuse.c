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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct pp_hwmgr {struct amdgpu_device* adev; } ;
struct TYPE_4__ {int /*<<< orphan*/  atom_context; } ;
struct amdgpu_device {TYPE_1__ mode_info; } ;
struct TYPE_6__ {int /*<<< orphan*/  usVoltageLevel; int /*<<< orphan*/  ucVoltageMode; } ;
struct TYPE_5__ {int /*<<< orphan*/  sASICSetVoltage; } ;
typedef  TYPE_2__ SET_VOLTAGE_PS_ALLOCATION ;
typedef  TYPE_3__ SET_VOLTAGE_PARAMETERS_V1_3 ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_GET_LEAKAGE_ID ; 
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetVoltage ; 
 int amdgpu_atom_execute_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int atomctrl_get_leakage_id_from_efuse(struct pp_hwmgr *hwmgr, uint16_t *virtual_voltage_id)
{
	struct amdgpu_device *adev = hwmgr->adev;
	SET_VOLTAGE_PS_ALLOCATION allocation;
	SET_VOLTAGE_PARAMETERS_V1_3 *voltage_parameters =
			(SET_VOLTAGE_PARAMETERS_V1_3 *)&allocation.sASICSetVoltage;
	int result;

	voltage_parameters->ucVoltageMode = ATOM_GET_LEAKAGE_ID;

	result = amdgpu_atom_execute_table(adev->mode_info.atom_context,
			GetIndexIntoMasterTable(COMMAND, SetVoltage),
			(uint32_t *)voltage_parameters);

	*virtual_voltage_id = voltage_parameters->usVoltageLevel;

	return result;
}