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
struct hw_asic_id {int vram_width; } ;
struct bw_calcs_vbios {int dram_channel_width_in_bits; int number_of_dram_channels; int number_of_dram_banks; int scatter_gather_enable; int cursor_width; int average_compression_rate; int number_of_request_slots_gmc_reserves_for_dmif_per_channel; void* maximum_blackout_recovery_time; void* blackout_duration; void* down_spread_percentage; void* mcifwrmc_urgent_latency; void* nbp_state_change_latency; void* stutter_self_refresh_entry_latency; void* stutter_self_refresh_exit_latency; void* dmifmc_urgent_latency; void* trc; void* data_return_bus_width; void* high_voltage_max_phyclk; void* mid_voltage_max_phyclk; void* low_voltage_max_phyclk; void* high_voltage_max_dispclk; void* mid_voltage_max_dispclk; void* low_voltage_max_dispclk; void* high_sclk; void* mid6_sclk; void* mid5_sclk; void* mid4_sclk; void* mid3_sclk; void* mid2_sclk; void* mid1_sclk; void* low_sclk; void* low_yclk; void* mid_yclk; void* high_yclk; void* memory_type; int /*<<< orphan*/  member_0; } ;
struct bw_calcs_dceip {int version; int max_average_percent_of_ideal_port_bw_display_can_use_in_normal_system_operation; int max_average_percent_of_ideal_drambw_display_can_use_in_normal_system_operation; int percent_of_ideal_port_bw_received_after_urgent_latency; int large_cursor; int dmif_pipe_en_fbc_chunk_tracker; int cursor_max_outstanding_group_num; int lines_interleaved_into_lb; int chunk_width; int number_of_graphics_pipes; int number_of_underlay_pipes; int display_write_back_supported; int argb_compression_support; int max_dmif_buffer_allocated; int graphics_dmif_size; int underlay_luma_dmif_size; int underlay_chroma_dmif_size; int pre_downscaler_enabled; int underlay_downscale_prefetch_enabled; int graphics_lb_nodownscaling_multi_line_prefetching; int limit_excessive_outstanding_dmif_requests; int scatter_gather_lines_of_pte_prefetching_in_linear_mode; int display_write_back420_luma_mcifwr_buffer_size; int display_write_back420_chroma_mcifwr_buffer_size; int scatter_gather_pte_request_rows_in_tiling_mode; void* mcifwr_all_surfaces_burst_time; void* display_pipe_throughput_factor; void* dispclk_ramping_factor; void* dispclk_per_request; void* request_efficiency; void* linear_mode_line_request_alternation_slice; void* maximum_total_outstanding_pte_requests_allowed_by_saw; void* minimum_outstanding_pte_request_limit; void* peak_pte_request_to_eviction_ratio_limiting_single_display_no_rotation; void* peak_pte_request_to_eviction_ratio_limiting_multiple_displays_or_single_rotated_display; void* underlay_maximum_height_efficient_for_tiling; void* underlay_maximum_width_efficient_for_tiling; void* cursor_dcp_buffer_lines; void* cursor_chunk_width; void* underlay422_lb_size_per_component; void* underlay420_chroma_lb_size_per_component; void* underlay420_luma_lb_size_per_component; void* stutter_and_dram_clock_state_change_gated_before_cursor; void* lb_size_per_component444; void* lb_write_pixels_per_dispclk; void* alpha_vscaler_efficiency; void* graphics_vscaler_efficiency12_bit_per_component; void* graphics_vscaler_efficiency10_bit_per_component; void* graphics_vscaler_efficiency8_bit_per_component; void* graphics_vscaler_efficiency6_bit_per_component; void* underlay_vscaler_efficiency12_bit_per_component; void* underlay_vscaler_efficiency10_bit_per_component; void* underlay_vscaler_efficiency8_bit_per_component; void* underlay_vscaler_efficiency6_bit_per_component; int /*<<< orphan*/  low_power_tiling_mode; void* dmif_request_buffer_size; int /*<<< orphan*/  member_0; } ;
typedef  enum bw_calcs_version { ____Placeholder_bw_calcs_version } bw_calcs_version ;

/* Variables and functions */
#define  BW_CALCS_VERSION_CARRIZO 134 
#define  BW_CALCS_VERSION_POLARIS10 133 
#define  BW_CALCS_VERSION_POLARIS11 132 
#define  BW_CALCS_VERSION_POLARIS12 131 
#define  BW_CALCS_VERSION_STONEY 130 
#define  BW_CALCS_VERSION_VEGA10 129 
#define  BW_CALCS_VERSION_VEGAM 128 
 int bw_calcs_version_from_asic_id (struct hw_asic_id) ; 
 void* bw_def_gddr5 ; 
 void* bw_def_hbm ; 
 void* bw_frc_to_fixed (int,int) ; 
 void* bw_int_to_fixed (int) ; 

void bw_calcs_init(struct bw_calcs_dceip *bw_dceip,
	struct bw_calcs_vbios *bw_vbios,
	struct hw_asic_id asic_id)
{
	struct bw_calcs_dceip dceip = { 0 };
	struct bw_calcs_vbios vbios = { 0 };

	enum bw_calcs_version version = bw_calcs_version_from_asic_id(asic_id);

	dceip.version = version;

	switch (version) {
	case BW_CALCS_VERSION_CARRIZO:
		vbios.memory_type = bw_def_gddr5;
		vbios.dram_channel_width_in_bits = 64;
		vbios.number_of_dram_channels = asic_id.vram_width / vbios.dram_channel_width_in_bits;
		vbios.number_of_dram_banks = 8;
		vbios.high_yclk = bw_int_to_fixed(1600);
		vbios.mid_yclk = bw_int_to_fixed(1600);
		vbios.low_yclk = bw_frc_to_fixed(66666, 100);
		vbios.low_sclk = bw_int_to_fixed(200);
		vbios.mid1_sclk = bw_int_to_fixed(300);
		vbios.mid2_sclk = bw_int_to_fixed(300);
		vbios.mid3_sclk = bw_int_to_fixed(300);
		vbios.mid4_sclk = bw_int_to_fixed(300);
		vbios.mid5_sclk = bw_int_to_fixed(300);
		vbios.mid6_sclk = bw_int_to_fixed(300);
		vbios.high_sclk = bw_frc_to_fixed(62609, 100);
		vbios.low_voltage_max_dispclk = bw_int_to_fixed(352);
		vbios.mid_voltage_max_dispclk = bw_int_to_fixed(467);
		vbios.high_voltage_max_dispclk = bw_int_to_fixed(643);
		vbios.low_voltage_max_phyclk = bw_int_to_fixed(540);
		vbios.mid_voltage_max_phyclk = bw_int_to_fixed(810);
		vbios.high_voltage_max_phyclk = bw_int_to_fixed(810);
		vbios.data_return_bus_width = bw_int_to_fixed(32);
		vbios.trc = bw_int_to_fixed(50);
		vbios.dmifmc_urgent_latency = bw_int_to_fixed(4);
		vbios.stutter_self_refresh_exit_latency = bw_frc_to_fixed(153, 10);
		vbios.stutter_self_refresh_entry_latency = bw_int_to_fixed(0);
		vbios.nbp_state_change_latency = bw_frc_to_fixed(19649, 1000);
		vbios.mcifwrmc_urgent_latency = bw_int_to_fixed(10);
		vbios.scatter_gather_enable = true;
		vbios.down_spread_percentage = bw_frc_to_fixed(5, 10);
		vbios.cursor_width = 32;
		vbios.average_compression_rate = 4;
		vbios.number_of_request_slots_gmc_reserves_for_dmif_per_channel = 256;
		vbios.blackout_duration = bw_int_to_fixed(0); /* us */
		vbios.maximum_blackout_recovery_time = bw_int_to_fixed(0);

		dceip.max_average_percent_of_ideal_port_bw_display_can_use_in_normal_system_operation = 100;
		dceip.max_average_percent_of_ideal_drambw_display_can_use_in_normal_system_operation = 100;
		dceip.percent_of_ideal_port_bw_received_after_urgent_latency = 100;
		dceip.large_cursor = false;
		dceip.dmif_request_buffer_size = bw_int_to_fixed(768);
		dceip.dmif_pipe_en_fbc_chunk_tracker = false;
		dceip.cursor_max_outstanding_group_num = 1;
		dceip.lines_interleaved_into_lb = 2;
		dceip.chunk_width = 256;
		dceip.number_of_graphics_pipes = 3;
		dceip.number_of_underlay_pipes = 1;
		dceip.low_power_tiling_mode = 0;
		dceip.display_write_back_supported = false;
		dceip.argb_compression_support = false;
		dceip.underlay_vscaler_efficiency6_bit_per_component =
			bw_frc_to_fixed(35556, 10000);
		dceip.underlay_vscaler_efficiency8_bit_per_component =
			bw_frc_to_fixed(34286, 10000);
		dceip.underlay_vscaler_efficiency10_bit_per_component =
			bw_frc_to_fixed(32, 10);
		dceip.underlay_vscaler_efficiency12_bit_per_component =
			bw_int_to_fixed(3);
		dceip.graphics_vscaler_efficiency6_bit_per_component =
			bw_frc_to_fixed(35, 10);
		dceip.graphics_vscaler_efficiency8_bit_per_component =
			bw_frc_to_fixed(34286, 10000);
		dceip.graphics_vscaler_efficiency10_bit_per_component =
			bw_frc_to_fixed(32, 10);
		dceip.graphics_vscaler_efficiency12_bit_per_component =
			bw_int_to_fixed(3);
		dceip.alpha_vscaler_efficiency = bw_int_to_fixed(3);
		dceip.max_dmif_buffer_allocated = 2;
		dceip.graphics_dmif_size = 12288;
		dceip.underlay_luma_dmif_size = 19456;
		dceip.underlay_chroma_dmif_size = 23552;
		dceip.pre_downscaler_enabled = true;
		dceip.underlay_downscale_prefetch_enabled = true;
		dceip.lb_write_pixels_per_dispclk = bw_int_to_fixed(1);
		dceip.lb_size_per_component444 = bw_int_to_fixed(82176);
		dceip.graphics_lb_nodownscaling_multi_line_prefetching = false;
		dceip.stutter_and_dram_clock_state_change_gated_before_cursor =
			bw_int_to_fixed(0);
		dceip.underlay420_luma_lb_size_per_component = bw_int_to_fixed(
			82176);
		dceip.underlay420_chroma_lb_size_per_component =
			bw_int_to_fixed(164352);
		dceip.underlay422_lb_size_per_component = bw_int_to_fixed(
			82176);
		dceip.cursor_chunk_width = bw_int_to_fixed(64);
		dceip.cursor_dcp_buffer_lines = bw_int_to_fixed(4);
		dceip.underlay_maximum_width_efficient_for_tiling =
			bw_int_to_fixed(1920);
		dceip.underlay_maximum_height_efficient_for_tiling =
			bw_int_to_fixed(1080);
		dceip.peak_pte_request_to_eviction_ratio_limiting_multiple_displays_or_single_rotated_display =
			bw_frc_to_fixed(3, 10);
		dceip.peak_pte_request_to_eviction_ratio_limiting_single_display_no_rotation =
			bw_int_to_fixed(25);
		dceip.minimum_outstanding_pte_request_limit = bw_int_to_fixed(
			2);
		dceip.maximum_total_outstanding_pte_requests_allowed_by_saw =
			bw_int_to_fixed(128);
		dceip.limit_excessive_outstanding_dmif_requests = true;
		dceip.linear_mode_line_request_alternation_slice =
			bw_int_to_fixed(64);
		dceip.scatter_gather_lines_of_pte_prefetching_in_linear_mode =
			32;
		dceip.display_write_back420_luma_mcifwr_buffer_size = 12288;
		dceip.display_write_back420_chroma_mcifwr_buffer_size = 8192;
		dceip.request_efficiency = bw_frc_to_fixed(8, 10);
		dceip.dispclk_per_request = bw_int_to_fixed(2);
		dceip.dispclk_ramping_factor = bw_frc_to_fixed(105, 100);
		dceip.display_pipe_throughput_factor = bw_frc_to_fixed(105, 100);
		dceip.scatter_gather_pte_request_rows_in_tiling_mode = 2;
		dceip.mcifwr_all_surfaces_burst_time = bw_int_to_fixed(0); /* todo: this is a bug*/
		break;
	case BW_CALCS_VERSION_POLARIS10:
		/* TODO: Treat VEGAM the same as P10 for now
		 * Need to tune the para for VEGAM if needed */
	case BW_CALCS_VERSION_VEGAM:
		vbios.memory_type = bw_def_gddr5;
		vbios.dram_channel_width_in_bits = 32;
		vbios.number_of_dram_channels = asic_id.vram_width / vbios.dram_channel_width_in_bits;
		vbios.number_of_dram_banks = 8;
		vbios.high_yclk = bw_int_to_fixed(6000);
		vbios.mid_yclk = bw_int_to_fixed(3200);
		vbios.low_yclk = bw_int_to_fixed(1000);
		vbios.low_sclk = bw_int_to_fixed(300);
		vbios.mid1_sclk = bw_int_to_fixed(400);
		vbios.mid2_sclk = bw_int_to_fixed(500);
		vbios.mid3_sclk = bw_int_to_fixed(600);
		vbios.mid4_sclk = bw_int_to_fixed(700);
		vbios.mid5_sclk = bw_int_to_fixed(800);
		vbios.mid6_sclk = bw_int_to_fixed(974);
		vbios.high_sclk = bw_int_to_fixed(1154);
		vbios.low_voltage_max_dispclk = bw_int_to_fixed(459);
		vbios.mid_voltage_max_dispclk = bw_int_to_fixed(654);
		vbios.high_voltage_max_dispclk = bw_int_to_fixed(1108);
		vbios.low_voltage_max_phyclk = bw_int_to_fixed(540);
		vbios.mid_voltage_max_phyclk = bw_int_to_fixed(810);
		vbios.high_voltage_max_phyclk = bw_int_to_fixed(810);
		vbios.data_return_bus_width = bw_int_to_fixed(32);
		vbios.trc = bw_int_to_fixed(48);
		vbios.dmifmc_urgent_latency = bw_int_to_fixed(3);
		vbios.stutter_self_refresh_exit_latency = bw_int_to_fixed(5);
		vbios.stutter_self_refresh_entry_latency = bw_int_to_fixed(0);
		vbios.nbp_state_change_latency = bw_int_to_fixed(45);
		vbios.mcifwrmc_urgent_latency = bw_int_to_fixed(10);
		vbios.scatter_gather_enable = true;
		vbios.down_spread_percentage = bw_frc_to_fixed(5, 10);
		vbios.cursor_width = 32;
		vbios.average_compression_rate = 4;
		vbios.number_of_request_slots_gmc_reserves_for_dmif_per_channel = 256;
		vbios.blackout_duration = bw_int_to_fixed(0); /* us */
		vbios.maximum_blackout_recovery_time = bw_int_to_fixed(0);

		dceip.max_average_percent_of_ideal_port_bw_display_can_use_in_normal_system_operation = 100;
		dceip.max_average_percent_of_ideal_drambw_display_can_use_in_normal_system_operation = 100;
		dceip.percent_of_ideal_port_bw_received_after_urgent_latency = 100;
		dceip.large_cursor = false;
		dceip.dmif_request_buffer_size = bw_int_to_fixed(768);
		dceip.dmif_pipe_en_fbc_chunk_tracker = false;
		dceip.cursor_max_outstanding_group_num = 1;
		dceip.lines_interleaved_into_lb = 2;
		dceip.chunk_width = 256;
		dceip.number_of_graphics_pipes = 6;
		dceip.number_of_underlay_pipes = 0;
		dceip.low_power_tiling_mode = 0;
		dceip.display_write_back_supported = false;
		dceip.argb_compression_support = true;
		dceip.underlay_vscaler_efficiency6_bit_per_component =
			bw_frc_to_fixed(35556, 10000);
		dceip.underlay_vscaler_efficiency8_bit_per_component =
			bw_frc_to_fixed(34286, 10000);
		dceip.underlay_vscaler_efficiency10_bit_per_component =
			bw_frc_to_fixed(32, 10);
		dceip.underlay_vscaler_efficiency12_bit_per_component =
			bw_int_to_fixed(3);
		dceip.graphics_vscaler_efficiency6_bit_per_component =
			bw_frc_to_fixed(35, 10);
		dceip.graphics_vscaler_efficiency8_bit_per_component =
			bw_frc_to_fixed(34286, 10000);
		dceip.graphics_vscaler_efficiency10_bit_per_component =
			bw_frc_to_fixed(32, 10);
		dceip.graphics_vscaler_efficiency12_bit_per_component =
			bw_int_to_fixed(3);
		dceip.alpha_vscaler_efficiency = bw_int_to_fixed(3);
		dceip.max_dmif_buffer_allocated = 4;
		dceip.graphics_dmif_size = 12288;
		dceip.underlay_luma_dmif_size = 19456;
		dceip.underlay_chroma_dmif_size = 23552;
		dceip.pre_downscaler_enabled = true;
		dceip.underlay_downscale_prefetch_enabled = true;
		dceip.lb_write_pixels_per_dispclk = bw_int_to_fixed(1);
		dceip.lb_size_per_component444 = bw_int_to_fixed(245952);
		dceip.graphics_lb_nodownscaling_multi_line_prefetching = true;
		dceip.stutter_and_dram_clock_state_change_gated_before_cursor =
			bw_int_to_fixed(1);
		dceip.underlay420_luma_lb_size_per_component = bw_int_to_fixed(
			82176);
		dceip.underlay420_chroma_lb_size_per_component =
			bw_int_to_fixed(164352);
		dceip.underlay422_lb_size_per_component = bw_int_to_fixed(
			82176);
		dceip.cursor_chunk_width = bw_int_to_fixed(64);
		dceip.cursor_dcp_buffer_lines = bw_int_to_fixed(4);
		dceip.underlay_maximum_width_efficient_for_tiling =
			bw_int_to_fixed(1920);
		dceip.underlay_maximum_height_efficient_for_tiling =
			bw_int_to_fixed(1080);
		dceip.peak_pte_request_to_eviction_ratio_limiting_multiple_displays_or_single_rotated_display =
			bw_frc_to_fixed(3, 10);
		dceip.peak_pte_request_to_eviction_ratio_limiting_single_display_no_rotation =
			bw_int_to_fixed(25);
		dceip.minimum_outstanding_pte_request_limit = bw_int_to_fixed(
			2);
		dceip.maximum_total_outstanding_pte_requests_allowed_by_saw =
			bw_int_to_fixed(128);
		dceip.limit_excessive_outstanding_dmif_requests = true;
		dceip.linear_mode_line_request_alternation_slice =
			bw_int_to_fixed(64);
		dceip.scatter_gather_lines_of_pte_prefetching_in_linear_mode =
			32;
		dceip.display_write_back420_luma_mcifwr_buffer_size = 12288;
		dceip.display_write_back420_chroma_mcifwr_buffer_size = 8192;
		dceip.request_efficiency = bw_frc_to_fixed(8, 10);
		dceip.dispclk_per_request = bw_int_to_fixed(2);
		dceip.dispclk_ramping_factor = bw_frc_to_fixed(105, 100);
		dceip.display_pipe_throughput_factor = bw_frc_to_fixed(105, 100);
		dceip.scatter_gather_pte_request_rows_in_tiling_mode = 2;
		dceip.mcifwr_all_surfaces_burst_time = bw_int_to_fixed(0);
		break;
	case BW_CALCS_VERSION_POLARIS11:
		vbios.memory_type = bw_def_gddr5;
		vbios.dram_channel_width_in_bits = 32;
		vbios.number_of_dram_channels = asic_id.vram_width / vbios.dram_channel_width_in_bits;
		vbios.number_of_dram_banks = 8;
		vbios.high_yclk = bw_int_to_fixed(6000);
		vbios.mid_yclk = bw_int_to_fixed(3200);
		vbios.low_yclk = bw_int_to_fixed(1000);
		vbios.low_sclk = bw_int_to_fixed(300);
		vbios.mid1_sclk = bw_int_to_fixed(400);
		vbios.mid2_sclk = bw_int_to_fixed(500);
		vbios.mid3_sclk = bw_int_to_fixed(600);
		vbios.mid4_sclk = bw_int_to_fixed(700);
		vbios.mid5_sclk = bw_int_to_fixed(800);
		vbios.mid6_sclk = bw_int_to_fixed(974);
		vbios.high_sclk = bw_int_to_fixed(1154);
		vbios.low_voltage_max_dispclk = bw_int_to_fixed(459);
		vbios.mid_voltage_max_dispclk = bw_int_to_fixed(654);
		vbios.high_voltage_max_dispclk = bw_int_to_fixed(1108);
		vbios.low_voltage_max_phyclk = bw_int_to_fixed(540);
		vbios.mid_voltage_max_phyclk = bw_int_to_fixed(810);
		vbios.high_voltage_max_phyclk = bw_int_to_fixed(810);
		vbios.data_return_bus_width = bw_int_to_fixed(32);
		vbios.trc = bw_int_to_fixed(48);
		if (vbios.number_of_dram_channels == 2) // 64-bit
			vbios.dmifmc_urgent_latency = bw_int_to_fixed(4);
		else
			vbios.dmifmc_urgent_latency = bw_int_to_fixed(3);
		vbios.stutter_self_refresh_exit_latency = bw_int_to_fixed(5);
		vbios.stutter_self_refresh_entry_latency = bw_int_to_fixed(0);
		vbios.nbp_state_change_latency = bw_int_to_fixed(45);
		vbios.mcifwrmc_urgent_latency = bw_int_to_fixed(10);
		vbios.scatter_gather_enable = true;
		vbios.down_spread_percentage = bw_frc_to_fixed(5, 10);
		vbios.cursor_width = 32;
		vbios.average_compression_rate = 4;
		vbios.number_of_request_slots_gmc_reserves_for_dmif_per_channel = 256;
		vbios.blackout_duration = bw_int_to_fixed(0); /* us */
		vbios.maximum_blackout_recovery_time = bw_int_to_fixed(0);

		dceip.max_average_percent_of_ideal_port_bw_display_can_use_in_normal_system_operation = 100;
		dceip.max_average_percent_of_ideal_drambw_display_can_use_in_normal_system_operation = 100;
		dceip.percent_of_ideal_port_bw_received_after_urgent_latency = 100;
		dceip.large_cursor = false;
		dceip.dmif_request_buffer_size = bw_int_to_fixed(768);
		dceip.dmif_pipe_en_fbc_chunk_tracker = false;
		dceip.cursor_max_outstanding_group_num = 1;
		dceip.lines_interleaved_into_lb = 2;
		dceip.chunk_width = 256;
		dceip.number_of_graphics_pipes = 5;
		dceip.number_of_underlay_pipes = 0;
		dceip.low_power_tiling_mode = 0;
		dceip.display_write_back_supported = false;
		dceip.argb_compression_support = true;
		dceip.underlay_vscaler_efficiency6_bit_per_component =
			bw_frc_to_fixed(35556, 10000);
		dceip.underlay_vscaler_efficiency8_bit_per_component =
			bw_frc_to_fixed(34286, 10000);
		dceip.underlay_vscaler_efficiency10_bit_per_component =
			bw_frc_to_fixed(32, 10);
		dceip.underlay_vscaler_efficiency12_bit_per_component =
			bw_int_to_fixed(3);
		dceip.graphics_vscaler_efficiency6_bit_per_component =
			bw_frc_to_fixed(35, 10);
		dceip.graphics_vscaler_efficiency8_bit_per_component =
			bw_frc_to_fixed(34286, 10000);
		dceip.graphics_vscaler_efficiency10_bit_per_component =
			bw_frc_to_fixed(32, 10);
		dceip.graphics_vscaler_efficiency12_bit_per_component =
			bw_int_to_fixed(3);
		dceip.alpha_vscaler_efficiency = bw_int_to_fixed(3);
		dceip.max_dmif_buffer_allocated = 4;
		dceip.graphics_dmif_size = 12288;
		dceip.underlay_luma_dmif_size = 19456;
		dceip.underlay_chroma_dmif_size = 23552;
		dceip.pre_downscaler_enabled = true;
		dceip.underlay_downscale_prefetch_enabled = true;
		dceip.lb_write_pixels_per_dispclk = bw_int_to_fixed(1);
		dceip.lb_size_per_component444 = bw_int_to_fixed(245952);
		dceip.graphics_lb_nodownscaling_multi_line_prefetching = true;
		dceip.stutter_and_dram_clock_state_change_gated_before_cursor =
			bw_int_to_fixed(1);
		dceip.underlay420_luma_lb_size_per_component = bw_int_to_fixed(
			82176);
		dceip.underlay420_chroma_lb_size_per_component =
			bw_int_to_fixed(164352);
		dceip.underlay422_lb_size_per_component = bw_int_to_fixed(
			82176);
		dceip.cursor_chunk_width = bw_int_to_fixed(64);
		dceip.cursor_dcp_buffer_lines = bw_int_to_fixed(4);
		dceip.underlay_maximum_width_efficient_for_tiling =
			bw_int_to_fixed(1920);
		dceip.underlay_maximum_height_efficient_for_tiling =
			bw_int_to_fixed(1080);
		dceip.peak_pte_request_to_eviction_ratio_limiting_multiple_displays_or_single_rotated_display =
			bw_frc_to_fixed(3, 10);
		dceip.peak_pte_request_to_eviction_ratio_limiting_single_display_no_rotation =
			bw_int_to_fixed(25);
		dceip.minimum_outstanding_pte_request_limit = bw_int_to_fixed(
			2);
		dceip.maximum_total_outstanding_pte_requests_allowed_by_saw =
			bw_int_to_fixed(128);
		dceip.limit_excessive_outstanding_dmif_requests = true;
		dceip.linear_mode_line_request_alternation_slice =
			bw_int_to_fixed(64);
		dceip.scatter_gather_lines_of_pte_prefetching_in_linear_mode =
			32;
		dceip.display_write_back420_luma_mcifwr_buffer_size = 12288;
		dceip.display_write_back420_chroma_mcifwr_buffer_size = 8192;
		dceip.request_efficiency = bw_frc_to_fixed(8, 10);
		dceip.dispclk_per_request = bw_int_to_fixed(2);
		dceip.dispclk_ramping_factor = bw_frc_to_fixed(105, 100);
		dceip.display_pipe_throughput_factor = bw_frc_to_fixed(105, 100);
		dceip.scatter_gather_pte_request_rows_in_tiling_mode = 2;
		dceip.mcifwr_all_surfaces_burst_time = bw_int_to_fixed(0);
		break;
	case BW_CALCS_VERSION_POLARIS12:
		vbios.memory_type = bw_def_gddr5;
		vbios.dram_channel_width_in_bits = 32;
		vbios.number_of_dram_channels = asic_id.vram_width / vbios.dram_channel_width_in_bits;
		vbios.number_of_dram_banks = 8;
		vbios.high_yclk = bw_int_to_fixed(6000);
		vbios.mid_yclk = bw_int_to_fixed(3200);
		vbios.low_yclk = bw_int_to_fixed(1000);
		vbios.low_sclk = bw_int_to_fixed(678);
		vbios.mid1_sclk = bw_int_to_fixed(864);
		vbios.mid2_sclk = bw_int_to_fixed(900);
		vbios.mid3_sclk = bw_int_to_fixed(920);
		vbios.mid4_sclk = bw_int_to_fixed(940);
		vbios.mid5_sclk = bw_int_to_fixed(960);
		vbios.mid6_sclk = bw_int_to_fixed(980);
		vbios.high_sclk = bw_int_to_fixed(1049);
		vbios.low_voltage_max_dispclk = bw_int_to_fixed(459);
		vbios.mid_voltage_max_dispclk = bw_int_to_fixed(654);
		vbios.high_voltage_max_dispclk = bw_int_to_fixed(1108);
		vbios.low_voltage_max_phyclk = bw_int_to_fixed(540);
		vbios.mid_voltage_max_phyclk = bw_int_to_fixed(810);
		vbios.high_voltage_max_phyclk = bw_int_to_fixed(810);
		vbios.data_return_bus_width = bw_int_to_fixed(32);
		vbios.trc = bw_int_to_fixed(48);
		if (vbios.number_of_dram_channels == 2) // 64-bit
			vbios.dmifmc_urgent_latency = bw_int_to_fixed(4);
		else
			vbios.dmifmc_urgent_latency = bw_int_to_fixed(3);
		vbios.stutter_self_refresh_exit_latency = bw_int_to_fixed(5);
		vbios.stutter_self_refresh_entry_latency = bw_int_to_fixed(0);
		vbios.nbp_state_change_latency = bw_int_to_fixed(250);
		vbios.mcifwrmc_urgent_latency = bw_int_to_fixed(10);
		vbios.scatter_gather_enable = false;
		vbios.down_spread_percentage = bw_frc_to_fixed(5, 10);
		vbios.cursor_width = 32;
		vbios.average_compression_rate = 4;
		vbios.number_of_request_slots_gmc_reserves_for_dmif_per_channel = 256;
		vbios.blackout_duration = bw_int_to_fixed(0); /* us */
		vbios.maximum_blackout_recovery_time = bw_int_to_fixed(0);

		dceip.max_average_percent_of_ideal_port_bw_display_can_use_in_normal_system_operation = 100;
		dceip.max_average_percent_of_ideal_drambw_display_can_use_in_normal_system_operation = 100;
		dceip.percent_of_ideal_port_bw_received_after_urgent_latency = 100;
		dceip.large_cursor = false;
		dceip.dmif_request_buffer_size = bw_int_to_fixed(768);
		dceip.dmif_pipe_en_fbc_chunk_tracker = false;
		dceip.cursor_max_outstanding_group_num = 1;
		dceip.lines_interleaved_into_lb = 2;
		dceip.chunk_width = 256;
		dceip.number_of_graphics_pipes = 5;
		dceip.number_of_underlay_pipes = 0;
		dceip.low_power_tiling_mode = 0;
		dceip.display_write_back_supported = true;
		dceip.argb_compression_support = true;
		dceip.underlay_vscaler_efficiency6_bit_per_component =
			bw_frc_to_fixed(35556, 10000);
		dceip.underlay_vscaler_efficiency8_bit_per_component =
			bw_frc_to_fixed(34286, 10000);
		dceip.underlay_vscaler_efficiency10_bit_per_component =
			bw_frc_to_fixed(32, 10);
		dceip.underlay_vscaler_efficiency12_bit_per_component =
			bw_int_to_fixed(3);
		dceip.graphics_vscaler_efficiency6_bit_per_component =
			bw_frc_to_fixed(35, 10);
		dceip.graphics_vscaler_efficiency8_bit_per_component =
			bw_frc_to_fixed(34286, 10000);
		dceip.graphics_vscaler_efficiency10_bit_per_component =
			bw_frc_to_fixed(32, 10);
		dceip.graphics_vscaler_efficiency12_bit_per_component =
			bw_int_to_fixed(3);
		dceip.alpha_vscaler_efficiency = bw_int_to_fixed(3);
		dceip.max_dmif_buffer_allocated = 4;
		dceip.graphics_dmif_size = 12288;
		dceip.underlay_luma_dmif_size = 19456;
		dceip.underlay_chroma_dmif_size = 23552;
		dceip.pre_downscaler_enabled = true;
		dceip.underlay_downscale_prefetch_enabled = true;
		dceip.lb_write_pixels_per_dispclk = bw_int_to_fixed(1);
		dceip.lb_size_per_component444 = bw_int_to_fixed(245952);
		dceip.graphics_lb_nodownscaling_multi_line_prefetching = true;
		dceip.stutter_and_dram_clock_state_change_gated_before_cursor =
			bw_int_to_fixed(1);
		dceip.underlay420_luma_lb_size_per_component = bw_int_to_fixed(
			82176);
		dceip.underlay420_chroma_lb_size_per_component =
			bw_int_to_fixed(164352);
		dceip.underlay422_lb_size_per_component = bw_int_to_fixed(
			82176);
		dceip.cursor_chunk_width = bw_int_to_fixed(64);
		dceip.cursor_dcp_buffer_lines = bw_int_to_fixed(4);
		dceip.underlay_maximum_width_efficient_for_tiling =
			bw_int_to_fixed(1920);
		dceip.underlay_maximum_height_efficient_for_tiling =
			bw_int_to_fixed(1080);
		dceip.peak_pte_request_to_eviction_ratio_limiting_multiple_displays_or_single_rotated_display =
			bw_frc_to_fixed(3, 10);
		dceip.peak_pte_request_to_eviction_ratio_limiting_single_display_no_rotation =
			bw_int_to_fixed(25);
		dceip.minimum_outstanding_pte_request_limit = bw_int_to_fixed(
			2);
		dceip.maximum_total_outstanding_pte_requests_allowed_by_saw =
			bw_int_to_fixed(128);
		dceip.limit_excessive_outstanding_dmif_requests = true;
		dceip.linear_mode_line_request_alternation_slice =
			bw_int_to_fixed(64);
		dceip.scatter_gather_lines_of_pte_prefetching_in_linear_mode =
			32;
		dceip.display_write_back420_luma_mcifwr_buffer_size = 12288;
		dceip.display_write_back420_chroma_mcifwr_buffer_size = 8192;
		dceip.request_efficiency = bw_frc_to_fixed(8, 10);
		dceip.dispclk_per_request = bw_int_to_fixed(2);
		dceip.dispclk_ramping_factor = bw_frc_to_fixed(105, 100);
		dceip.display_pipe_throughput_factor = bw_frc_to_fixed(105, 100);
		dceip.scatter_gather_pte_request_rows_in_tiling_mode = 2;
		dceip.mcifwr_all_surfaces_burst_time = bw_int_to_fixed(0);
		break;
	case BW_CALCS_VERSION_STONEY:
		vbios.memory_type = bw_def_gddr5;
		vbios.dram_channel_width_in_bits = 64;
		vbios.number_of_dram_channels = asic_id.vram_width / vbios.dram_channel_width_in_bits;
		vbios.number_of_dram_banks = 8;
		vbios.high_yclk = bw_int_to_fixed(1866);
		vbios.mid_yclk = bw_int_to_fixed(1866);
		vbios.low_yclk = bw_int_to_fixed(1333);
		vbios.low_sclk = bw_int_to_fixed(200);
		vbios.mid1_sclk = bw_int_to_fixed(600);
		vbios.mid2_sclk = bw_int_to_fixed(600);
		vbios.mid3_sclk = bw_int_to_fixed(600);
		vbios.mid4_sclk = bw_int_to_fixed(600);
		vbios.mid5_sclk = bw_int_to_fixed(600);
		vbios.mid6_sclk = bw_int_to_fixed(600);
		vbios.high_sclk = bw_int_to_fixed(800);
		vbios.low_voltage_max_dispclk = bw_int_to_fixed(352);
		vbios.mid_voltage_max_dispclk = bw_int_to_fixed(467);
		vbios.high_voltage_max_dispclk = bw_int_to_fixed(643);
		vbios.low_voltage_max_phyclk = bw_int_to_fixed(540);
		vbios.mid_voltage_max_phyclk = bw_int_to_fixed(810);
		vbios.high_voltage_max_phyclk = bw_int_to_fixed(810);
		vbios.data_return_bus_width = bw_int_to_fixed(32);
		vbios.trc = bw_int_to_fixed(50);
		vbios.dmifmc_urgent_latency = bw_int_to_fixed(4);
		vbios.stutter_self_refresh_exit_latency = bw_frc_to_fixed(158, 10);
		vbios.stutter_self_refresh_entry_latency = bw_int_to_fixed(0);
		vbios.nbp_state_change_latency = bw_frc_to_fixed(2008, 100);
		vbios.mcifwrmc_urgent_latency = bw_int_to_fixed(10);
		vbios.scatter_gather_enable = true;
		vbios.down_spread_percentage = bw_frc_to_fixed(5, 10);
		vbios.cursor_width = 32;
		vbios.average_compression_rate = 4;
		vbios.number_of_request_slots_gmc_reserves_for_dmif_per_channel = 256;
		vbios.blackout_duration = bw_int_to_fixed(0); /* us */
		vbios.maximum_blackout_recovery_time = bw_int_to_fixed(0);

		dceip.max_average_percent_of_ideal_port_bw_display_can_use_in_normal_system_operation = 100;
		dceip.max_average_percent_of_ideal_drambw_display_can_use_in_normal_system_operation = 100;
		dceip.percent_of_ideal_port_bw_received_after_urgent_latency = 100;
		dceip.large_cursor = false;
		dceip.dmif_request_buffer_size = bw_int_to_fixed(768);
		dceip.dmif_pipe_en_fbc_chunk_tracker = false;
		dceip.cursor_max_outstanding_group_num = 1;
		dceip.lines_interleaved_into_lb = 2;
		dceip.chunk_width = 256;
		dceip.number_of_graphics_pipes = 2;
		dceip.number_of_underlay_pipes = 1;
		dceip.low_power_tiling_mode = 0;
		dceip.display_write_back_supported = false;
		dceip.argb_compression_support = true;
		dceip.underlay_vscaler_efficiency6_bit_per_component =
			bw_frc_to_fixed(35556, 10000);
		dceip.underlay_vscaler_efficiency8_bit_per_component =
			bw_frc_to_fixed(34286, 10000);
		dceip.underlay_vscaler_efficiency10_bit_per_component =
			bw_frc_to_fixed(32, 10);
		dceip.underlay_vscaler_efficiency12_bit_per_component =
			bw_int_to_fixed(3);
		dceip.graphics_vscaler_efficiency6_bit_per_component =
			bw_frc_to_fixed(35, 10);
		dceip.graphics_vscaler_efficiency8_bit_per_component =
			bw_frc_to_fixed(34286, 10000);
		dceip.graphics_vscaler_efficiency10_bit_per_component =
			bw_frc_to_fixed(32, 10);
		dceip.graphics_vscaler_efficiency12_bit_per_component =
			bw_int_to_fixed(3);
		dceip.alpha_vscaler_efficiency = bw_int_to_fixed(3);
		dceip.max_dmif_buffer_allocated = 2;
		dceip.graphics_dmif_size = 12288;
		dceip.underlay_luma_dmif_size = 19456;
		dceip.underlay_chroma_dmif_size = 23552;
		dceip.pre_downscaler_enabled = true;
		dceip.underlay_downscale_prefetch_enabled = true;
		dceip.lb_write_pixels_per_dispclk = bw_int_to_fixed(1);
		dceip.lb_size_per_component444 = bw_int_to_fixed(82176);
		dceip.graphics_lb_nodownscaling_multi_line_prefetching = false;
		dceip.stutter_and_dram_clock_state_change_gated_before_cursor =
			bw_int_to_fixed(0);
		dceip.underlay420_luma_lb_size_per_component = bw_int_to_fixed(
			82176);
		dceip.underlay420_chroma_lb_size_per_component =
			bw_int_to_fixed(164352);
		dceip.underlay422_lb_size_per_component = bw_int_to_fixed(
			82176);
		dceip.cursor_chunk_width = bw_int_to_fixed(64);
		dceip.cursor_dcp_buffer_lines = bw_int_to_fixed(4);
		dceip.underlay_maximum_width_efficient_for_tiling =
			bw_int_to_fixed(1920);
		dceip.underlay_maximum_height_efficient_for_tiling =
			bw_int_to_fixed(1080);
		dceip.peak_pte_request_to_eviction_ratio_limiting_multiple_displays_or_single_rotated_display =
			bw_frc_to_fixed(3, 10);
		dceip.peak_pte_request_to_eviction_ratio_limiting_single_display_no_rotation =
			bw_int_to_fixed(25);
		dceip.minimum_outstanding_pte_request_limit = bw_int_to_fixed(
			2);
		dceip.maximum_total_outstanding_pte_requests_allowed_by_saw =
			bw_int_to_fixed(128);
		dceip.limit_excessive_outstanding_dmif_requests = true;
		dceip.linear_mode_line_request_alternation_slice =
			bw_int_to_fixed(64);
		dceip.scatter_gather_lines_of_pte_prefetching_in_linear_mode =
			32;
		dceip.display_write_back420_luma_mcifwr_buffer_size = 12288;
		dceip.display_write_back420_chroma_mcifwr_buffer_size = 8192;
		dceip.request_efficiency = bw_frc_to_fixed(8, 10);
		dceip.dispclk_per_request = bw_int_to_fixed(2);
		dceip.dispclk_ramping_factor = bw_frc_to_fixed(105, 100);
		dceip.display_pipe_throughput_factor = bw_frc_to_fixed(105, 100);
		dceip.scatter_gather_pte_request_rows_in_tiling_mode = 2;
		dceip.mcifwr_all_surfaces_burst_time = bw_int_to_fixed(0);
		break;
	case BW_CALCS_VERSION_VEGA10:
		vbios.memory_type = bw_def_hbm;
		vbios.dram_channel_width_in_bits = 128;
		vbios.number_of_dram_channels = asic_id.vram_width / vbios.dram_channel_width_in_bits;
		vbios.number_of_dram_banks = 16;
		vbios.high_yclk = bw_int_to_fixed(2400);
		vbios.mid_yclk = bw_int_to_fixed(1700);
		vbios.low_yclk = bw_int_to_fixed(1000);
		vbios.low_sclk = bw_int_to_fixed(300);
		vbios.mid1_sclk = bw_int_to_fixed(350);
		vbios.mid2_sclk = bw_int_to_fixed(400);
		vbios.mid3_sclk = bw_int_to_fixed(500);
		vbios.mid4_sclk = bw_int_to_fixed(600);
		vbios.mid5_sclk = bw_int_to_fixed(700);
		vbios.mid6_sclk = bw_int_to_fixed(760);
		vbios.high_sclk = bw_int_to_fixed(776);
		vbios.low_voltage_max_dispclk = bw_int_to_fixed(460);
		vbios.mid_voltage_max_dispclk = bw_int_to_fixed(670);
		vbios.high_voltage_max_dispclk = bw_int_to_fixed(1133);
		vbios.low_voltage_max_phyclk = bw_int_to_fixed(540);
		vbios.mid_voltage_max_phyclk = bw_int_to_fixed(810);
		vbios.high_voltage_max_phyclk = bw_int_to_fixed(810);
		vbios.data_return_bus_width = bw_int_to_fixed(32);
		vbios.trc = bw_int_to_fixed(48);
		vbios.dmifmc_urgent_latency = bw_int_to_fixed(3);
		vbios.stutter_self_refresh_exit_latency = bw_frc_to_fixed(75, 10);
		vbios.stutter_self_refresh_entry_latency = bw_frc_to_fixed(19, 10);
		vbios.nbp_state_change_latency = bw_int_to_fixed(39);
		vbios.mcifwrmc_urgent_latency = bw_int_to_fixed(10);
		vbios.scatter_gather_enable = false;
		vbios.down_spread_percentage = bw_frc_to_fixed(5, 10);
		vbios.cursor_width = 32;
		vbios.average_compression_rate = 4;
		vbios.number_of_request_slots_gmc_reserves_for_dmif_per_channel = 8;
		vbios.blackout_duration = bw_int_to_fixed(0); /* us */
		vbios.maximum_blackout_recovery_time = bw_int_to_fixed(0);

		dceip.max_average_percent_of_ideal_port_bw_display_can_use_in_normal_system_operation = 100;
		dceip.max_average_percent_of_ideal_drambw_display_can_use_in_normal_system_operation = 100;
		dceip.percent_of_ideal_port_bw_received_after_urgent_latency = 100;
		dceip.large_cursor = false;
		dceip.dmif_request_buffer_size = bw_int_to_fixed(2304);
		dceip.dmif_pipe_en_fbc_chunk_tracker = true;
		dceip.cursor_max_outstanding_group_num = 1;
		dceip.lines_interleaved_into_lb = 2;
		dceip.chunk_width = 256;
		dceip.number_of_graphics_pipes = 6;
		dceip.number_of_underlay_pipes = 0;
		dceip.low_power_tiling_mode = 0;
		dceip.display_write_back_supported = true;
		dceip.argb_compression_support = true;
		dceip.underlay_vscaler_efficiency6_bit_per_component =
			bw_frc_to_fixed(35556, 10000);
		dceip.underlay_vscaler_efficiency8_bit_per_component =
			bw_frc_to_fixed(34286, 10000);
		dceip.underlay_vscaler_efficiency10_bit_per_component =
			bw_frc_to_fixed(32, 10);
		dceip.underlay_vscaler_efficiency12_bit_per_component =
			bw_int_to_fixed(3);
		dceip.graphics_vscaler_efficiency6_bit_per_component =
			bw_frc_to_fixed(35, 10);
		dceip.graphics_vscaler_efficiency8_bit_per_component =
			bw_frc_to_fixed(34286, 10000);
		dceip.graphics_vscaler_efficiency10_bit_per_component =
			bw_frc_to_fixed(32, 10);
		dceip.graphics_vscaler_efficiency12_bit_per_component =
			bw_int_to_fixed(3);
		dceip.alpha_vscaler_efficiency = bw_int_to_fixed(3);
		dceip.max_dmif_buffer_allocated = 4;
		dceip.graphics_dmif_size = 24576;
		dceip.underlay_luma_dmif_size = 19456;
		dceip.underlay_chroma_dmif_size = 23552;
		dceip.pre_downscaler_enabled = true;
		dceip.underlay_downscale_prefetch_enabled = false;
		dceip.lb_write_pixels_per_dispclk = bw_int_to_fixed(1);
		dceip.lb_size_per_component444 = bw_int_to_fixed(245952);
		dceip.graphics_lb_nodownscaling_multi_line_prefetching = true;
		dceip.stutter_and_dram_clock_state_change_gated_before_cursor =
			bw_int_to_fixed(1);
		dceip.underlay420_luma_lb_size_per_component = bw_int_to_fixed(
			82176);
		dceip.underlay420_chroma_lb_size_per_component =
			bw_int_to_fixed(164352);
		dceip.underlay422_lb_size_per_component = bw_int_to_fixed(
			82176);
		dceip.cursor_chunk_width = bw_int_to_fixed(64);
		dceip.cursor_dcp_buffer_lines = bw_int_to_fixed(4);
		dceip.underlay_maximum_width_efficient_for_tiling =
			bw_int_to_fixed(1920);
		dceip.underlay_maximum_height_efficient_for_tiling =
			bw_int_to_fixed(1080);
		dceip.peak_pte_request_to_eviction_ratio_limiting_multiple_displays_or_single_rotated_display =
			bw_frc_to_fixed(3, 10);
		dceip.peak_pte_request_to_eviction_ratio_limiting_single_display_no_rotation =
			bw_int_to_fixed(25);
		dceip.minimum_outstanding_pte_request_limit = bw_int_to_fixed(
			2);
		dceip.maximum_total_outstanding_pte_requests_allowed_by_saw =
			bw_int_to_fixed(128);
		dceip.limit_excessive_outstanding_dmif_requests = true;
		dceip.linear_mode_line_request_alternation_slice =
			bw_int_to_fixed(64);
		dceip.scatter_gather_lines_of_pte_prefetching_in_linear_mode =
			32;
		dceip.display_write_back420_luma_mcifwr_buffer_size = 12288;
		dceip.display_write_back420_chroma_mcifwr_buffer_size = 8192;
		dceip.request_efficiency = bw_frc_to_fixed(8, 10);
		dceip.dispclk_per_request = bw_int_to_fixed(2);
		dceip.dispclk_ramping_factor = bw_frc_to_fixed(105, 100);
		dceip.display_pipe_throughput_factor = bw_frc_to_fixed(105, 100);
		dceip.scatter_gather_pte_request_rows_in_tiling_mode = 2;
		dceip.mcifwr_all_surfaces_burst_time = bw_int_to_fixed(0);
		break;
	default:
		break;
	}
	*bw_dceip = dceip;
	*bw_vbios = vbios;

}