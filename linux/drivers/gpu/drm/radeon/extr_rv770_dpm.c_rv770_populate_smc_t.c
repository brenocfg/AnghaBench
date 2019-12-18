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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_9__ {scalar_t__ sclk; } ;
struct TYPE_8__ {scalar_t__ sclk; } ;
struct TYPE_7__ {scalar_t__ sclk; } ;
struct rv7xx_ps {TYPE_3__ high; TYPE_2__ medium; TYPE_1__ low; } ;
struct rv7xx_power_info {int lmp; int rlp; int lhp; int rmp; int bsp; int pbsp; } ;
struct radeon_ps {int dummy; } ;
struct radeon_device {int dummy; } ;
struct TYPE_11__ {TYPE_4__* levels; } ;
struct TYPE_10__ {void* aT; } ;
typedef  TYPE_5__ RV770_SMC_SWSTATE ;

/* Variables and functions */
 int CG_L (int) ; 
 int CG_R (int) ; 
 int R600_AH_DFLT ; 
 int RV770_SMC_PERFORMANCE_LEVELS_PER_SWSTATE ; 
 void* cpu_to_be32 (int) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 
 struct rv7xx_ps* rv770_get_ps (struct radeon_ps*) ; 

int rv770_populate_smc_t(struct radeon_device *rdev,
			 struct radeon_ps *radeon_state,
			 RV770_SMC_SWSTATE *smc_state)
{
	struct rv7xx_ps *state = rv770_get_ps(radeon_state);
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	int i;
	int a_n;
	int a_d;
	u8 l[RV770_SMC_PERFORMANCE_LEVELS_PER_SWSTATE];
	u8 r[RV770_SMC_PERFORMANCE_LEVELS_PER_SWSTATE];
	u32 a_t;

	l[0] = 0;
	r[2] = 100;

	a_n = (int)state->medium.sclk * pi->lmp +
		(int)state->low.sclk * (R600_AH_DFLT - pi->rlp);
	a_d = (int)state->low.sclk * (100 - (int)pi->rlp) +
		(int)state->medium.sclk * pi->lmp;

	l[1] = (u8)(pi->lmp - (int)pi->lmp * a_n / a_d);
	r[0] = (u8)(pi->rlp + (100 - (int)pi->rlp) * a_n / a_d);

	a_n = (int)state->high.sclk * pi->lhp + (int)state->medium.sclk *
		(R600_AH_DFLT - pi->rmp);
	a_d = (int)state->medium.sclk * (100 - (int)pi->rmp) +
		(int)state->high.sclk * pi->lhp;

	l[2] = (u8)(pi->lhp - (int)pi->lhp * a_n / a_d);
	r[1] = (u8)(pi->rmp + (100 - (int)pi->rmp) * a_n / a_d);

	for (i = 0; i < (RV770_SMC_PERFORMANCE_LEVELS_PER_SWSTATE - 1); i++) {
		a_t = CG_R(r[i] * pi->bsp / 200) | CG_L(l[i] * pi->bsp / 200);
		smc_state->levels[i].aT = cpu_to_be32(a_t);
	}

	a_t = CG_R(r[RV770_SMC_PERFORMANCE_LEVELS_PER_SWSTATE - 1] * pi->pbsp / 200) |
		CG_L(l[RV770_SMC_PERFORMANCE_LEVELS_PER_SWSTATE - 1] * pi->pbsp / 200);

	smc_state->levels[RV770_SMC_PERFORMANCE_LEVELS_PER_SWSTATE - 1].aT =
		cpu_to_be32(a_t);

	return 0;
}