#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  size_t u32 ;
struct atom_clock_dividers {scalar_t__ post_divider; } ;
struct TYPE_10__ {TYPE_1__* entries; scalar_t__ count; } ;
struct TYPE_11__ {TYPE_2__ acp_clock_voltage_dependency_table; } ;
struct TYPE_12__ {TYPE_3__ dyn_state; } ;
struct TYPE_13__ {TYPE_4__ dpm; } ;
struct amdgpu_device {TYPE_5__ pm; } ;
struct TYPE_15__ {size_t AcpLevelCount; TYPE_6__* AcpLevel; } ;
struct TYPE_14__ {int MinPhases; int /*<<< orphan*/  MinVoltage; int /*<<< orphan*/  Frequency; void* Divider; } ;
struct TYPE_9__ {int /*<<< orphan*/  v; int /*<<< orphan*/  clk; } ;
typedef  TYPE_7__ SMU7_Discrete_DpmTable ;

/* Variables and functions */
 int /*<<< orphan*/  COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK ; 
 int EINVAL ; 
 int amdgpu_atombios_get_clock_dividers (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct atom_clock_dividers*) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ci_populate_smc_acp_level(struct amdgpu_device *adev,
				     SMU7_Discrete_DpmTable *table)
{
	u32 count;
	struct atom_clock_dividers dividers;
	int ret = -EINVAL;

	table->AcpLevelCount = (u8)
		(adev->pm.dpm.dyn_state.acp_clock_voltage_dependency_table.count);

	for (count = 0; count < table->AcpLevelCount; count++) {
		table->AcpLevel[count].Frequency =
			adev->pm.dpm.dyn_state.acp_clock_voltage_dependency_table.entries[count].clk;
		table->AcpLevel[count].MinVoltage =
			adev->pm.dpm.dyn_state.acp_clock_voltage_dependency_table.entries[count].v;
		table->AcpLevel[count].MinPhases = 1;

		ret = amdgpu_atombios_get_clock_dividers(adev,
							 COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK,
							 table->AcpLevel[count].Frequency, false, &dividers);
		if (ret)
			return ret;

		table->AcpLevel[count].Divider = (u8)dividers.post_divider;

		table->AcpLevel[count].Frequency = cpu_to_be32(table->AcpLevel[count].Frequency);
		table->AcpLevel[count].MinVoltage = cpu_to_be16(table->AcpLevel[count].MinVoltage);
	}

	return ret;
}