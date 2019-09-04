#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int* sclks; } ;
struct rv6xx_power_info {TYPE_1__ hw; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARB_RFSH_RATE ; 
 int POWERMODE0 (int /*<<< orphan*/ ) ; 
 int POWERMODE1 (int /*<<< orphan*/ ) ; 
 int POWERMODE2 (int /*<<< orphan*/ ) ; 
 int POWERMODE3 (int /*<<< orphan*/ ) ; 
 size_t R600_POWER_LEVEL_HIGH ; 
 size_t R600_POWER_LEVEL_LOW ; 
 size_t R600_POWER_LEVEL_MEDIUM ; 
 int /*<<< orphan*/  SQM_RATIO ; 
 int STATE0 (int) ; 
 int STATE1 (int) ; 
 int STATE2 (int) ; 
 int STATE3 (int) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  calculate_memory_refresh_rate (struct radeon_device*,int) ; 
 int /*<<< orphan*/  radeon_atom_set_engine_dram_timings (struct radeon_device*,int,int /*<<< orphan*/ ) ; 
 struct rv6xx_power_info* rv6xx_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void rv6xx_program_memory_timing_parameters(struct radeon_device *rdev)
{
	struct rv6xx_power_info *pi = rv6xx_get_pi(rdev);
	u32 sqm_ratio;
	u32 arb_refresh_rate;
	u32 high_clock;

	if (pi->hw.sclks[R600_POWER_LEVEL_HIGH] <
	    (pi->hw.sclks[R600_POWER_LEVEL_LOW] * 0xFF / 0x40))
		high_clock = pi->hw.sclks[R600_POWER_LEVEL_HIGH];
	else
		high_clock =
			pi->hw.sclks[R600_POWER_LEVEL_LOW] * 0xFF / 0x40;

	radeon_atom_set_engine_dram_timings(rdev, high_clock, 0);

	sqm_ratio = (STATE0(64 * high_clock / pi->hw.sclks[R600_POWER_LEVEL_LOW]) |
		     STATE1(64 * high_clock / pi->hw.sclks[R600_POWER_LEVEL_MEDIUM]) |
		     STATE2(64 * high_clock / pi->hw.sclks[R600_POWER_LEVEL_HIGH]) |
		     STATE3(64 * high_clock / pi->hw.sclks[R600_POWER_LEVEL_HIGH]));
	WREG32(SQM_RATIO, sqm_ratio);

	arb_refresh_rate =
		(POWERMODE0(calculate_memory_refresh_rate(rdev,
							  pi->hw.sclks[R600_POWER_LEVEL_LOW])) |
		 POWERMODE1(calculate_memory_refresh_rate(rdev,
							  pi->hw.sclks[R600_POWER_LEVEL_MEDIUM])) |
		 POWERMODE2(calculate_memory_refresh_rate(rdev,
							  pi->hw.sclks[R600_POWER_LEVEL_HIGH])) |
		 POWERMODE3(calculate_memory_refresh_rate(rdev,
							  pi->hw.sclks[R600_POWER_LEVEL_HIGH])));
	WREG32(ARB_RFSH_RATE, arb_refresh_rate);
}