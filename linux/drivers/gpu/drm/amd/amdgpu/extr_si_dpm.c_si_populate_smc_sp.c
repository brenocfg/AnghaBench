#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct si_ps {int performance_level_count; } ;
struct rv7xx_power_info {int /*<<< orphan*/  psp; int /*<<< orphan*/  dsp; } ;
struct amdgpu_ps {int dummy; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_5__ {TYPE_1__* levels; } ;
struct TYPE_4__ {void* bSP; } ;
typedef  TYPE_2__ SISLANDS_SMC_SWSTATE ;

/* Variables and functions */
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct rv7xx_power_info* rv770_get_pi (struct amdgpu_device*) ; 
 struct si_ps* si_get_ps (struct amdgpu_ps*) ; 

__attribute__((used)) static void si_populate_smc_sp(struct amdgpu_device *adev,
			       struct amdgpu_ps *amdgpu_state,
			       SISLANDS_SMC_SWSTATE *smc_state)
{
	struct  si_ps *ps = si_get_ps(amdgpu_state);
	struct rv7xx_power_info *pi = rv770_get_pi(adev);
	int i;

	for (i = 0; i < ps->performance_level_count - 1; i++)
		smc_state->levels[i].bSP = cpu_to_be32(pi->dsp);

	smc_state->levels[ps->performance_level_count - 1].bSP =
		cpu_to_be32(pi->psp);
}