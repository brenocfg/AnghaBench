#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
struct dm_pp_clock_levels {int num_levels; int /*<<< orphan*/  clocks_in_khz; } ;
typedef  int /*<<< orphan*/  sclks_in_khz ;
typedef  int /*<<< orphan*/  mclks_in_khz ;
typedef  enum dm_pp_clock_type { ____Placeholder_dm_pp_clock_type } dm_pp_clock_type ;
typedef  int /*<<< orphan*/  disp_clks_in_khz ;

/* Variables and functions */
#define  DM_PP_CLOCK_TYPE_DISPLAY_CLK 130 
#define  DM_PP_CLOCK_TYPE_ENGINE_CLK 129 
#define  DM_PP_CLOCK_TYPE_MEMORY_CLK 128 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void get_default_clock_levels(
		enum dm_pp_clock_type clk_type,
		struct dm_pp_clock_levels *clks)
{
	uint32_t disp_clks_in_khz[6] = {
			300000, 400000, 496560, 626090, 685720, 757900 };
	uint32_t sclks_in_khz[6] = {
			300000, 360000, 423530, 514290, 626090, 720000 };
	uint32_t mclks_in_khz[2] = { 333000, 800000 };

	switch (clk_type) {
	case DM_PP_CLOCK_TYPE_DISPLAY_CLK:
		clks->num_levels = 6;
		memmove(clks->clocks_in_khz, disp_clks_in_khz,
				sizeof(disp_clks_in_khz));
		break;
	case DM_PP_CLOCK_TYPE_ENGINE_CLK:
		clks->num_levels = 6;
		memmove(clks->clocks_in_khz, sclks_in_khz,
				sizeof(sclks_in_khz));
		break;
	case DM_PP_CLOCK_TYPE_MEMORY_CLK:
		clks->num_levels = 2;
		memmove(clks->clocks_in_khz, mclks_in_khz,
				sizeof(mclks_in_khz));
		break;
	default:
		clks->num_levels = 0;
		break;
	}
}