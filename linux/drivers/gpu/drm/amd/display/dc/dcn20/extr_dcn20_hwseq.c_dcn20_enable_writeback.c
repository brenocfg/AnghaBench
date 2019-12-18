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
struct timing_generator {TYPE_2__* funcs; } ;
struct mcif_wb {TYPE_8__* funcs; } ;
struct dwbc {TYPE_9__* funcs; } ;
struct TYPE_11__ {int /*<<< orphan*/  dest_height; } ;
struct dc_writeback_info {size_t dwb_pipe_inst; int wb_enabled; TYPE_10__ dwb_params; int /*<<< orphan*/  mcif_buf_params; } ;
struct dc_stream_status {size_t primary_otg_inst; } ;
struct dc {TYPE_7__* current_state; TYPE_1__* res_pool; } ;
struct TYPE_20__ {int /*<<< orphan*/  (* enable ) (struct dwbc*,TYPE_10__*) ;} ;
struct TYPE_19__ {int /*<<< orphan*/  (* enable_mcif ) (struct mcif_wb*) ;int /*<<< orphan*/  (* config_mcif_arb ) (struct mcif_wb*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* config_mcif_buf ) (struct mcif_wb*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_14__ {int /*<<< orphan*/ * mcif_wb_arb; } ;
struct TYPE_15__ {TYPE_3__ bw_writeback; } ;
struct TYPE_16__ {TYPE_4__ dcn; } ;
struct TYPE_17__ {TYPE_5__ bw; } ;
struct TYPE_18__ {TYPE_6__ bw_ctx; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* set_dwb_source ) (struct timing_generator*,size_t) ;} ;
struct TYPE_12__ {struct timing_generator** timing_generators; struct mcif_wb** mcif_wb; struct dwbc** dwbc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 size_t MAX_DWB_PIPES ; 
 size_t MAX_PIPES ; 
 int /*<<< orphan*/  stub1 (struct timing_generator*,size_t) ; 
 int /*<<< orphan*/  stub2 (struct mcif_wb*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct mcif_wb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (struct mcif_wb*) ; 
 int /*<<< orphan*/  stub5 (struct dwbc*,TYPE_10__*) ; 

__attribute__((used)) static void dcn20_enable_writeback(
		struct dc *dc,
		const struct dc_stream_status *stream_status,
		struct dc_writeback_info *wb_info)
{
	struct dwbc *dwb;
	struct mcif_wb *mcif_wb;
	struct timing_generator *optc;

	ASSERT(wb_info->dwb_pipe_inst < MAX_DWB_PIPES);
	ASSERT(wb_info->wb_enabled);
	dwb = dc->res_pool->dwbc[wb_info->dwb_pipe_inst];
	mcif_wb = dc->res_pool->mcif_wb[wb_info->dwb_pipe_inst];

	/* set the OPTC source mux */
	ASSERT(stream_status->primary_otg_inst < MAX_PIPES);
	optc = dc->res_pool->timing_generators[stream_status->primary_otg_inst];
	optc->funcs->set_dwb_source(optc, wb_info->dwb_pipe_inst);
	/* set MCIF_WB buffer and arbitration configuration */
	mcif_wb->funcs->config_mcif_buf(mcif_wb, &wb_info->mcif_buf_params, wb_info->dwb_params.dest_height);
	mcif_wb->funcs->config_mcif_arb(mcif_wb, &dc->current_state->bw_ctx.bw.dcn.bw_writeback.mcif_wb_arb[wb_info->dwb_pipe_inst]);
	/* Enable MCIF_WB */
	mcif_wb->funcs->enable_mcif(mcif_wb);
	/* Enable DWB */
	dwb->funcs->enable(dwb, &wb_info->dwb_params);
	/* TODO: add sequence to enable/disable warmup */
}