#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int uint32_t ;
struct pp_hwmgr {struct amdgpu_device* adev; } ;
struct atom_get_smu_clock_info_parameters_v3_1 {scalar_t__ dfsdid; int /*<<< orphan*/  command; void* syspll_id; void* clk_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  smu_clock_freq_hz; } ;
struct atom_get_smu_clock_info_output_parameters_v3_1 {TYPE_2__ atom_smu_outputclkfreq; } ;
struct TYPE_3__ {int /*<<< orphan*/  atom_context; } ;
struct amdgpu_device {TYPE_1__ mode_info; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GET_SMU_CLOCK_INFO_V3_1_GET_CLOCK_FREQ ; 
 int GetIndexIntoMasterCmdTable (int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_atom_execute_table (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  getsmuclockinfo ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

int pp_atomfwctrl_get_clk_information_by_clkid(struct pp_hwmgr *hwmgr,
					       uint8_t clk_id, uint8_t syspll_id,
					       uint32_t *frequency)
{
	struct amdgpu_device *adev = hwmgr->adev;
	struct atom_get_smu_clock_info_parameters_v3_1   parameters;
	struct atom_get_smu_clock_info_output_parameters_v3_1 *output;
	uint32_t ix;

	parameters.clk_id = clk_id;
	parameters.syspll_id = syspll_id;
	parameters.command = GET_SMU_CLOCK_INFO_V3_1_GET_CLOCK_FREQ;
	parameters.dfsdid = 0;

	ix = GetIndexIntoMasterCmdTable(getsmuclockinfo);

	if (amdgpu_atom_execute_table(
		adev->mode_info.atom_context, ix, (uint32_t *)&parameters))
		return -EINVAL;

	output = (struct atom_get_smu_clock_info_output_parameters_v3_1 *)&parameters;
	*frequency = le32_to_cpu(output->atom_smu_outputclkfreq.smu_clock_freq_hz) / 10000;

	return 0;
}