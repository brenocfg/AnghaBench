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
typedef  int /*<<< orphan*/  u32 ;
struct rv7xx_pl {int /*<<< orphan*/  mclk; int /*<<< orphan*/  sclk; } ;
struct radeon_device {int dummy; } ;
struct TYPE_2__ {struct rv7xx_pl* pl; } ;
struct evergreen_power_info {TYPE_1__ ulv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MC_ARB_BURST_TIME ; 
 int /*<<< orphan*/  MC_ARB_RFSH_RATE ; 
 int /*<<< orphan*/  POWERMODE0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POWERMODE0_MASK ; 
 int /*<<< orphan*/  STATE0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATE0_MASK ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cypress_calculate_burst_time (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_atom_set_engine_dram_timings (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rv770_calculate_memory_refresh_rate (struct radeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btc_set_ulv_dram_timing(struct radeon_device *rdev)
{
	u32 val;
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	struct rv7xx_pl *ulv_pl = eg_pi->ulv.pl;

	radeon_atom_set_engine_dram_timings(rdev,
					    ulv_pl->sclk,
					    ulv_pl->mclk);

	val = rv770_calculate_memory_refresh_rate(rdev, ulv_pl->sclk);
	WREG32_P(MC_ARB_RFSH_RATE, POWERMODE0(val), ~POWERMODE0_MASK);

	val = cypress_calculate_burst_time(rdev, ulv_pl->sclk, ulv_pl->mclk);
	WREG32_P(MC_ARB_BURST_TIME, STATE0(val), ~STATE0_MASK);

	return 0;
}