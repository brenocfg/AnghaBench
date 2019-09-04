#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ phyclk_khz; } ;
struct TYPE_11__ {int /*<<< orphan*/  watermarks; TYPE_8__ clk; } ;
struct TYPE_12__ {TYPE_3__ dcn; } ;
struct dc_state {scalar_t__ stream_count; TYPE_4__ bw; } ;
struct TYPE_14__ {scalar_t__ sanity_checks; } ;
struct dc {TYPE_6__ debug; TYPE_5__* res_pool; TYPE_1__* ctx; } ;
struct TYPE_15__ {TYPE_2__* funcs; } ;
struct TYPE_13__ {int ref_clock_inKhz; int /*<<< orphan*/  hubbub; TYPE_7__* dccg; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* update_clocks ) (TYPE_7__*,TYPE_8__*,int) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  dce_environment; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_FPGA_MAXIMUS_DC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcn10_pplib_apply_display_requirements (struct dc*,struct dc_state*) ; 
 int /*<<< orphan*/  dcn10_verify_allow_pstate_change_high (struct dc*) ; 
 int /*<<< orphan*/  hubbub1_program_watermarks (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*,TYPE_8__*,int) ; 

__attribute__((used)) static void dcn10_set_bandwidth(
		struct dc *dc,
		struct dc_state *context,
		bool safe_to_lower)
{
	if (dc->debug.sanity_checks)
		dcn10_verify_allow_pstate_change_high(dc);

	if (!IS_FPGA_MAXIMUS_DC(dc->ctx->dce_environment)) {
		if (context->stream_count == 0)
			context->bw.dcn.clk.phyclk_khz = 0;

		dc->res_pool->dccg->funcs->update_clocks(
				dc->res_pool->dccg,
				&context->bw.dcn.clk,
				safe_to_lower);

		dcn10_pplib_apply_display_requirements(dc, context);
	}

	hubbub1_program_watermarks(dc->res_pool->hubbub,
			&context->bw.dcn.watermarks,
			dc->res_pool->ref_clock_inKhz / 1000,
			true);

	if (dc->debug.sanity_checks)
		dcn10_verify_allow_pstate_change_high(dc);
}