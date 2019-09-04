#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dm_pp_clock_levels_with_voltage {int num_levels; TYPE_2__* data; int /*<<< orphan*/  member_0; } ;
struct dc_context {int dummy; } ;
struct dc {TYPE_1__* dcn_soc; struct dc_context* ctx; } ;
struct TYPE_4__ {double clocks_in_khz; } ;
struct TYPE_3__ {int fabric_and_dram_bandwidth_vmin0p65; double fabric_and_dram_bandwidth_vmid0p72; double number_of_channels; double fabric_and_dram_bandwidth_vnom0p8; double fabric_and_dram_bandwidth_vmax0p9; double dcfclkv_min0p65; double dcfclkv_mid0p72; double dcfclkv_nom0p8; double dcfclkv_max0p9; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  DM_PP_CLOCK_TYPE_DCFCLK ; 
 int /*<<< orphan*/  DM_PP_CLOCK_TYPE_FCLK ; 
 double ddr4_dram_factor_single_Channel ; 
 int dm_pp_get_clock_levels_by_type_with_voltage (struct dc_context*,int /*<<< orphan*/ ,struct dm_pp_clock_levels_with_voltage*) ; 
 int /*<<< orphan*/  kernel_fpu_begin () ; 
 int /*<<< orphan*/  kernel_fpu_end () ; 
 int verify_clock_values (struct dm_pp_clock_levels_with_voltage*) ; 

void dcn_bw_update_from_pplib(struct dc *dc)
{
	struct dc_context *ctx = dc->ctx;
	struct dm_pp_clock_levels_with_voltage fclks = {0}, dcfclks = {0};
	bool res;

	/* TODO: This is not the proper way to obtain fabric_and_dram_bandwidth, should be min(fclk, memclk) */
	res = dm_pp_get_clock_levels_by_type_with_voltage(
			ctx, DM_PP_CLOCK_TYPE_FCLK, &fclks);

	kernel_fpu_begin();

	if (res)
		res = verify_clock_values(&fclks);

	if (res) {
		ASSERT(fclks.num_levels >= 3);
		dc->dcn_soc->fabric_and_dram_bandwidth_vmin0p65 = 32 * (fclks.data[0].clocks_in_khz / 1000.0) / 1000.0;
		dc->dcn_soc->fabric_and_dram_bandwidth_vmid0p72 = dc->dcn_soc->number_of_channels *
				(fclks.data[fclks.num_levels - (fclks.num_levels > 2 ? 3 : 2)].clocks_in_khz / 1000.0)
				* ddr4_dram_factor_single_Channel / 1000.0;
		dc->dcn_soc->fabric_and_dram_bandwidth_vnom0p8 = dc->dcn_soc->number_of_channels *
				(fclks.data[fclks.num_levels - 2].clocks_in_khz / 1000.0)
				* ddr4_dram_factor_single_Channel / 1000.0;
		dc->dcn_soc->fabric_and_dram_bandwidth_vmax0p9 = dc->dcn_soc->number_of_channels *
				(fclks.data[fclks.num_levels - 1].clocks_in_khz / 1000.0)
				* ddr4_dram_factor_single_Channel / 1000.0;
	} else
		BREAK_TO_DEBUGGER();

	kernel_fpu_end();

	res = dm_pp_get_clock_levels_by_type_with_voltage(
			ctx, DM_PP_CLOCK_TYPE_DCFCLK, &dcfclks);

	kernel_fpu_begin();

	if (res)
		res = verify_clock_values(&dcfclks);

	if (res && dcfclks.num_levels >= 3) {
		dc->dcn_soc->dcfclkv_min0p65 = dcfclks.data[0].clocks_in_khz / 1000.0;
		dc->dcn_soc->dcfclkv_mid0p72 = dcfclks.data[dcfclks.num_levels - 3].clocks_in_khz / 1000.0;
		dc->dcn_soc->dcfclkv_nom0p8 = dcfclks.data[dcfclks.num_levels - 2].clocks_in_khz / 1000.0;
		dc->dcn_soc->dcfclkv_max0p9 = dcfclks.data[dcfclks.num_levels - 1].clocks_in_khz / 1000.0;
	} else
		BREAK_TO_DEBUGGER();

	kernel_fpu_end();
}