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
typedef  void* uint32_t ;
struct pp_hwmgr {struct amdgpu_device* adev; } ;
struct pp_atomfwctrl_clock_dividers_soc15 {int /*<<< orphan*/  ucPll_ss_enable; int /*<<< orphan*/  usPll_ss_slew_frac; void* ulPll_ss_fbsmult; void* ulPll_fb_mult; void* ulDid; void* ulClock; } ;
struct compute_gpu_clock_output_parameter_v1_8 {int /*<<< orphan*/  pll_ss_enable; int /*<<< orphan*/  pll_ss_slew_frac; int /*<<< orphan*/  pll_ss_fbsmult; int /*<<< orphan*/  pll_fb_mult; int /*<<< orphan*/  dfs_did; int /*<<< orphan*/  gpuclock_10khz; } ;
struct compute_gpu_clock_input_parameter_v1_8 {void* gpu_clock_type; void* gpuclock_10khz; } ;
struct TYPE_2__ {int /*<<< orphan*/  atom_context; } ;
struct amdgpu_device {TYPE_1__ mode_info; } ;

/* Variables and functions */
 int EINVAL ; 
 void* GetIndexIntoMasterCmdTable (int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_atom_execute_table (int /*<<< orphan*/ ,void*,void**) ; 
 int /*<<< orphan*/  computegpuclockparam ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

int pp_atomfwctrl_get_gpu_pll_dividers_vega10(struct pp_hwmgr *hwmgr,
		uint32_t clock_type, uint32_t clock_value,
		struct pp_atomfwctrl_clock_dividers_soc15 *dividers)
{
	struct amdgpu_device *adev = hwmgr->adev;
	struct compute_gpu_clock_input_parameter_v1_8 pll_parameters;
	struct compute_gpu_clock_output_parameter_v1_8 *pll_output;
	uint32_t idx;

	pll_parameters.gpuclock_10khz = (uint32_t)clock_value;
	pll_parameters.gpu_clock_type = clock_type;

	idx = GetIndexIntoMasterCmdTable(computegpuclockparam);

	if (amdgpu_atom_execute_table(
		adev->mode_info.atom_context, idx, (uint32_t *)&pll_parameters))
		return -EINVAL;

	pll_output = (struct compute_gpu_clock_output_parameter_v1_8 *)
			&pll_parameters;
	dividers->ulClock = le32_to_cpu(pll_output->gpuclock_10khz);
	dividers->ulDid = le32_to_cpu(pll_output->dfs_did);
	dividers->ulPll_fb_mult = le32_to_cpu(pll_output->pll_fb_mult);
	dividers->ulPll_ss_fbsmult = le32_to_cpu(pll_output->pll_ss_fbsmult);
	dividers->usPll_ss_slew_frac = le16_to_cpu(pll_output->pll_ss_slew_frac);
	dividers->ucPll_ss_enable = pll_output->pll_ss_enable;

	return 0;
}