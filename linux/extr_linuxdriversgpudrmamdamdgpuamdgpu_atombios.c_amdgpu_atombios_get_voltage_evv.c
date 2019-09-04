#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  usVoltageLevel; } ;
struct TYPE_9__ {int /*<<< orphan*/  ulSCLKFreq; int /*<<< orphan*/  usVoltageLevel; int /*<<< orphan*/  ucVoltageMode; int /*<<< orphan*/  ucVoltageType; } ;
union get_voltage_info {TYPE_8__ evv_out; TYPE_1__ in; } ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_15__ {int /*<<< orphan*/  atom_context; } ;
struct TYPE_11__ {size_t count; TYPE_2__* entries; } ;
struct TYPE_12__ {TYPE_3__ vddc_dependency_on_sclk; } ;
struct TYPE_13__ {TYPE_4__ dyn_state; } ;
struct TYPE_14__ {TYPE_5__ dpm; } ;
struct amdgpu_device {TYPE_7__ mode_info; TYPE_6__ pm; } ;
struct TYPE_10__ {scalar_t__ v; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_GET_VOLTAGE_EVV_VOLTAGE ; 
 int /*<<< orphan*/  COMMAND ; 
 int EINVAL ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetVoltageInfo ; 
 int /*<<< orphan*/  VOLTAGE_TYPE_VDDC ; 
 int /*<<< orphan*/  amdgpu_atom_execute_table (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

int amdgpu_atombios_get_voltage_evv(struct amdgpu_device *adev,
				    u16 virtual_voltage_id,
				    u16 *voltage)
{
	int index = GetIndexIntoMasterTable(COMMAND, GetVoltageInfo);
	u32 entry_id;
	u32 count = adev->pm.dpm.dyn_state.vddc_dependency_on_sclk.count;
	union get_voltage_info args;

	for (entry_id = 0; entry_id < count; entry_id++) {
		if (adev->pm.dpm.dyn_state.vddc_dependency_on_sclk.entries[entry_id].v ==
		    virtual_voltage_id)
			break;
	}

	if (entry_id >= count)
		return -EINVAL;

	args.in.ucVoltageType = VOLTAGE_TYPE_VDDC;
	args.in.ucVoltageMode = ATOM_GET_VOLTAGE_EVV_VOLTAGE;
	args.in.usVoltageLevel = cpu_to_le16(virtual_voltage_id);
	args.in.ulSCLKFreq =
		cpu_to_le32(adev->pm.dpm.dyn_state.vddc_dependency_on_sclk.entries[entry_id].clk);

	amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uint32_t *)&args);

	*voltage = le16_to_cpu(args.evv_out.usVoltageLevel);

	return 0;
}