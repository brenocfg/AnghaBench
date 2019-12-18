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
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  mclk; int /*<<< orphan*/  sclk; } ;
struct TYPE_5__ {int /*<<< orphan*/  mclk; int /*<<< orphan*/  sclk; } ;
struct TYPE_4__ {int /*<<< orphan*/  mclk; int /*<<< orphan*/  sclk; } ;
struct rv7xx_ps {TYPE_3__ high; TYPE_2__ medium; TYPE_1__ low; } ;
struct radeon_ps {int dummy; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MC_ARB_BURST_TIME ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int STATE1 (int /*<<< orphan*/ ) ; 
 int STATE1_MASK ; 
 int STATE2 (int /*<<< orphan*/ ) ; 
 int STATE2_MASK ; 
 int STATE3 (int /*<<< orphan*/ ) ; 
 int STATE3_MASK ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cypress_calculate_burst_time (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rv730_program_memory_timing_parameters (struct radeon_device*,struct radeon_ps*) ; 
 struct rv7xx_ps* rv770_get_ps (struct radeon_ps*) ; 

void cypress_program_memory_timing_parameters(struct radeon_device *rdev,
					      struct radeon_ps *radeon_new_state)
{
	struct rv7xx_ps *new_state = rv770_get_ps(radeon_new_state);
	u32 mc_arb_burst_time = RREG32(MC_ARB_BURST_TIME);

	mc_arb_burst_time &= ~(STATE1_MASK | STATE2_MASK | STATE3_MASK);

	mc_arb_burst_time |= STATE1(cypress_calculate_burst_time(rdev,
								 new_state->low.sclk,
								 new_state->low.mclk));
	mc_arb_burst_time |= STATE2(cypress_calculate_burst_time(rdev,
								 new_state->medium.sclk,
								 new_state->medium.mclk));
	mc_arb_burst_time |= STATE3(cypress_calculate_burst_time(rdev,
								 new_state->high.sclk,
								 new_state->high.mclk));

	rv730_program_memory_timing_parameters(rdev, radeon_new_state);

	WREG32(MC_ARB_BURST_TIME, mc_arb_burst_time);
}