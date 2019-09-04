#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct pp_hwmgr {struct amdgpu_device* adev; } ;
struct TYPE_5__ {int /*<<< orphan*/  atom_context; } ;
struct amdgpu_device {TYPE_1__ mode_info; } ;
struct TYPE_6__ {int ulClockFreq; int /*<<< orphan*/  ulComputeClockFlag; } ;
struct TYPE_7__ {int /*<<< orphan*/  ucMclkDPMState; TYPE_2__ ulClock; } ;
struct TYPE_8__ {TYPE_3__ asDPMMCReg; } ;
typedef  TYPE_4__ DYNAMICE_MEMORY_SETTINGS_PARAMETER_V2_1 ;

/* Variables and functions */
 int /*<<< orphan*/  ADJUST_MC_SETTING_PARAM ; 
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  DynamicMemorySettings ; 
 int /*<<< orphan*/  GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SET_CLOCK_FREQ_MASK ; 
 int amdgpu_atom_execute_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int atomctrl_set_ac_timing_ai(struct pp_hwmgr *hwmgr, uint32_t memory_clock,
			      uint8_t level)
{
	struct amdgpu_device *adev = hwmgr->adev;
	DYNAMICE_MEMORY_SETTINGS_PARAMETER_V2_1 memory_clock_parameters;
	int result;

	memory_clock_parameters.asDPMMCReg.ulClock.ulClockFreq =
		memory_clock & SET_CLOCK_FREQ_MASK;
	memory_clock_parameters.asDPMMCReg.ulClock.ulComputeClockFlag =
		ADJUST_MC_SETTING_PARAM;
	memory_clock_parameters.asDPMMCReg.ucMclkDPMState = level;

	result = amdgpu_atom_execute_table(adev->mode_info.atom_context,
		 GetIndexIntoMasterTable(COMMAND, DynamicMemorySettings),
		(uint32_t *)&memory_clock_parameters);

	return result;
}