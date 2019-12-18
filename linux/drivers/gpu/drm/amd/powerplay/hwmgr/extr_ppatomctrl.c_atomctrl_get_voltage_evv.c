#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_9__ {TYPE_2__* vddc_dependency_on_sclk; } ;
struct pp_hwmgr {TYPE_3__ dyn_state; struct amdgpu_device* adev; } ;
struct TYPE_10__ {int /*<<< orphan*/  atom_context; } ;
struct amdgpu_device {TYPE_4__ mode_info; } ;
struct TYPE_12__ {int /*<<< orphan*/  usVoltageLevel; } ;
struct TYPE_11__ {int /*<<< orphan*/  ulSCLKFreq; scalar_t__ usVoltageLevel; int /*<<< orphan*/  ucVoltageMode; int /*<<< orphan*/  ucVoltageType; } ;
struct TYPE_8__ {int count; TYPE_1__* entries; } ;
struct TYPE_7__ {scalar_t__ v; int /*<<< orphan*/  clk; } ;
typedef  TYPE_5__ GET_VOLTAGE_INFO_INPUT_PARAMETER_V1_2 ;
typedef  TYPE_6__ GET_EVV_VOLTAGE_INFO_OUTPUT_PARAMETER_V1_2 ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_GET_VOLTAGE_EVV_VOLTAGE ; 
 int /*<<< orphan*/  COMMAND ; 
 int EINVAL ; 
 int /*<<< orphan*/  GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetVoltageInfo ; 
 int /*<<< orphan*/  VOLTAGE_TYPE_VDDC ; 
 int amdgpu_atom_execute_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

int atomctrl_get_voltage_evv(struct pp_hwmgr *hwmgr,
			     uint16_t virtual_voltage_id,
			     uint16_t *voltage)
{
	struct amdgpu_device *adev = hwmgr->adev;
	GET_VOLTAGE_INFO_INPUT_PARAMETER_V1_2 get_voltage_info_param_space;
	int result;
	int entry_id;

	/* search for leakage voltage ID 0xff01 ~ 0xff08 and sckl */
	for (entry_id = 0; entry_id < hwmgr->dyn_state.vddc_dependency_on_sclk->count; entry_id++) {
		if (hwmgr->dyn_state.vddc_dependency_on_sclk->entries[entry_id].v == virtual_voltage_id) {
			/* found */
			break;
		}
	}

	if (entry_id >= hwmgr->dyn_state.vddc_dependency_on_sclk->count) {
	        pr_debug("Can't find requested voltage id in vddc_dependency_on_sclk table!\n");
	        return -EINVAL;
	}

	get_voltage_info_param_space.ucVoltageType = VOLTAGE_TYPE_VDDC;
	get_voltage_info_param_space.ucVoltageMode = ATOM_GET_VOLTAGE_EVV_VOLTAGE;
	get_voltage_info_param_space.usVoltageLevel = virtual_voltage_id;
	get_voltage_info_param_space.ulSCLKFreq =
		cpu_to_le32(hwmgr->dyn_state.vddc_dependency_on_sclk->entries[entry_id].clk);

	result = amdgpu_atom_execute_table(adev->mode_info.atom_context,
			GetIndexIntoMasterTable(COMMAND, GetVoltageInfo),
			(uint32_t *)&get_voltage_info_param_space);

	if (0 != result)
		return result;

	*voltage = le16_to_cpu(((GET_EVV_VOLTAGE_INFO_OUTPUT_PARAMETER_V1_2 *)
				(&get_voltage_info_param_space))->usVoltageLevel);

	return result;
}