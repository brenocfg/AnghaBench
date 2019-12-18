#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct pp_hwmgr {struct amdgpu_device* adev; } ;
struct TYPE_5__ {int /*<<< orphan*/  atom_context; } ;
struct amdgpu_device {TYPE_2__ mode_info; } ;
struct TYPE_4__ {void* ulClock; } ;
struct TYPE_6__ {TYPE_1__ sReserved; void* ulTargetEngineClock; } ;
typedef  TYPE_3__ SET_ENGINE_CLOCK_PS_ALLOCATION ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND ; 
 int COMPUTE_ENGINE_PLL_PARAM ; 
 int /*<<< orphan*/  DynamicMemorySettings ; 
 int /*<<< orphan*/  GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SET_CLOCK_FREQ_MASK ; 
 int amdgpu_atom_execute_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 void* cpu_to_le32 (int) ; 

int atomctrl_set_engine_dram_timings_rv770(
		struct pp_hwmgr *hwmgr,
		uint32_t engine_clock,
		uint32_t memory_clock)
{
	struct amdgpu_device *adev = hwmgr->adev;

	SET_ENGINE_CLOCK_PS_ALLOCATION engine_clock_parameters;

	/* They are both in 10KHz Units. */
	engine_clock_parameters.ulTargetEngineClock =
		cpu_to_le32((engine_clock & SET_CLOCK_FREQ_MASK) |
			    ((COMPUTE_ENGINE_PLL_PARAM << 24)));

	/* in 10 khz units.*/
	engine_clock_parameters.sReserved.ulClock =
		cpu_to_le32(memory_clock & SET_CLOCK_FREQ_MASK);

	return amdgpu_atom_execute_table(adev->mode_info.atom_context,
			GetIndexIntoMasterTable(COMMAND, DynamicMemorySettings),
			(uint32_t *)&engine_clock_parameters);
}