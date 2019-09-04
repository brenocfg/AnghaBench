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
struct bw_calcs_dceip {int /*<<< orphan*/  dmif_request_buffer_size; int /*<<< orphan*/  mcifwr_all_surfaces_burst_time; int /*<<< orphan*/  display_pipe_throughput_factor; int /*<<< orphan*/  dispclk_ramping_factor; int /*<<< orphan*/  dispclk_per_request; int /*<<< orphan*/  request_efficiency; int /*<<< orphan*/  linear_mode_line_request_alternation_slice; int /*<<< orphan*/  maximum_total_outstanding_pte_requests_allowed_by_saw; int /*<<< orphan*/  minimum_outstanding_pte_request_limit; int /*<<< orphan*/  peak_pte_request_to_eviction_ratio_limiting_single_display_no_rotation; int /*<<< orphan*/  peak_pte_request_to_eviction_ratio_limiting_multiple_displays_or_single_rotated_display; int /*<<< orphan*/  underlay_maximum_height_efficient_for_tiling; int /*<<< orphan*/  underlay_maximum_width_efficient_for_tiling; int /*<<< orphan*/  cursor_dcp_buffer_lines; int /*<<< orphan*/  cursor_chunk_width; int /*<<< orphan*/  underlay422_lb_size_per_component; int /*<<< orphan*/  underlay420_chroma_lb_size_per_component; int /*<<< orphan*/  underlay420_luma_lb_size_per_component; int /*<<< orphan*/  stutter_and_dram_clock_state_change_gated_before_cursor; int /*<<< orphan*/  lb_size_per_component444; int /*<<< orphan*/  lb_write_pixels_per_dispclk; int /*<<< orphan*/  alpha_vscaler_efficiency; int /*<<< orphan*/  graphics_vscaler_efficiency12_bit_per_component; int /*<<< orphan*/  graphics_vscaler_efficiency10_bit_per_component; int /*<<< orphan*/  graphics_vscaler_efficiency8_bit_per_component; int /*<<< orphan*/  graphics_vscaler_efficiency6_bit_per_component; int /*<<< orphan*/  underlay_vscaler_efficiency12_bit_per_component; int /*<<< orphan*/  underlay_vscaler_efficiency10_bit_per_component; int /*<<< orphan*/  scatter_gather_pte_request_rows_in_tiling_mode; int /*<<< orphan*/  display_write_back420_chroma_mcifwr_buffer_size; int /*<<< orphan*/  display_write_back420_luma_mcifwr_buffer_size; int /*<<< orphan*/  scatter_gather_lines_of_pte_prefetching_in_linear_mode; int /*<<< orphan*/  underlay_chroma_dmif_size; int /*<<< orphan*/  underlay_luma_dmif_size; int /*<<< orphan*/  graphics_dmif_size; int /*<<< orphan*/  max_dmif_buffer_allocated; int /*<<< orphan*/  number_of_underlay_pipes; int /*<<< orphan*/  number_of_graphics_pipes; int /*<<< orphan*/  chunk_width; int /*<<< orphan*/  low_power_tiling_mode; int /*<<< orphan*/  lines_interleaved_into_lb; int /*<<< orphan*/  cursor_max_outstanding_group_num; int /*<<< orphan*/  limit_excessive_outstanding_dmif_requests; int /*<<< orphan*/  graphics_lb_nodownscaling_multi_line_prefetching; int /*<<< orphan*/  underlay_downscale_prefetch_enabled; int /*<<< orphan*/  pre_downscaler_enabled; int /*<<< orphan*/  argb_compression_support; int /*<<< orphan*/  display_write_back_supported; int /*<<< orphan*/  dmif_pipe_en_fbc_chunk_tracker; int /*<<< orphan*/  large_cursor; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_LOG_BANDWIDTH_CALCS (char*,...) ; 
 int /*<<< orphan*/  bw_fixed_to_int (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_bw_calcs_dceip(struct dc_context *ctx, const struct bw_calcs_dceip *dceip)
{

	DC_LOG_BANDWIDTH_CALCS("#####################################################################");
	DC_LOG_BANDWIDTH_CALCS("struct bw_calcs_dceip");
	DC_LOG_BANDWIDTH_CALCS("#####################################################################");
	DC_LOG_BANDWIDTH_CALCS("	[enum]   bw_calcs_version version %d", dceip->version);
	DC_LOG_BANDWIDTH_CALCS("	[bool] large_cursor: %d", dceip->large_cursor);
	DC_LOG_BANDWIDTH_CALCS("	[bool] dmif_pipe_en_fbc_chunk_tracker: %d", dceip->dmif_pipe_en_fbc_chunk_tracker);
	DC_LOG_BANDWIDTH_CALCS("	[bool] display_write_back_supported: %d", dceip->display_write_back_supported);
	DC_LOG_BANDWIDTH_CALCS("	[bool] argb_compression_support: %d", dceip->argb_compression_support);
	DC_LOG_BANDWIDTH_CALCS("	[bool] pre_downscaler_enabled: %d", dceip->pre_downscaler_enabled);
	DC_LOG_BANDWIDTH_CALCS("	[bool] underlay_downscale_prefetch_enabled: %d",
				dceip->underlay_downscale_prefetch_enabled);
	DC_LOG_BANDWIDTH_CALCS("	[bool] graphics_lb_nodownscaling_multi_line_prefetching: %d",
				dceip->graphics_lb_nodownscaling_multi_line_prefetching);
	DC_LOG_BANDWIDTH_CALCS("	[bool] limit_excessive_outstanding_dmif_requests: %d",
				dceip->limit_excessive_outstanding_dmif_requests);
	DC_LOG_BANDWIDTH_CALCS("	[uint32_t] cursor_max_outstanding_group_num: %d",
				dceip->cursor_max_outstanding_group_num);
	DC_LOG_BANDWIDTH_CALCS("	[uint32_t] lines_interleaved_into_lb: %d", dceip->lines_interleaved_into_lb);
	DC_LOG_BANDWIDTH_CALCS("	[uint32_t] low_power_tiling_mode: %d", dceip->low_power_tiling_mode);
	DC_LOG_BANDWIDTH_CALCS("	[uint32_t] chunk_width: %d", dceip->chunk_width);
	DC_LOG_BANDWIDTH_CALCS("	[uint32_t] number_of_graphics_pipes: %d", dceip->number_of_graphics_pipes);
	DC_LOG_BANDWIDTH_CALCS("	[uint32_t] number_of_underlay_pipes: %d", dceip->number_of_underlay_pipes);
	DC_LOG_BANDWIDTH_CALCS("	[uint32_t] max_dmif_buffer_allocated: %d", dceip->max_dmif_buffer_allocated);
	DC_LOG_BANDWIDTH_CALCS("	[uint32_t] graphics_dmif_size: %d", dceip->graphics_dmif_size);
	DC_LOG_BANDWIDTH_CALCS("	[uint32_t] underlay_luma_dmif_size: %d", dceip->underlay_luma_dmif_size);
	DC_LOG_BANDWIDTH_CALCS("	[uint32_t] underlay_chroma_dmif_size: %d", dceip->underlay_chroma_dmif_size);
	DC_LOG_BANDWIDTH_CALCS("	[uint32_t] scatter_gather_lines_of_pte_prefetching_in_linear_mode: %d",
				dceip->scatter_gather_lines_of_pte_prefetching_in_linear_mode);
	DC_LOG_BANDWIDTH_CALCS("	[uint32_t] display_write_back420_luma_mcifwr_buffer_size: %d",
				dceip->display_write_back420_luma_mcifwr_buffer_size);
	DC_LOG_BANDWIDTH_CALCS("	[uint32_t] display_write_back420_chroma_mcifwr_buffer_size: %d",
				dceip->display_write_back420_chroma_mcifwr_buffer_size);
	DC_LOG_BANDWIDTH_CALCS("	[uint32_t] scatter_gather_pte_request_rows_in_tiling_mode: %d",
				dceip->scatter_gather_pte_request_rows_in_tiling_mode);
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] underlay_vscaler_efficiency10_bit_per_component: %d",
				bw_fixed_to_int(dceip->underlay_vscaler_efficiency10_bit_per_component));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] underlay_vscaler_efficiency12_bit_per_component: %d",
				bw_fixed_to_int(dceip->underlay_vscaler_efficiency12_bit_per_component));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] graphics_vscaler_efficiency6_bit_per_component: %d",
				bw_fixed_to_int(dceip->graphics_vscaler_efficiency6_bit_per_component));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] graphics_vscaler_efficiency8_bit_per_component: %d",
				bw_fixed_to_int(dceip->graphics_vscaler_efficiency8_bit_per_component));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] graphics_vscaler_efficiency10_bit_per_component: %d",
				bw_fixed_to_int(dceip->graphics_vscaler_efficiency10_bit_per_component));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] graphics_vscaler_efficiency12_bit_per_component: %d",
				bw_fixed_to_int(dceip->graphics_vscaler_efficiency12_bit_per_component));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] alpha_vscaler_efficiency: %d",
				bw_fixed_to_int(dceip->alpha_vscaler_efficiency));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] lb_write_pixels_per_dispclk: %d",
				bw_fixed_to_int(dceip->lb_write_pixels_per_dispclk));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] lb_size_per_component444: %d",
				bw_fixed_to_int(dceip->lb_size_per_component444));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] stutter_and_dram_clock_state_change_gated_before_cursor: %d",
				bw_fixed_to_int(dceip->stutter_and_dram_clock_state_change_gated_before_cursor));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] underlay420_luma_lb_size_per_component: %d",
				bw_fixed_to_int(dceip->underlay420_luma_lb_size_per_component));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] underlay420_chroma_lb_size_per_component: %d",
				bw_fixed_to_int(dceip->underlay420_chroma_lb_size_per_component));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] underlay422_lb_size_per_component: %d",
				bw_fixed_to_int(dceip->underlay422_lb_size_per_component));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] cursor_chunk_width: %d", bw_fixed_to_int(dceip->cursor_chunk_width));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] cursor_dcp_buffer_lines: %d",
				bw_fixed_to_int(dceip->cursor_dcp_buffer_lines));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] underlay_maximum_width_efficient_for_tiling: %d",
				bw_fixed_to_int(dceip->underlay_maximum_width_efficient_for_tiling));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] underlay_maximum_height_efficient_for_tiling: %d",
				bw_fixed_to_int(dceip->underlay_maximum_height_efficient_for_tiling));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] peak_pte_request_to_eviction_ratio_limiting_multiple_displays_or_single_rotated_display: %d",
				bw_fixed_to_int(dceip->peak_pte_request_to_eviction_ratio_limiting_multiple_displays_or_single_rotated_display));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] peak_pte_request_to_eviction_ratio_limiting_single_display_no_rotation: %d",
				bw_fixed_to_int(dceip->peak_pte_request_to_eviction_ratio_limiting_single_display_no_rotation));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] minimum_outstanding_pte_request_limit: %d",
				bw_fixed_to_int(dceip->minimum_outstanding_pte_request_limit));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] maximum_total_outstanding_pte_requests_allowed_by_saw: %d",
				bw_fixed_to_int(dceip->maximum_total_outstanding_pte_requests_allowed_by_saw));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] linear_mode_line_request_alternation_slice: %d",
				bw_fixed_to_int(dceip->linear_mode_line_request_alternation_slice));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] request_efficiency: %d", bw_fixed_to_int(dceip->request_efficiency));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] dispclk_per_request: %d", bw_fixed_to_int(dceip->dispclk_per_request));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] dispclk_ramping_factor: %d",
				bw_fixed_to_int(dceip->dispclk_ramping_factor));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] display_pipe_throughput_factor: %d",
				bw_fixed_to_int(dceip->display_pipe_throughput_factor));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] mcifwr_all_surfaces_burst_time: %d",
				bw_fixed_to_int(dceip->mcifwr_all_surfaces_burst_time));
	DC_LOG_BANDWIDTH_CALCS("	[bw_fixed] dmif_request_buffer_size: %d",
				bw_fixed_to_int(dceip->dmif_request_buffer_size));


}