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
struct dc_context {int dummy; } ;
struct bw_calcs_vbios {int /*<<< orphan*/  maximum_blackout_recovery_time; int /*<<< orphan*/  blackout_duration; int /*<<< orphan*/  number_of_request_slots_gmc_reserves_for_dmif_per_channel; int /*<<< orphan*/  average_compression_rate; int /*<<< orphan*/  cursor_width; int /*<<< orphan*/  down_spread_percentage; int /*<<< orphan*/  scatter_gather_enable; int /*<<< orphan*/  mcifwrmc_urgent_latency; int /*<<< orphan*/  nbp_state_change_latency; int /*<<< orphan*/  stutter_self_refresh_entry_latency; int /*<<< orphan*/  stutter_self_refresh_exit_latency; int /*<<< orphan*/  dmifmc_urgent_latency; int /*<<< orphan*/  trc; int /*<<< orphan*/  data_return_bus_width; int /*<<< orphan*/  high_voltage_max_phyclk; int /*<<< orphan*/  mid_voltage_max_phyclk; int /*<<< orphan*/  low_voltage_max_phyclk; int /*<<< orphan*/  high_voltage_max_dispclk; int /*<<< orphan*/  mid_voltage_max_dispclk; int /*<<< orphan*/  low_voltage_max_dispclk; int /*<<< orphan*/  high_sclk; int /*<<< orphan*/  mid6_sclk; int /*<<< orphan*/  mid5_sclk; int /*<<< orphan*/  mid4_sclk; int /*<<< orphan*/  mid3_sclk; int /*<<< orphan*/  mid2_sclk; int /*<<< orphan*/  mid1_sclk; int /*<<< orphan*/  low_sclk; int /*<<< orphan*/  high_yclk; int /*<<< orphan*/  mid_yclk; int /*<<< orphan*/  low_yclk; int /*<<< orphan*/  number_of_dram_banks; int /*<<< orphan*/  number_of_dram_channels; int /*<<< orphan*/  dram_channel_width_in_bits; int /*<<< orphan*/  memory_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_LOG_BANDWIDTH_CALCS (char*,...) ; 
 int /*<<< orphan*/  bw_fixed_to_int (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_bw_calcs_vbios(struct dc_context *ctx, const struct bw_calcs_vbios *vbios)
{

	DC_LOG_BANDWIDTH_CALCS("#####################################################################");
	DC_LOG_BANDWIDTH_CALCS("struct bw_calcs_vbios vbios");
	DC_LOG_BANDWIDTH_CALCS("#####################################################################");
	DC_LOG_BANDWIDTH_CALCS("	[enum] bw_defines memory_type: %d", vbios->memory_type);
	DC_LOG_BANDWIDTH_CALCS("	[enum] bw_defines memory_type: %d", vbios->memory_type);
	DC_LOG_BANDWIDTH_CALCS("	[uint32_t] dram_channel_width_in_bits: %d", vbios->dram_channel_width_in_bits);
	DC_LOG_BANDWIDTH_CALCS("	[uint32_t] number_of_dram_channels: %d", vbios->number_of_dram_channels);
	DC_LOG_BANDWIDTH_CALCS("	[uint32_t] number_of_dram_banks: %d", vbios->number_of_dram_banks);
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] low_yclk: %d", bw_fixed_to_int(vbios->low_yclk));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] mid_yclk: %d", bw_fixed_to_int(vbios->mid_yclk));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] high_yclk: %d", bw_fixed_to_int(vbios->high_yclk));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] low_sclk: %d", bw_fixed_to_int(vbios->low_sclk));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] mid1_sclk: %d", bw_fixed_to_int(vbios->mid1_sclk));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] mid2_sclk: %d", bw_fixed_to_int(vbios->mid2_sclk));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] mid3_sclk: %d", bw_fixed_to_int(vbios->mid3_sclk));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] mid4_sclk: %d", bw_fixed_to_int(vbios->mid4_sclk));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] mid5_sclk: %d", bw_fixed_to_int(vbios->mid5_sclk));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] mid6_sclk: %d", bw_fixed_to_int(vbios->mid6_sclk));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] high_sclk: %d", bw_fixed_to_int(vbios->high_sclk));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] low_voltage_max_dispclk: %d",
				bw_fixed_to_int(vbios->low_voltage_max_dispclk));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] mid_voltage_max_dispclk;: %d",
				bw_fixed_to_int(vbios->mid_voltage_max_dispclk));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] high_voltage_max_dispclk;: %d",
				bw_fixed_to_int(vbios->high_voltage_max_dispclk));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] low_voltage_max_phyclk: %d",
				bw_fixed_to_int(vbios->low_voltage_max_phyclk));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] mid_voltage_max_phyclk: %d",
				bw_fixed_to_int(vbios->mid_voltage_max_phyclk));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] high_voltage_max_phyclk: %d",
				bw_fixed_to_int(vbios->high_voltage_max_phyclk));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] data_return_bus_width: %d", bw_fixed_to_int(vbios->data_return_bus_width));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] trc: %d", bw_fixed_to_int(vbios->trc));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] dmifmc_urgent_latency: %d", bw_fixed_to_int(vbios->dmifmc_urgent_latency));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] stutter_self_refresh_exit_latency: %d",
				bw_fixed_to_int(vbios->stutter_self_refresh_exit_latency));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] stutter_self_refresh_entry_latency: %d",
				bw_fixed_to_int(vbios->stutter_self_refresh_entry_latency));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] nbp_state_change_latency: %d",
				bw_fixed_to_int(vbios->nbp_state_change_latency));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] mcifwrmc_urgent_latency: %d",
				bw_fixed_to_int(vbios->mcifwrmc_urgent_latency));
	DC_LOG_BANDWIDTH_CALCS("	[bool] scatter_gather_enable: %d", vbios->scatter_gather_enable);
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] down_spread_percentage: %d",
				bw_fixed_to_int(vbios->down_spread_percentage));
	DC_LOG_BANDWIDTH_CALCS("	[uint32_t] cursor_width: %d", vbios->cursor_width);
	DC_LOG_BANDWIDTH_CALCS("	[uint32_t] average_compression_rate: %d", vbios->average_compression_rate);
	DC_LOG_BANDWIDTH_CALCS("	[uint32_t] number_of_request_slots_gmc_reserves_for_dmif_per_channel: %d",
				vbios->number_of_request_slots_gmc_reserves_for_dmif_per_channel);
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] blackout_duration: %d", bw_fixed_to_int(vbios->blackout_duration));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] maximum_blackout_recovery_time: %d",
				bw_fixed_to_int(vbios->maximum_blackout_recovery_time));


}