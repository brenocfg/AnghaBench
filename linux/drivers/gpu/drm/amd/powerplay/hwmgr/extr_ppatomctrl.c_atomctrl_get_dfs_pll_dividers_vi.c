#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct pp_hwmgr {struct amdgpu_device* adev; } ;
struct TYPE_8__ {int /*<<< orphan*/  atom_context; } ;
struct amdgpu_device {TYPE_1__ mode_info; } ;
struct TYPE_10__ {void* ul_fb_div; void* ul_fb_div_frac; } ;
struct TYPE_12__ {int /*<<< orphan*/  uc_pll_cntl_flag; int /*<<< orphan*/  uc_pll_post_div; int /*<<< orphan*/  uc_pll_ref_div; TYPE_3__ ul_fb_div; int /*<<< orphan*/  real_clock; int /*<<< orphan*/  pll_post_divider; } ;
typedef  TYPE_5__ pp_atomctrl_clock_dividers_vi ;
struct TYPE_11__ {int /*<<< orphan*/  usFbDiv; int /*<<< orphan*/  usFbDivFrac; } ;
struct TYPE_9__ {int /*<<< orphan*/  ulClock; int /*<<< orphan*/  ucPostDiv; } ;
struct TYPE_13__ {int /*<<< orphan*/  ucPllCntlFlag; int /*<<< orphan*/  ucPllPostDiv; int /*<<< orphan*/  ucPllRefDiv; TYPE_4__ ulFbDiv; TYPE_2__ ulClock; } ;
typedef  TYPE_6__ COMPUTE_GPU_CLOCK_OUTPUT_PARAMETERS_V1_6 ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK ; 
 int /*<<< orphan*/  ComputeMemoryEnginePLL ; 
 int /*<<< orphan*/  GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int amdgpu_atom_execute_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

int atomctrl_get_dfs_pll_dividers_vi(
		struct pp_hwmgr *hwmgr,
		uint32_t clock_value,
		pp_atomctrl_clock_dividers_vi *dividers)
{
	struct amdgpu_device *adev = hwmgr->adev;
	COMPUTE_GPU_CLOCK_OUTPUT_PARAMETERS_V1_6 pll_patameters;
	int result;

	pll_patameters.ulClock.ulClock = cpu_to_le32(clock_value);
	pll_patameters.ulClock.ucPostDiv =
		COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK;

	result = amdgpu_atom_execute_table(adev->mode_info.atom_context,
		 GetIndexIntoMasterTable(COMMAND, ComputeMemoryEnginePLL),
		(uint32_t *)&pll_patameters);

	if (0 == result) {
		dividers->pll_post_divider =
			pll_patameters.ulClock.ucPostDiv;
		dividers->real_clock =
			le32_to_cpu(pll_patameters.ulClock.ulClock);

		dividers->ul_fb_div.ul_fb_div_frac =
			le16_to_cpu(pll_patameters.ulFbDiv.usFbDivFrac);
		dividers->ul_fb_div.ul_fb_div =
			le16_to_cpu(pll_patameters.ulFbDiv.usFbDiv);

		dividers->uc_pll_ref_div =
			pll_patameters.ucPllRefDiv;
		dividers->uc_pll_post_div =
			pll_patameters.ucPllPostDiv;
		dividers->uc_pll_cntl_flag =
			pll_patameters.ucPllCntlFlag;
	}

	return result;
}