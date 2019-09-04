#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct pp_hwmgr {struct amdgpu_device* adev; } ;
struct TYPE_5__ {int /*<<< orphan*/  atom_context; } ;
struct amdgpu_device {TYPE_1__ mode_info; } ;
struct TYPE_6__ {int /*<<< orphan*/  real_clock; int /*<<< orphan*/  pll_post_divider; } ;
typedef  TYPE_2__ pp_atomctrl_clock_dividers_kong ;
struct TYPE_7__ {int /*<<< orphan*/  ulClock; int /*<<< orphan*/  ucPostDiv; } ;
typedef  TYPE_3__ COMPUTE_MEMORY_ENGINE_PLL_PARAMETERS_V4 ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  ComputeMemoryEnginePLL ; 
 int /*<<< orphan*/  GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int amdgpu_atom_execute_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

int atomctrl_get_engine_pll_dividers_kong(struct pp_hwmgr *hwmgr,
					  uint32_t clock_value,
					  pp_atomctrl_clock_dividers_kong *dividers)
{
	struct amdgpu_device *adev = hwmgr->adev;
	COMPUTE_MEMORY_ENGINE_PLL_PARAMETERS_V4 pll_parameters;
	int result;

	pll_parameters.ulClock = cpu_to_le32(clock_value);

	result = amdgpu_atom_execute_table(adev->mode_info.atom_context,
		 GetIndexIntoMasterTable(COMMAND, ComputeMemoryEnginePLL),
		(uint32_t *)&pll_parameters);

	if (0 == result) {
		dividers->pll_post_divider = pll_parameters.ucPostDiv;
		dividers->real_clock = le32_to_cpu(pll_parameters.ulClock);
	}

	return result;
}