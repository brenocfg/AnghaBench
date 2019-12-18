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
struct rv7xx_power_info {int bsp; int pbsp; } ;
struct radeon_ps {int dummy; } ;
struct radeon_device {int dummy; } ;
struct ni_ps {int performance_level_count; TYPE_1__* performance_levels; } ;
struct evergreen_power_info {scalar_t__ smu_uvd_hs; scalar_t__ uvd_enabled; } ;
struct TYPE_7__ {TYPE_2__* levels; } ;
struct TYPE_6__ {void* aT; } ;
struct TYPE_5__ {int /*<<< orphan*/  sclk; } ;
typedef  TYPE_3__ NISLANDS_SMC_SWSTATE ;

/* Variables and functions */
 int CG_L (int) ; 
 int CG_R (int) ; 
 int CG_R_MASK ; 
 int EINVAL ; 
 int R600_AH_DFLT ; 
 int be32_to_cpu (void*) ; 
 void* cpu_to_be32 (int) ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 struct ni_ps* ni_get_ps (struct radeon_ps*) ; 
 int r600_calculate_at (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 

__attribute__((used)) static int ni_populate_smc_t(struct radeon_device *rdev,
			     struct radeon_ps *radeon_state,
			     NISLANDS_SMC_SWSTATE *smc_state)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	struct ni_ps *state = ni_get_ps(radeon_state);
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
		if (eg_pi->uvd_enabled)
			ret = r600_calculate_at(
				1000 * (i * (eg_pi->smu_uvd_hs ? 2 : 8) + 2),
				100 * R600_AH_DFLT,
				state->performance_levels[i + 1].sclk,
				state->performance_levels[i].sclk,
				&t_l,
				&t_h);
		else
			ret = r600_calculate_at(
				1000 * (i + 1),
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