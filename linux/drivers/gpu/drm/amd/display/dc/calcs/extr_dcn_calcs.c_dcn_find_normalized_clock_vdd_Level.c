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
struct dc {TYPE_1__* dcn_soc; } ;
typedef  enum dm_pp_clock_type { ____Placeholder_dm_pp_clock_type } dm_pp_clock_type ;
struct TYPE_2__ {int max_dispclk_vmax0p9; int max_dispclk_vnom0p8; int max_dispclk_vmid0p72; int max_dispclk_vmin0p65; int phyclkv_max0p9; int phyclkv_nom0p8; int phyclkv_mid0p72; int phyclkv_min0p65; int max_dppclk_vmax0p9; int max_dppclk_vnom0p8; int max_dppclk_vmid0p72; int max_dppclk_vmin0p65; unsigned int number_of_channels; int fabric_and_dram_bandwidth_vmax0p9; int fabric_and_dram_bandwidth_vnom0p8; int fabric_and_dram_bandwidth_vmid0p72; int fabric_and_dram_bandwidth_vmin0p65; int dcfclkv_max0p9; int dcfclkv_nom0p8; int dcfclkv_mid0p72; int dcfclkv_min0p65; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
#define  DM_PP_CLOCK_TYPE_DCFCLK 132 
#define  DM_PP_CLOCK_TYPE_DISPLAYPHYCLK 131 
#define  DM_PP_CLOCK_TYPE_DISPLAY_CLK 130 
#define  DM_PP_CLOCK_TYPE_DPPCLK 129 
#define  DM_PP_CLOCK_TYPE_MEMORY_CLK 128 
 int dcn_bw_v_max0p9 ; 
 int dcn_bw_v_max0p91 ; 
 int dcn_bw_v_mid0p72 ; 
 int dcn_bw_v_min0p65 ; 
 int dcn_bw_v_nom0p8 ; 
 unsigned int ddr4_dram_factor_single_Channel ; 

__attribute__((used)) static unsigned int dcn_find_normalized_clock_vdd_Level(
	const struct dc *dc,
	enum dm_pp_clock_type clocks_type,
	int clocks_in_khz)
{
	int vdd_level = dcn_bw_v_min0p65;

	if (clocks_in_khz == 0)/*todo some clock not in the considerations*/
		return vdd_level;

	switch (clocks_type) {
	case DM_PP_CLOCK_TYPE_DISPLAY_CLK:
		if (clocks_in_khz > dc->dcn_soc->max_dispclk_vmax0p9*1000) {
			vdd_level = dcn_bw_v_max0p91;
			BREAK_TO_DEBUGGER();
		} else if (clocks_in_khz > dc->dcn_soc->max_dispclk_vnom0p8*1000) {
			vdd_level = dcn_bw_v_max0p9;
		} else if (clocks_in_khz > dc->dcn_soc->max_dispclk_vmid0p72*1000) {
			vdd_level = dcn_bw_v_nom0p8;
		} else if (clocks_in_khz > dc->dcn_soc->max_dispclk_vmin0p65*1000) {
			vdd_level = dcn_bw_v_mid0p72;
		} else
			vdd_level = dcn_bw_v_min0p65;
		break;
	case DM_PP_CLOCK_TYPE_DISPLAYPHYCLK:
		if (clocks_in_khz > dc->dcn_soc->phyclkv_max0p9*1000) {
			vdd_level = dcn_bw_v_max0p91;
			BREAK_TO_DEBUGGER();
		} else if (clocks_in_khz > dc->dcn_soc->phyclkv_nom0p8*1000) {
			vdd_level = dcn_bw_v_max0p9;
		} else if (clocks_in_khz > dc->dcn_soc->phyclkv_mid0p72*1000) {
			vdd_level = dcn_bw_v_nom0p8;
		} else if (clocks_in_khz > dc->dcn_soc->phyclkv_min0p65*1000) {
			vdd_level = dcn_bw_v_mid0p72;
		} else
			vdd_level = dcn_bw_v_min0p65;
		break;

	case DM_PP_CLOCK_TYPE_DPPCLK:
		if (clocks_in_khz > dc->dcn_soc->max_dppclk_vmax0p9*1000) {
			vdd_level = dcn_bw_v_max0p91;
			BREAK_TO_DEBUGGER();
		} else if (clocks_in_khz > dc->dcn_soc->max_dppclk_vnom0p8*1000) {
			vdd_level = dcn_bw_v_max0p9;
		} else if (clocks_in_khz > dc->dcn_soc->max_dppclk_vmid0p72*1000) {
			vdd_level = dcn_bw_v_nom0p8;
		} else if (clocks_in_khz > dc->dcn_soc->max_dppclk_vmin0p65*1000) {
			vdd_level = dcn_bw_v_mid0p72;
		} else
			vdd_level = dcn_bw_v_min0p65;
		break;

	case DM_PP_CLOCK_TYPE_MEMORY_CLK:
		{
			unsigned factor = (ddr4_dram_factor_single_Channel * dc->dcn_soc->number_of_channels);

			if (clocks_in_khz > dc->dcn_soc->fabric_and_dram_bandwidth_vmax0p9*1000000/factor) {
				vdd_level = dcn_bw_v_max0p91;
				BREAK_TO_DEBUGGER();
			} else if (clocks_in_khz > dc->dcn_soc->fabric_and_dram_bandwidth_vnom0p8*1000000/factor) {
				vdd_level = dcn_bw_v_max0p9;
			} else if (clocks_in_khz > dc->dcn_soc->fabric_and_dram_bandwidth_vmid0p72*1000000/factor) {
				vdd_level = dcn_bw_v_nom0p8;
			} else if (clocks_in_khz > dc->dcn_soc->fabric_and_dram_bandwidth_vmin0p65*1000000/factor) {
				vdd_level = dcn_bw_v_mid0p72;
			} else
				vdd_level = dcn_bw_v_min0p65;
		}
		break;

	case DM_PP_CLOCK_TYPE_DCFCLK:
		if (clocks_in_khz > dc->dcn_soc->dcfclkv_max0p9*1000) {
			vdd_level = dcn_bw_v_max0p91;
			BREAK_TO_DEBUGGER();
		} else if (clocks_in_khz > dc->dcn_soc->dcfclkv_nom0p8*1000) {
			vdd_level = dcn_bw_v_max0p9;
		} else if (clocks_in_khz > dc->dcn_soc->dcfclkv_mid0p72*1000) {
			vdd_level = dcn_bw_v_nom0p8;
		} else if (clocks_in_khz > dc->dcn_soc->dcfclkv_min0p65*1000) {
			vdd_level = dcn_bw_v_mid0p72;
		} else
			vdd_level = dcn_bw_v_min0p65;
		break;

	default:
		 break;
	}
	return vdd_level;
}