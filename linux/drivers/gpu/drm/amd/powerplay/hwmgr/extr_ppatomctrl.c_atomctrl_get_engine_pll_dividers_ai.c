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
typedef  int /*<<< orphan*/  uint32_t ;
struct pp_hwmgr {struct amdgpu_device* adev; } ;
struct TYPE_7__ {int /*<<< orphan*/  atom_context; } ;
struct amdgpu_device {TYPE_2__ mode_info; } ;
struct TYPE_8__ {void* usPcc_fcw_slew_frac; void* usSsc_fcw_slew_frac; void* usPcc_fcw_int; void* usSsc_fcw1_int; void* usSsc_fcw1_frac; int /*<<< orphan*/  ucSscEnable; int /*<<< orphan*/  ucSclkPllRange; int /*<<< orphan*/  ucSclkVcoMode; int /*<<< orphan*/  ucSclkPostDiv; void* usSclk_fcw_int; void* usSclk_fcw_frac; } ;
typedef  TYPE_3__ pp_atomctrl_clock_dividers_ai ;
struct TYPE_6__ {int /*<<< orphan*/  ucPostDiv; int /*<<< orphan*/  ulClock; } ;
struct TYPE_9__ {int /*<<< orphan*/  usPcc_fcw_slew_frac; int /*<<< orphan*/  usSsc_fcw_slew_frac; int /*<<< orphan*/  usPcc_fcw_int; int /*<<< orphan*/  usSsc_fcw1_int; int /*<<< orphan*/  usSsc_fcw1_frac; int /*<<< orphan*/  ucSscEnable; int /*<<< orphan*/  ucSclkPllRange; int /*<<< orphan*/  ucSclkVcoMode; int /*<<< orphan*/  ucSclkPostDiv; int /*<<< orphan*/  usSclk_fcw_int; int /*<<< orphan*/  usSclk_fcw_frac; TYPE_1__ ulClock; } ;
typedef  TYPE_4__ COMPUTE_GPU_CLOCK_OUTPUT_PARAMETERS_V1_7 ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  COMPUTE_GPUCLK_INPUT_FLAG_SCLK ; 
 int /*<<< orphan*/  ComputeMemoryEnginePLL ; 
 int /*<<< orphan*/  GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int amdgpu_atom_execute_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 

int atomctrl_get_engine_pll_dividers_ai(struct pp_hwmgr *hwmgr,
		uint32_t clock_value,
		pp_atomctrl_clock_dividers_ai *dividers)
{
	struct amdgpu_device *adev = hwmgr->adev;
	COMPUTE_GPU_CLOCK_OUTPUT_PARAMETERS_V1_7 pll_patameters;
	int result;

	pll_patameters.ulClock.ulClock = cpu_to_le32(clock_value);
	pll_patameters.ulClock.ucPostDiv = COMPUTE_GPUCLK_INPUT_FLAG_SCLK;

	result = amdgpu_atom_execute_table(adev->mode_info.atom_context,
		 GetIndexIntoMasterTable(COMMAND, ComputeMemoryEnginePLL),
		(uint32_t *)&pll_patameters);

	if (0 == result) {
		dividers->usSclk_fcw_frac     = le16_to_cpu(pll_patameters.usSclk_fcw_frac);
		dividers->usSclk_fcw_int      = le16_to_cpu(pll_patameters.usSclk_fcw_int);
		dividers->ucSclkPostDiv       = pll_patameters.ucSclkPostDiv;
		dividers->ucSclkVcoMode       = pll_patameters.ucSclkVcoMode;
		dividers->ucSclkPllRange      = pll_patameters.ucSclkPllRange;
		dividers->ucSscEnable         = pll_patameters.ucSscEnable;
		dividers->usSsc_fcw1_frac     = le16_to_cpu(pll_patameters.usSsc_fcw1_frac);
		dividers->usSsc_fcw1_int      = le16_to_cpu(pll_patameters.usSsc_fcw1_int);
		dividers->usPcc_fcw_int       = le16_to_cpu(pll_patameters.usPcc_fcw_int);
		dividers->usSsc_fcw_slew_frac = le16_to_cpu(pll_patameters.usSsc_fcw_slew_frac);
		dividers->usPcc_fcw_slew_frac = le16_to_cpu(pll_patameters.usPcc_fcw_slew_frac);
	}
	return result;
}