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
struct rv7xx_ps {TYPE_3__ low; TYPE_2__ medium; TYPE_1__ high; } ;
struct radeon_ps {int dummy; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MC_ARB_DRAM_TIMING ; 
 int /*<<< orphan*/  MC_ARB_DRAM_TIMING2 ; 
 int /*<<< orphan*/  MC_ARB_DRAM_TIMING2_1 ; 
 int /*<<< orphan*/  MC_ARB_DRAM_TIMING2_2 ; 
 int /*<<< orphan*/  MC_ARB_DRAM_TIMING2_3 ; 
 int /*<<< orphan*/  MC_ARB_DRAM_TIMING_1 ; 
 int /*<<< orphan*/  MC_ARB_DRAM_TIMING_2 ; 
 int /*<<< orphan*/  MC_ARB_DRAM_TIMING_3 ; 
 int /*<<< orphan*/  MC_ARB_RFSH_RATE ; 
 int POWERMODE1 (int /*<<< orphan*/ ) ; 
 int POWERMODE1_MASK ; 
 int POWERMODE2 (int /*<<< orphan*/ ) ; 
 int POWERMODE2_MASK ; 
 int POWERMODE3 (int /*<<< orphan*/ ) ; 
 int POWERMODE3_MASK ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_atom_set_engine_dram_timings (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rv770_calculate_memory_refresh_rate (struct radeon_device*,int /*<<< orphan*/ ) ; 
 struct rv7xx_ps* rv770_get_ps (struct radeon_ps*) ; 

void rv730_program_memory_timing_parameters(struct radeon_device *rdev,
					    struct radeon_ps *radeon_state)
{
	struct rv7xx_ps *state = rv770_get_ps(radeon_state);
	u32 arb_refresh_rate = 0;
	u32 dram_timing = 0;
	u32 dram_timing2 = 0;
	u32 old_dram_timing = 0;
	u32 old_dram_timing2 = 0;

	arb_refresh_rate = RREG32(MC_ARB_RFSH_RATE) &
		~(POWERMODE1_MASK | POWERMODE2_MASK | POWERMODE3_MASK);
	arb_refresh_rate |=
		(POWERMODE1(rv770_calculate_memory_refresh_rate(rdev, state->low.sclk)) |
		 POWERMODE2(rv770_calculate_memory_refresh_rate(rdev, state->medium.sclk)) |
		 POWERMODE3(rv770_calculate_memory_refresh_rate(rdev, state->high.sclk)));
	WREG32(MC_ARB_RFSH_RATE, arb_refresh_rate);

	/* save the boot dram timings */
	old_dram_timing = RREG32(MC_ARB_DRAM_TIMING);
	old_dram_timing2 = RREG32(MC_ARB_DRAM_TIMING2);

	radeon_atom_set_engine_dram_timings(rdev,
					    state->high.sclk,
					    state->high.mclk);

	dram_timing = RREG32(MC_ARB_DRAM_TIMING);
	dram_timing2 = RREG32(MC_ARB_DRAM_TIMING2);

	WREG32(MC_ARB_DRAM_TIMING_3, dram_timing);
	WREG32(MC_ARB_DRAM_TIMING2_3, dram_timing2);

	radeon_atom_set_engine_dram_timings(rdev,
					    state->medium.sclk,
					    state->medium.mclk);

	dram_timing = RREG32(MC_ARB_DRAM_TIMING);
	dram_timing2 = RREG32(MC_ARB_DRAM_TIMING2);

	WREG32(MC_ARB_DRAM_TIMING_2, dram_timing);
	WREG32(MC_ARB_DRAM_TIMING2_2, dram_timing2);

	radeon_atom_set_engine_dram_timings(rdev,
					    state->low.sclk,
					    state->low.mclk);

	dram_timing = RREG32(MC_ARB_DRAM_TIMING);
	dram_timing2 = RREG32(MC_ARB_DRAM_TIMING2);

	WREG32(MC_ARB_DRAM_TIMING_1, dram_timing);
	WREG32(MC_ARB_DRAM_TIMING2_1, dram_timing2);

	/* restore the boot dram timings */
	WREG32(MC_ARB_DRAM_TIMING, old_dram_timing);
	WREG32(MC_ARB_DRAM_TIMING2, old_dram_timing2);

}