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
typedef  scalar_t__ uint32_t ;
struct pp_hwmgr {struct amdgpu_device* adev; } ;
struct TYPE_7__ {int /*<<< orphan*/  atom_context; } ;
struct amdgpu_device {TYPE_2__ mode_info; } ;
struct TYPE_8__ {scalar_t__ mpll_post_divider; } ;
typedef  TYPE_3__ pp_atomctrl_memory_clock_param ;
struct TYPE_6__ {scalar_t__ ucPostDiv; int /*<<< orphan*/  ulClock; } ;
struct TYPE_9__ {TYPE_1__ ulClock; } ;
typedef  TYPE_4__ COMPUTE_MEMORY_CLOCK_PARAM_PARAMETERS_V2_2 ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  ComputeMemoryClockParam ; 
 int /*<<< orphan*/  GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int amdgpu_atom_execute_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 

int atomctrl_get_memory_pll_dividers_vi(struct pp_hwmgr *hwmgr,
		uint32_t clock_value, pp_atomctrl_memory_clock_param *mpll_param)
{
	struct amdgpu_device *adev = hwmgr->adev;
	COMPUTE_MEMORY_CLOCK_PARAM_PARAMETERS_V2_2 mpll_parameters;
	int result;

	mpll_parameters.ulClock.ulClock = cpu_to_le32(clock_value);

	result = amdgpu_atom_execute_table(adev->mode_info.atom_context,
			GetIndexIntoMasterTable(COMMAND, ComputeMemoryClockParam),
			(uint32_t *)&mpll_parameters);

	if (!result)
		mpll_param->mpll_post_divider =
				(uint32_t)mpll_parameters.ulClock.ucPostDiv;

	return result;
}