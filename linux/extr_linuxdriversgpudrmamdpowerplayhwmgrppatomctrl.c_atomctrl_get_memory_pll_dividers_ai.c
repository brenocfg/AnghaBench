#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct pp_hwmgr {struct amdgpu_device* adev; } ;
struct TYPE_8__ {int /*<<< orphan*/  atom_context; } ;
struct amdgpu_device {TYPE_2__ mode_info; } ;
struct TYPE_10__ {int /*<<< orphan*/  ulPostDiv; int /*<<< orphan*/  ulClock; void* ulMclk_fcw_frac; void* ulMclk_fcw_int; } ;
typedef  TYPE_4__ pp_atomctrl_memory_clock_param_ai ;
struct TYPE_9__ {int /*<<< orphan*/  ucPostDiv; int /*<<< orphan*/  ulClock; } ;
struct TYPE_7__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_11__ {TYPE_3__ ulClock; int /*<<< orphan*/  usMclk_fcw_frac; int /*<<< orphan*/  usMclk_fcw_int; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; TYPE_1__ member_0; } ;
typedef  TYPE_5__ COMPUTE_MEMORY_CLOCK_PARAM_PARAMETERS_V2_3 ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  ComputeMemoryClockParam ; 
 int /*<<< orphan*/  GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int amdgpu_atom_execute_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

int atomctrl_get_memory_pll_dividers_ai(struct pp_hwmgr *hwmgr,
					uint32_t clock_value,
					pp_atomctrl_memory_clock_param_ai *mpll_param)
{
	struct amdgpu_device *adev = hwmgr->adev;
	COMPUTE_MEMORY_CLOCK_PARAM_PARAMETERS_V2_3 mpll_parameters = {{0}, 0, 0};
	int result;

	mpll_parameters.ulClock.ulClock = cpu_to_le32(clock_value);

	result = amdgpu_atom_execute_table(adev->mode_info.atom_context,
			GetIndexIntoMasterTable(COMMAND, ComputeMemoryClockParam),
			(uint32_t *)&mpll_parameters);

	/* VEGAM's mpll takes sometime to finish computing */
	udelay(10);

	if (!result) {
		mpll_param->ulMclk_fcw_int =
			le16_to_cpu(mpll_parameters.usMclk_fcw_int);
		mpll_param->ulMclk_fcw_frac =
			le16_to_cpu(mpll_parameters.usMclk_fcw_frac);
		mpll_param->ulClock =
			le32_to_cpu(mpll_parameters.ulClock.ulClock);
		mpll_param->ulPostDiv = mpll_parameters.ulClock.ucPostDiv;
	}

	return result;
}