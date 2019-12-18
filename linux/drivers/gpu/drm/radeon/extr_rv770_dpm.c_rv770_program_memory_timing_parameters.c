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
struct TYPE_6__ {int sclk; int /*<<< orphan*/  mclk; } ;
struct TYPE_5__ {int sclk; } ;
struct TYPE_4__ {int sclk; } ;
struct rv7xx_ps {TYPE_3__ high; TYPE_2__ medium; TYPE_1__ low; } ;
struct rv7xx_power_info {int boot_sclk; } ;
struct radeon_ps {int dummy; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MC_ARB_RFSH_RATE ; 
 int /*<<< orphan*/  MC_ARB_SQM_RATIO ; 
 int POWERMODE0 (int /*<<< orphan*/ ) ; 
 int POWERMODE1 (int /*<<< orphan*/ ) ; 
 int POWERMODE2 (int /*<<< orphan*/ ) ; 
 int POWERMODE3 (int /*<<< orphan*/ ) ; 
 int STATE0 (int) ; 
 int STATE1 (int) ; 
 int STATE2 (int) ; 
 int STATE3 (int) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_atom_set_engine_dram_timings (struct radeon_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rv770_calculate_memory_refresh_rate (struct radeon_device*,int) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 
 struct rv7xx_ps* rv770_get_ps (struct radeon_ps*) ; 

__attribute__((used)) static void rv770_program_memory_timing_parameters(struct radeon_device *rdev,
						   struct radeon_ps *radeon_state)
{
	struct rv7xx_ps *state = rv770_get_ps(radeon_state);
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	u32 sqm_ratio;
	u32 arb_refresh_rate;
	u32 high_clock;

	if (state->high.sclk < (state->low.sclk * 0xFF / 0x40))
		high_clock = state->high.sclk;
	else
		high_clock = (state->low.sclk * 0xFF / 0x40);

	radeon_atom_set_engine_dram_timings(rdev, high_clock,
					    state->high.mclk);

	sqm_ratio =
		STATE0(64 * high_clock / pi->boot_sclk) |
		STATE1(64 * high_clock / state->low.sclk) |
		STATE2(64 * high_clock / state->medium.sclk) |
		STATE3(64 * high_clock / state->high.sclk);
	WREG32(MC_ARB_SQM_RATIO, sqm_ratio);

	arb_refresh_rate =
		POWERMODE0(rv770_calculate_memory_refresh_rate(rdev, pi->boot_sclk)) |
		POWERMODE1(rv770_calculate_memory_refresh_rate(rdev, state->low.sclk)) |
		POWERMODE2(rv770_calculate_memory_refresh_rate(rdev, state->medium.sclk)) |
		POWERMODE3(rv770_calculate_memory_refresh_rate(rdev, state->high.sclk));
	WREG32(MC_ARB_RFSH_RATE, arb_refresh_rate);
}