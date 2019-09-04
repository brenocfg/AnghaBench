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
typedef  int u32 ;
struct si_ps {int performance_level_count; TYPE_1__* performance_levels; } ;
struct rv7xx_power_info {int bsp; int pbsp; } ;
struct amdgpu_ps {int dummy; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_7__ {TYPE_2__* levels; } ;
struct TYPE_6__ {void* aT; } ;
struct TYPE_5__ {int /*<<< orphan*/  sclk; } ;
typedef  TYPE_3__ SISLANDS_SMC_SWSTATE ;

/* Variables and functions */
 int CG_L (int) ; 
 int CG_R (int) ; 
 int CG_R_MASK ; 
 int EINVAL ; 
 int R600_AH_DFLT ; 
 int SISLANDS_MAX_HARDWARE_POWERLEVELS ; 
 int be32_to_cpu (void*) ; 
 void* cpu_to_be32 (int) ; 
 int r600_calculate_at (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 struct rv7xx_power_info* rv770_get_pi (struct amdgpu_device*) ; 
 struct si_ps* si_get_ps (struct amdgpu_ps*) ; 

__attribute__((used)) static int si_populate_smc_t(struct amdgpu_device *adev,
			     struct amdgpu_ps *amdgpu_state,
			     SISLANDS_SMC_SWSTATE *smc_state)
{
	struct rv7xx_power_info *pi = rv770_get_pi(adev);
	struct  si_ps *state = si_get_ps(amdgpu_state);
	u32 a_t;
	u32 t_l, t_h;
	u32 high_bsp;
	int i, ret;

	if (state->performance_level_count >= 9)
		return -EINVAL;

	if (state->performance_level_count < 2) {
		a_t = CG_R(0xffff) | CG_L(0);
		smc_state->levels[0].aT = cpu_to_be32(a_t);
		return 0;
	}

	smc_state->levels[0].aT = cpu_to_be32(0);

	for (i = 0; i <= state->performance_level_count - 2; i++) {
		ret = r600_calculate_at(
			(50 / SISLANDS_MAX_HARDWARE_POWERLEVELS) * 100 * (i + 1),
			100 * R600_AH_DFLT,
			state->performance_levels[i + 1].sclk,
			state->performance_levels[i].sclk,
			&t_l,
			&t_h);

		if (ret) {
			t_h = (i + 1) * 1000 - 50 * R600_AH_DFLT;
			t_l = (i + 1) * 1000 + 50 * R600_AH_DFLT;
		}

		a_t = be32_to_cpu(smc_state->levels[i].aT) & ~CG_R_MASK;
		a_t |= CG_R(t_l * pi->bsp / 20000);
		smc_state->levels[i].aT = cpu_to_be32(a_t);

		high_bsp = (i == state->performance_level_count - 2) ?
			pi->pbsp : pi->bsp;
		a_t = CG_R(0xffff) | CG_L(t_h * high_bsp / 20000);
		smc_state->levels[i + 1].aT = cpu_to_be32(a_t);
	}

	return 0;
}