#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int rob_buffer_size_kbytes; int det_buffer_size_kbytes; int dpp_output_buffer_pixels; int opp_output_buffer_lines; int pte_enable; int pte_chunk_size_kbytes; int meta_chunk_size_kbytes; int writeback_chunk_size_kbytes; int line_buffer_size_bits; int max_line_buffer_lines; int IsLineBufferBppFixed; int LineBufferFixedBpp; int writeback_luma_buffer_size_kbytes; int writeback_chroma_buffer_size_kbytes; int max_num_dpp; int max_num_wb; int max_dchub_pscl_bw_pix_per_clk; int max_pscl_lb_bw_pix_per_clk; int max_lb_vscl_bw_pix_per_clk; int max_vscl_hscl_bw_pix_per_clk; int max_hscl_ratio; int max_vscl_ratio; int max_hscl_taps; int max_vscl_taps; int underscan_factor; int can_vstartup_lines_exceed_vsync_plus_back_porch_lines_minus_one; int bug_forcing_LC_req_same_size_fixed; int /*<<< orphan*/  dcfclk_cstate_latency; int /*<<< orphan*/  max_inter_dcn_tile_repeaters; int /*<<< orphan*/  dispclk_ramp_margin_percent; int /*<<< orphan*/  pixel_chunk_size_kbytes; } ;
struct TYPE_6__ {int sr_exit_time_us; int sr_enter_plus_exit_time_us; int urgent_latency_us; int writeback_latency_us; int max_request_size_bytes; int downspread_percent; int urgent_out_of_order_return_per_channel_bytes; int vmm_page_size_bytes; int dram_clock_change_latency_us; int /*<<< orphan*/  return_bus_width_bytes; int /*<<< orphan*/  num_chans; int /*<<< orphan*/  round_trip_ping_latency_dcfclk_cycles; int /*<<< orphan*/  ideal_dram_bw_after_urgent_percent; } ;
struct TYPE_9__ {TYPE_3__ ip; TYPE_1__ soc; } ;
struct dc {TYPE_5__* dcn_ip; TYPE_4__ dml; TYPE_2__* dcn_soc; } ;
struct TYPE_10__ {int rob_buffer_size_in_kbyte; int det_buffer_size_in_kbyte; int dpp_output_buffer_pixels; int opp_output_buffer_lines; int pte_enable; int pte_chunk_size; int meta_chunk_size; int writeback_chunk_size; int odm_capability; int dsc_capability; int line_buffer_size; int max_line_buffer_lines; int is_line_buffer_bpp_fixed; int line_buffer_fixed_bpp; int writeback_luma_buffer_size; int writeback_chroma_buffer_size; int max_num_dpp; int max_num_writeback; int max_dchub_topscl_throughput; int max_pscl_tolb_throughput; int max_lb_tovscl_throughput; int max_vscl_tohscl_throughput; int max_hscl_ratio; int max_vscl_ratio; int max_hscl_taps; int max_vscl_taps; int pte_buffer_size_in_requests; int under_scan_factor; int can_vstartup_lines_exceed_vsync_plus_back_porch_lines_minus_one; int bug_forcing_luma_and_chroma_request_to_same_size_fixed; int /*<<< orphan*/  dcfclk_cstate_latency; int /*<<< orphan*/  max_inter_dcn_tile_repeaters; int /*<<< orphan*/  dispclk_ramping_margin; int /*<<< orphan*/  pixel_chunk_size_in_kbyte; } ;
struct TYPE_7__ {int sr_exit_time; int sr_enter_plus_exit_time; int urgent_latency; int write_back_latency; int max_request_size; int dcfclkv_max0p9; int dcfclkv_nom0p8; int dcfclkv_mid0p72; int dcfclkv_min0p65; int max_dispclk_vmax0p9; int max_dispclk_vnom0p8; int max_dispclk_vmid0p72; int max_dispclk_vmin0p65; int max_dppclk_vmax0p9; int max_dppclk_vnom0p8; int max_dppclk_vmid0p72; int max_dppclk_vmin0p65; int socclk; int fabric_and_dram_bandwidth_vmax0p9; int fabric_and_dram_bandwidth_vnom0p8; int fabric_and_dram_bandwidth_vmid0p72; int fabric_and_dram_bandwidth_vmin0p65; int phyclkv_max0p9; int phyclkv_nom0p8; int phyclkv_mid0p72; int phyclkv_min0p65; int downspreading; int urgent_out_of_order_return_per_channel; int vmm_page_size; int dram_clock_change_latency; int /*<<< orphan*/  return_bus_width; int /*<<< orphan*/  number_of_channels; int /*<<< orphan*/  round_trip_ping_latency_cycles; int /*<<< orphan*/  percent_of_ideal_drambw_received_after_urg_latency; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_LOG_BANDWIDTH_CALCS (char*,int,int,int,int,int /*<<< orphan*/ ,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int dcn_bw_yes ; 
 int /*<<< orphan*/  kernel_fpu_begin () ; 
 int /*<<< orphan*/  kernel_fpu_end () ; 

void dcn_bw_sync_calcs_and_dml(struct dc *dc)
{
	kernel_fpu_begin();
	DC_LOG_BANDWIDTH_CALCS("sr_exit_time: %f ns\n"
			"sr_enter_plus_exit_time: %f ns\n"
			"urgent_latency: %f ns\n"
			"write_back_latency: %f ns\n"
			"percent_of_ideal_drambw_received_after_urg_latency: %f %%\n"
			"max_request_size: %d bytes\n"
			"dcfclkv_max0p9: %f kHz\n"
			"dcfclkv_nom0p8: %f kHz\n"
			"dcfclkv_mid0p72: %f kHz\n"
			"dcfclkv_min0p65: %f kHz\n"
			"max_dispclk_vmax0p9: %f kHz\n"
			"max_dispclk_vnom0p8: %f kHz\n"
			"max_dispclk_vmid0p72: %f kHz\n"
			"max_dispclk_vmin0p65: %f kHz\n"
			"max_dppclk_vmax0p9: %f kHz\n"
			"max_dppclk_vnom0p8: %f kHz\n"
			"max_dppclk_vmid0p72: %f kHz\n"
			"max_dppclk_vmin0p65: %f kHz\n"
			"socclk: %f kHz\n"
			"fabric_and_dram_bandwidth_vmax0p9: %f MB/s\n"
			"fabric_and_dram_bandwidth_vnom0p8: %f MB/s\n"
			"fabric_and_dram_bandwidth_vmid0p72: %f MB/s\n"
			"fabric_and_dram_bandwidth_vmin0p65: %f MB/s\n"
			"phyclkv_max0p9: %f kHz\n"
			"phyclkv_nom0p8: %f kHz\n"
			"phyclkv_mid0p72: %f kHz\n"
			"phyclkv_min0p65: %f kHz\n"
			"downspreading: %f %%\n"
			"round_trip_ping_latency_cycles: %d DCFCLK Cycles\n"
			"urgent_out_of_order_return_per_channel: %d Bytes\n"
			"number_of_channels: %d\n"
			"vmm_page_size: %d Bytes\n"
			"dram_clock_change_latency: %f ns\n"
			"return_bus_width: %d Bytes\n",
			dc->dcn_soc->sr_exit_time * 1000,
			dc->dcn_soc->sr_enter_plus_exit_time * 1000,
			dc->dcn_soc->urgent_latency * 1000,
			dc->dcn_soc->write_back_latency * 1000,
			dc->dcn_soc->percent_of_ideal_drambw_received_after_urg_latency,
			dc->dcn_soc->max_request_size,
			dc->dcn_soc->dcfclkv_max0p9 * 1000,
			dc->dcn_soc->dcfclkv_nom0p8 * 1000,
			dc->dcn_soc->dcfclkv_mid0p72 * 1000,
			dc->dcn_soc->dcfclkv_min0p65 * 1000,
			dc->dcn_soc->max_dispclk_vmax0p9 * 1000,
			dc->dcn_soc->max_dispclk_vnom0p8 * 1000,
			dc->dcn_soc->max_dispclk_vmid0p72 * 1000,
			dc->dcn_soc->max_dispclk_vmin0p65 * 1000,
			dc->dcn_soc->max_dppclk_vmax0p9 * 1000,
			dc->dcn_soc->max_dppclk_vnom0p8 * 1000,
			dc->dcn_soc->max_dppclk_vmid0p72 * 1000,
			dc->dcn_soc->max_dppclk_vmin0p65 * 1000,
			dc->dcn_soc->socclk * 1000,
			dc->dcn_soc->fabric_and_dram_bandwidth_vmax0p9 * 1000,
			dc->dcn_soc->fabric_and_dram_bandwidth_vnom0p8 * 1000,
			dc->dcn_soc->fabric_and_dram_bandwidth_vmid0p72 * 1000,
			dc->dcn_soc->fabric_and_dram_bandwidth_vmin0p65 * 1000,
			dc->dcn_soc->phyclkv_max0p9 * 1000,
			dc->dcn_soc->phyclkv_nom0p8 * 1000,
			dc->dcn_soc->phyclkv_mid0p72 * 1000,
			dc->dcn_soc->phyclkv_min0p65 * 1000,
			dc->dcn_soc->downspreading * 100,
			dc->dcn_soc->round_trip_ping_latency_cycles,
			dc->dcn_soc->urgent_out_of_order_return_per_channel,
			dc->dcn_soc->number_of_channels,
			dc->dcn_soc->vmm_page_size,
			dc->dcn_soc->dram_clock_change_latency * 1000,
			dc->dcn_soc->return_bus_width);
	DC_LOG_BANDWIDTH_CALCS("rob_buffer_size_in_kbyte: %f\n"
			"det_buffer_size_in_kbyte: %f\n"
			"dpp_output_buffer_pixels: %f\n"
			"opp_output_buffer_lines: %f\n"
			"pixel_chunk_size_in_kbyte: %f\n"
			"pte_enable: %d\n"
			"pte_chunk_size: %d kbytes\n"
			"meta_chunk_size: %d kbytes\n"
			"writeback_chunk_size: %d kbytes\n"
			"odm_capability: %d\n"
			"dsc_capability: %d\n"
			"line_buffer_size: %d bits\n"
			"max_line_buffer_lines: %d\n"
			"is_line_buffer_bpp_fixed: %d\n"
			"line_buffer_fixed_bpp: %d\n"
			"writeback_luma_buffer_size: %d kbytes\n"
			"writeback_chroma_buffer_size: %d kbytes\n"
			"max_num_dpp: %d\n"
			"max_num_writeback: %d\n"
			"max_dchub_topscl_throughput: %d pixels/dppclk\n"
			"max_pscl_tolb_throughput: %d pixels/dppclk\n"
			"max_lb_tovscl_throughput: %d pixels/dppclk\n"
			"max_vscl_tohscl_throughput: %d pixels/dppclk\n"
			"max_hscl_ratio: %f\n"
			"max_vscl_ratio: %f\n"
			"max_hscl_taps: %d\n"
			"max_vscl_taps: %d\n"
			"pte_buffer_size_in_requests: %d\n"
			"dispclk_ramping_margin: %f %%\n"
			"under_scan_factor: %f %%\n"
			"max_inter_dcn_tile_repeaters: %d\n"
			"can_vstartup_lines_exceed_vsync_plus_back_porch_lines_minus_one: %d\n"
			"bug_forcing_luma_and_chroma_request_to_same_size_fixed: %d\n"
			"dcfclk_cstate_latency: %d\n",
			dc->dcn_ip->rob_buffer_size_in_kbyte,
			dc->dcn_ip->det_buffer_size_in_kbyte,
			dc->dcn_ip->dpp_output_buffer_pixels,
			dc->dcn_ip->opp_output_buffer_lines,
			dc->dcn_ip->pixel_chunk_size_in_kbyte,
			dc->dcn_ip->pte_enable,
			dc->dcn_ip->pte_chunk_size,
			dc->dcn_ip->meta_chunk_size,
			dc->dcn_ip->writeback_chunk_size,
			dc->dcn_ip->odm_capability,
			dc->dcn_ip->dsc_capability,
			dc->dcn_ip->line_buffer_size,
			dc->dcn_ip->max_line_buffer_lines,
			dc->dcn_ip->is_line_buffer_bpp_fixed,
			dc->dcn_ip->line_buffer_fixed_bpp,
			dc->dcn_ip->writeback_luma_buffer_size,
			dc->dcn_ip->writeback_chroma_buffer_size,
			dc->dcn_ip->max_num_dpp,
			dc->dcn_ip->max_num_writeback,
			dc->dcn_ip->max_dchub_topscl_throughput,
			dc->dcn_ip->max_pscl_tolb_throughput,
			dc->dcn_ip->max_lb_tovscl_throughput,
			dc->dcn_ip->max_vscl_tohscl_throughput,
			dc->dcn_ip->max_hscl_ratio,
			dc->dcn_ip->max_vscl_ratio,
			dc->dcn_ip->max_hscl_taps,
			dc->dcn_ip->max_vscl_taps,
			dc->dcn_ip->pte_buffer_size_in_requests,
			dc->dcn_ip->dispclk_ramping_margin,
			dc->dcn_ip->under_scan_factor * 100,
			dc->dcn_ip->max_inter_dcn_tile_repeaters,
			dc->dcn_ip->can_vstartup_lines_exceed_vsync_plus_back_porch_lines_minus_one,
			dc->dcn_ip->bug_forcing_luma_and_chroma_request_to_same_size_fixed,
			dc->dcn_ip->dcfclk_cstate_latency);

	dc->dml.soc.sr_exit_time_us = dc->dcn_soc->sr_exit_time;
	dc->dml.soc.sr_enter_plus_exit_time_us = dc->dcn_soc->sr_enter_plus_exit_time;
	dc->dml.soc.urgent_latency_us = dc->dcn_soc->urgent_latency;
	dc->dml.soc.writeback_latency_us = dc->dcn_soc->write_back_latency;
	dc->dml.soc.ideal_dram_bw_after_urgent_percent =
			dc->dcn_soc->percent_of_ideal_drambw_received_after_urg_latency;
	dc->dml.soc.max_request_size_bytes = dc->dcn_soc->max_request_size;
	dc->dml.soc.downspread_percent = dc->dcn_soc->downspreading;
	dc->dml.soc.round_trip_ping_latency_dcfclk_cycles =
			dc->dcn_soc->round_trip_ping_latency_cycles;
	dc->dml.soc.urgent_out_of_order_return_per_channel_bytes =
			dc->dcn_soc->urgent_out_of_order_return_per_channel;
	dc->dml.soc.num_chans = dc->dcn_soc->number_of_channels;
	dc->dml.soc.vmm_page_size_bytes = dc->dcn_soc->vmm_page_size;
	dc->dml.soc.dram_clock_change_latency_us = dc->dcn_soc->dram_clock_change_latency;
	dc->dml.soc.return_bus_width_bytes = dc->dcn_soc->return_bus_width;

	dc->dml.ip.rob_buffer_size_kbytes = dc->dcn_ip->rob_buffer_size_in_kbyte;
	dc->dml.ip.det_buffer_size_kbytes = dc->dcn_ip->det_buffer_size_in_kbyte;
	dc->dml.ip.dpp_output_buffer_pixels = dc->dcn_ip->dpp_output_buffer_pixels;
	dc->dml.ip.opp_output_buffer_lines = dc->dcn_ip->opp_output_buffer_lines;
	dc->dml.ip.pixel_chunk_size_kbytes = dc->dcn_ip->pixel_chunk_size_in_kbyte;
	dc->dml.ip.pte_enable = dc->dcn_ip->pte_enable == dcn_bw_yes;
	dc->dml.ip.pte_chunk_size_kbytes = dc->dcn_ip->pte_chunk_size;
	dc->dml.ip.meta_chunk_size_kbytes = dc->dcn_ip->meta_chunk_size;
	dc->dml.ip.writeback_chunk_size_kbytes = dc->dcn_ip->writeback_chunk_size;
	dc->dml.ip.line_buffer_size_bits = dc->dcn_ip->line_buffer_size;
	dc->dml.ip.max_line_buffer_lines = dc->dcn_ip->max_line_buffer_lines;
	dc->dml.ip.IsLineBufferBppFixed = dc->dcn_ip->is_line_buffer_bpp_fixed == dcn_bw_yes;
	dc->dml.ip.LineBufferFixedBpp = dc->dcn_ip->line_buffer_fixed_bpp;
	dc->dml.ip.writeback_luma_buffer_size_kbytes = dc->dcn_ip->writeback_luma_buffer_size;
	dc->dml.ip.writeback_chroma_buffer_size_kbytes = dc->dcn_ip->writeback_chroma_buffer_size;
	dc->dml.ip.max_num_dpp = dc->dcn_ip->max_num_dpp;
	dc->dml.ip.max_num_wb = dc->dcn_ip->max_num_writeback;
	dc->dml.ip.max_dchub_pscl_bw_pix_per_clk = dc->dcn_ip->max_dchub_topscl_throughput;
	dc->dml.ip.max_pscl_lb_bw_pix_per_clk = dc->dcn_ip->max_pscl_tolb_throughput;
	dc->dml.ip.max_lb_vscl_bw_pix_per_clk = dc->dcn_ip->max_lb_tovscl_throughput;
	dc->dml.ip.max_vscl_hscl_bw_pix_per_clk = dc->dcn_ip->max_vscl_tohscl_throughput;
	dc->dml.ip.max_hscl_ratio = dc->dcn_ip->max_hscl_ratio;
	dc->dml.ip.max_vscl_ratio = dc->dcn_ip->max_vscl_ratio;
	dc->dml.ip.max_hscl_taps = dc->dcn_ip->max_hscl_taps;
	dc->dml.ip.max_vscl_taps = dc->dcn_ip->max_vscl_taps;
	/*pte_buffer_size_in_requests missing in dml*/
	dc->dml.ip.dispclk_ramp_margin_percent = dc->dcn_ip->dispclk_ramping_margin;
	dc->dml.ip.underscan_factor = dc->dcn_ip->under_scan_factor;
	dc->dml.ip.max_inter_dcn_tile_repeaters = dc->dcn_ip->max_inter_dcn_tile_repeaters;
	dc->dml.ip.can_vstartup_lines_exceed_vsync_plus_back_porch_lines_minus_one =
		dc->dcn_ip->can_vstartup_lines_exceed_vsync_plus_back_porch_lines_minus_one == dcn_bw_yes;
	dc->dml.ip.bug_forcing_LC_req_same_size_fixed =
		dc->dcn_ip->bug_forcing_luma_and_chroma_request_to_same_size_fixed == dcn_bw_yes;
	dc->dml.ip.dcfclk_cstate_latency = dc->dcn_ip->dcfclk_cstate_latency;
	kernel_fpu_end();
}