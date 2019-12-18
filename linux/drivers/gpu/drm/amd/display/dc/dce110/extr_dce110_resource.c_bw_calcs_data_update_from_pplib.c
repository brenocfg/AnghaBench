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
struct dm_pp_clock_levels {int* clocks_in_khz; int num_levels; int /*<<< orphan*/  member_0; } ;
struct dc {TYPE_1__* bw_vbios; int /*<<< orphan*/  ctx; struct dm_pp_clock_levels sclk_lvls; } ;
struct TYPE_2__ {void* high_yclk; void* mid_yclk; void* low_yclk; void* low_voltage_max_dispclk; void* mid_voltage_max_dispclk; void* high_voltage_max_dispclk; void* low_sclk; void* mid6_sclk; void* mid5_sclk; void* mid4_sclk; void* mid3_sclk; void* mid2_sclk; void* mid1_sclk; void* high_sclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_PP_CLOCK_TYPE_DISPLAY_CLK ; 
 int /*<<< orphan*/  DM_PP_CLOCK_TYPE_ENGINE_CLK ; 
 int /*<<< orphan*/  DM_PP_CLOCK_TYPE_MEMORY_CLK ; 
 int MEMORY_TYPE_MULTIPLIER_CZ ; 
 void* bw_frc_to_fixed (int,int) ; 
 int /*<<< orphan*/  dm_pp_get_clock_levels_by_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dm_pp_clock_levels*) ; 

__attribute__((used)) static void bw_calcs_data_update_from_pplib(struct dc *dc)
{
	struct dm_pp_clock_levels clks = {0};

	/*do system clock*/
	dm_pp_get_clock_levels_by_type(
			dc->ctx,
			DM_PP_CLOCK_TYPE_ENGINE_CLK,
			&clks);
	/* convert all the clock fro kHz to fix point mHz */
	dc->bw_vbios->high_sclk = bw_frc_to_fixed(
			clks.clocks_in_khz[clks.num_levels-1], 1000);
	dc->bw_vbios->mid1_sclk  = bw_frc_to_fixed(
			clks.clocks_in_khz[clks.num_levels/8], 1000);
	dc->bw_vbios->mid2_sclk  = bw_frc_to_fixed(
			clks.clocks_in_khz[clks.num_levels*2/8], 1000);
	dc->bw_vbios->mid3_sclk  = bw_frc_to_fixed(
			clks.clocks_in_khz[clks.num_levels*3/8], 1000);
	dc->bw_vbios->mid4_sclk  = bw_frc_to_fixed(
			clks.clocks_in_khz[clks.num_levels*4/8], 1000);
	dc->bw_vbios->mid5_sclk  = bw_frc_to_fixed(
			clks.clocks_in_khz[clks.num_levels*5/8], 1000);
	dc->bw_vbios->mid6_sclk  = bw_frc_to_fixed(
			clks.clocks_in_khz[clks.num_levels*6/8], 1000);
	dc->bw_vbios->low_sclk  = bw_frc_to_fixed(
			clks.clocks_in_khz[0], 1000);
	dc->sclk_lvls = clks;

	/*do display clock*/
	dm_pp_get_clock_levels_by_type(
			dc->ctx,
			DM_PP_CLOCK_TYPE_DISPLAY_CLK,
			&clks);
	dc->bw_vbios->high_voltage_max_dispclk = bw_frc_to_fixed(
			clks.clocks_in_khz[clks.num_levels-1], 1000);
	dc->bw_vbios->mid_voltage_max_dispclk  = bw_frc_to_fixed(
			clks.clocks_in_khz[clks.num_levels>>1], 1000);
	dc->bw_vbios->low_voltage_max_dispclk  = bw_frc_to_fixed(
			clks.clocks_in_khz[0], 1000);

	/*do memory clock*/
	dm_pp_get_clock_levels_by_type(
			dc->ctx,
			DM_PP_CLOCK_TYPE_MEMORY_CLK,
			&clks);

	dc->bw_vbios->low_yclk = bw_frc_to_fixed(
		clks.clocks_in_khz[0] * MEMORY_TYPE_MULTIPLIER_CZ, 1000);
	dc->bw_vbios->mid_yclk = bw_frc_to_fixed(
		clks.clocks_in_khz[clks.num_levels>>1] * MEMORY_TYPE_MULTIPLIER_CZ,
		1000);
	dc->bw_vbios->high_yclk = bw_frc_to_fixed(
		clks.clocks_in_khz[clks.num_levels-1] * MEMORY_TYPE_MULTIPLIER_CZ,
		1000);
}