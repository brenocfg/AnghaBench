#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct mcif_arb_params {int* cli_watermark; int* pstate_watermark; double time_per_pixel; int slice_lines; int arbitration_slice; int /*<<< orphan*/  max_scaled_time; } ;
struct TYPE_11__ {TYPE_9__* pipe_ctx; } ;
struct TYPE_13__ {struct mcif_arb_params* mcif_wb_arb; } ;
struct TYPE_14__ {TYPE_2__ bw_writeback; } ;
struct TYPE_15__ {TYPE_3__ dcn; } ;
struct TYPE_18__ {int /*<<< orphan*/  dml; TYPE_4__ bw; } ;
struct dc_state {TYPE_10__ res_ctx; TYPE_7__ bw_ctx; } ;
struct dc {TYPE_1__* res_pool; } ;
typedef  enum mmhubbub_wbif_mode { ____Placeholder_mmhubbub_wbif_mode } mmhubbub_wbif_mode ;
typedef  int /*<<< orphan*/  display_e2e_pipe_params_st ;
struct TYPE_20__ {TYPE_8__* stream; } ;
struct TYPE_19__ {double phy_pix_clk; TYPE_6__* writeback_info; } ;
struct TYPE_16__ {scalar_t__ out_format; scalar_t__ output_depth; } ;
struct TYPE_17__ {int wb_enabled; TYPE_5__ dwb_params; } ;
struct TYPE_12__ {int pipe_count; } ;

/* Variables and functions */
 scalar_t__ DWB_OUTPUT_PIXEL_DEPTH_8BPC ; 
 int MAX_DWB_PIPES ; 
 int PACKED_444 ; 
 int PLANAR_420_10BPC ; 
 int PLANAR_420_8BPC ; 
 int /*<<< orphan*/  dcn20_calc_max_scaled_time (double,int,int) ; 
 scalar_t__ dwb_scaler_mode_yuv420 ; 
 int get_wm_writeback_dram_clock_change (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int get_wm_writeback_urgent (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void dcn20_set_mcif_arb_params(
		struct dc *dc,
		struct dc_state *context,
		display_e2e_pipe_params_st *pipes,
		int pipe_cnt)
{
	enum mmhubbub_wbif_mode wbif_mode;
	struct mcif_arb_params *wb_arb_params;
	int i, j, k, dwb_pipe;

	/* Writeback MCIF_WB arbitration parameters */
	dwb_pipe = 0;
	for (i = 0; i < dc->res_pool->pipe_count; i++) {

		if (!context->res_ctx.pipe_ctx[i].stream)
			continue;

		for (j = 0; j < MAX_DWB_PIPES; j++) {
			if (context->res_ctx.pipe_ctx[i].stream->writeback_info[j].wb_enabled == false)
				continue;

			//wb_arb_params = &context->res_ctx.pipe_ctx[i].stream->writeback_info[j].mcif_arb_params;
			wb_arb_params = &context->bw_ctx.bw.dcn.bw_writeback.mcif_wb_arb[dwb_pipe];

			if (context->res_ctx.pipe_ctx[i].stream->writeback_info[j].dwb_params.out_format == dwb_scaler_mode_yuv420) {
				if (context->res_ctx.pipe_ctx[i].stream->writeback_info[j].dwb_params.output_depth == DWB_OUTPUT_PIXEL_DEPTH_8BPC)
					wbif_mode = PLANAR_420_8BPC;
				else
					wbif_mode = PLANAR_420_10BPC;
			} else
				wbif_mode = PACKED_444;

			for (k = 0; k < sizeof(wb_arb_params->cli_watermark)/sizeof(wb_arb_params->cli_watermark[0]); k++) {
				wb_arb_params->cli_watermark[k] = get_wm_writeback_urgent(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
				wb_arb_params->pstate_watermark[k] = get_wm_writeback_dram_clock_change(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
			}
			wb_arb_params->time_per_pixel = 16.0 / context->res_ctx.pipe_ctx[i].stream->phy_pix_clk; /* 4 bit fraction, ms */
			wb_arb_params->slice_lines = 32;
			wb_arb_params->arbitration_slice = 2;
			wb_arb_params->max_scaled_time = dcn20_calc_max_scaled_time(wb_arb_params->time_per_pixel,
				wbif_mode,
				wb_arb_params->cli_watermark[0]); /* assume 4 watermark sets have the same value */

			dwb_pipe++;

			if (dwb_pipe >= MAX_DWB_PIPES)
				return;
		}
		if (dwb_pipe >= MAX_DWB_PIPES)
			return;
	}
}