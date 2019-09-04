#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct si_ps {int performance_level_count; int /*<<< orphan*/ * performance_levels; } ;
struct si_power_info {int /*<<< orphan*/  sram_end; scalar_t__ arb_table_start; } ;
struct amdgpu_ps {int dummy; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ SMC_SIslands_MCArbDramTimingRegisterSet ;

/* Variables and functions */
 int /*<<< orphan*/  SMC_SIslands_MCArbDramTimingRegisters ; 
 int amdgpu_si_copy_bytes_to_smc (struct amdgpu_device*,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  data ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct si_power_info* si_get_pi (struct amdgpu_device*) ; 
 struct si_ps* si_get_ps (struct amdgpu_ps*) ; 
 int si_populate_memory_timing_parameters (struct amdgpu_device*,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int si_do_program_memory_timing_parameters(struct amdgpu_device *adev,
						  struct amdgpu_ps *amdgpu_state,
						  unsigned int first_arb_set)
{
	struct si_power_info *si_pi = si_get_pi(adev);
	struct  si_ps *state = si_get_ps(amdgpu_state);
	SMC_SIslands_MCArbDramTimingRegisterSet arb_regs = { 0 };
	int i, ret = 0;

	for (i = 0; i < state->performance_level_count; i++) {
		ret = si_populate_memory_timing_parameters(adev, &state->performance_levels[i], &arb_regs);
		if (ret)
			break;
		ret = amdgpu_si_copy_bytes_to_smc(adev,
						  si_pi->arb_table_start +
						  offsetof(SMC_SIslands_MCArbDramTimingRegisters, data) +
						  sizeof(SMC_SIslands_MCArbDramTimingRegisterSet) * (first_arb_set + i),
						  (u8 *)&arb_regs,
						  sizeof(SMC_SIslands_MCArbDramTimingRegisterSet),
						  si_pi->sram_end);
		if (ret)
			break;
	}

	return ret;
}