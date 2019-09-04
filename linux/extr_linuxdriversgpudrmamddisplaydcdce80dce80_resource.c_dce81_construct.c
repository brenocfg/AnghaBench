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
typedef  int /*<<< orphan*/  uint8_t ;
struct irq_service_init_data {struct dc_context* ctx; } ;
struct dm_pp_static_clock_info {int /*<<< orphan*/  max_clocks_state; int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {unsigned int pipe_count; unsigned int timing_generator_count; int clk_src_count; int /*<<< orphan*/ ** opps; int /*<<< orphan*/ ** transforms; int /*<<< orphan*/ ** ipps; int /*<<< orphan*/ ** mis; int /*<<< orphan*/ ** timing_generators; int /*<<< orphan*/  irqs; TYPE_5__* dccg; int /*<<< orphan*/ * abm; int /*<<< orphan*/ * dmcu; int /*<<< orphan*/ ** clock_sources; int /*<<< orphan*/ * dp_clock_source; int /*<<< orphan*/  underlay_pipe_index; int /*<<< orphan*/ * funcs; TYPE_4__* res_cap; } ;
struct dce110_resource_pool {TYPE_3__ base; } ;
struct dc_firmware_info {scalar_t__ external_clock_source_frequency_for_dp; } ;
struct dc_context {struct dc_bios* dc_bios; } ;
struct dc_bios {TYPE_2__* funcs; int /*<<< orphan*/ * regs; } ;
struct TYPE_6__ {int max_downscale_ratio; int i2c_speed_in_khz; int max_cursor_size; int is_apu; unsigned int max_planes; int disable_dp_clk_share; } ;
struct dc {TYPE_1__ caps; struct dc_context* ctx; } ;
struct TYPE_10__ {int /*<<< orphan*/  max_clks_state; } ;
struct TYPE_9__ {unsigned int num_timing_generator; } ;
struct TYPE_7__ {scalar_t__ (* get_firmware_info ) (struct dc_bios*,struct dc_firmware_info*) ;} ;

/* Variables and functions */
 scalar_t__ BP_RESULT_OK ; 
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  CLOCK_SOURCE_ID_EXTERNAL ; 
 int /*<<< orphan*/  CLOCK_SOURCE_ID_PLL0 ; 
 int /*<<< orphan*/  CLOCK_SOURCE_ID_PLL1 ; 
 int /*<<< orphan*/  CLOCK_SOURCE_ID_PLL2 ; 
 int /*<<< orphan*/  NO_UNDERLAY_PIPE ; 
 int /*<<< orphan*/  abm_mask ; 
 int /*<<< orphan*/  abm_regs ; 
 int /*<<< orphan*/  abm_shift ; 
 int /*<<< orphan*/  bios_regs ; 
 int /*<<< orphan*/ * clk_src_regs ; 
 int /*<<< orphan*/  dal_irq_service_dce80_create (struct irq_service_init_data*) ; 
 void* dce80_clock_source_create (struct dc_context*,struct dc_bios*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dce80_hw_sequencer_construct (struct dc*) ; 
 int /*<<< orphan*/ * dce80_ipp_create (struct dc_context*,unsigned int) ; 
 int /*<<< orphan*/ * dce80_mem_input_create (struct dc_context*,unsigned int) ; 
 int /*<<< orphan*/ * dce80_opp_create (struct dc_context*,unsigned int) ; 
 int /*<<< orphan*/  dce80_res_pool_funcs ; 
 int /*<<< orphan*/ * dce80_tg_offsets ; 
 int /*<<< orphan*/ * dce80_timing_generator_create (struct dc_context*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dce80_transform_create (struct dc_context*,unsigned int) ; 
 int /*<<< orphan*/ * dce_abm_create (struct dc_context*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__* dce_dccg_create (struct dc_context*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dce_dmcu_create (struct dc_context*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destruct (struct dce110_resource_pool*) ; 
 int /*<<< orphan*/  disp_clk_mask ; 
 int /*<<< orphan*/  disp_clk_regs ; 
 int /*<<< orphan*/  disp_clk_shift ; 
 int /*<<< orphan*/  dm_error (char*) ; 
 scalar_t__ dm_pp_get_static_clocks (struct dc_context*,struct dm_pp_static_clock_info*) ; 
 int /*<<< orphan*/  dmcu_mask ; 
 int /*<<< orphan*/  dmcu_regs ; 
 int /*<<< orphan*/  dmcu_shift ; 
 TYPE_4__ res_cap_81 ; 
 int /*<<< orphan*/  res_create_funcs ; 
 int /*<<< orphan*/  resource_construct (int /*<<< orphan*/ ,struct dc*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct dc_bios*,struct dc_firmware_info*) ; 

__attribute__((used)) static bool dce81_construct(
	uint8_t num_virtual_links,
	struct dc *dc,
	struct dce110_resource_pool *pool)
{
	unsigned int i;
	struct dc_context *ctx = dc->ctx;
	struct dc_firmware_info info;
	struct dc_bios *bp;
	struct dm_pp_static_clock_info static_clk_info = {0};

	ctx->dc_bios->regs = &bios_regs;

	pool->base.res_cap = &res_cap_81;
	pool->base.funcs = &dce80_res_pool_funcs;


	/*************************************************
	 *  Resource + asic cap harcoding                *
	 *************************************************/
	pool->base.underlay_pipe_index = NO_UNDERLAY_PIPE;
	pool->base.pipe_count = res_cap_81.num_timing_generator;
	pool->base.timing_generator_count = res_cap_81.num_timing_generator;
	dc->caps.max_downscale_ratio = 200;
	dc->caps.i2c_speed_in_khz = 40;
	dc->caps.max_cursor_size = 128;
	dc->caps.is_apu = true;

	/*************************************************
	 *  Create resources                             *
	 *************************************************/

	bp = ctx->dc_bios;

	if ((bp->funcs->get_firmware_info(bp, &info) == BP_RESULT_OK) &&
		info.external_clock_source_frequency_for_dp != 0) {
		pool->base.dp_clock_source =
				dce80_clock_source_create(ctx, bp, CLOCK_SOURCE_ID_EXTERNAL, NULL, true);

		pool->base.clock_sources[0] =
				dce80_clock_source_create(ctx, bp, CLOCK_SOURCE_ID_PLL0, &clk_src_regs[0], false);
		pool->base.clock_sources[1] =
				dce80_clock_source_create(ctx, bp, CLOCK_SOURCE_ID_PLL1, &clk_src_regs[1], false);
		pool->base.clock_sources[2] =
				dce80_clock_source_create(ctx, bp, CLOCK_SOURCE_ID_PLL2, &clk_src_regs[2], false);
		pool->base.clk_src_count = 3;

	} else {
		pool->base.dp_clock_source =
				dce80_clock_source_create(ctx, bp, CLOCK_SOURCE_ID_PLL0, &clk_src_regs[0], true);

		pool->base.clock_sources[0] =
				dce80_clock_source_create(ctx, bp, CLOCK_SOURCE_ID_PLL1, &clk_src_regs[1], false);
		pool->base.clock_sources[1] =
				dce80_clock_source_create(ctx, bp, CLOCK_SOURCE_ID_PLL2, &clk_src_regs[2], false);
		pool->base.clk_src_count = 2;
	}

	if (pool->base.dp_clock_source == NULL) {
		dm_error("DC: failed to create dp clock source!\n");
		BREAK_TO_DEBUGGER();
		goto res_create_fail;
	}

	for (i = 0; i < pool->base.clk_src_count; i++) {
		if (pool->base.clock_sources[i] == NULL) {
			dm_error("DC: failed to create clock sources!\n");
			BREAK_TO_DEBUGGER();
			goto res_create_fail;
		}
	}

	pool->base.dccg = dce_dccg_create(ctx,
			&disp_clk_regs,
			&disp_clk_shift,
			&disp_clk_mask);
	if (pool->base.dccg == NULL) {
		dm_error("DC: failed to create display clock!\n");
		BREAK_TO_DEBUGGER();
		goto res_create_fail;
	}

	pool->base.dmcu = dce_dmcu_create(ctx,
			&dmcu_regs,
			&dmcu_shift,
			&dmcu_mask);
	if (pool->base.dmcu == NULL) {
		dm_error("DC: failed to create dmcu!\n");
		BREAK_TO_DEBUGGER();
		goto res_create_fail;
	}

	pool->base.abm = dce_abm_create(ctx,
			&abm_regs,
			&abm_shift,
			&abm_mask);
	if (pool->base.abm == NULL) {
		dm_error("DC: failed to create abm!\n");
		BREAK_TO_DEBUGGER();
		goto res_create_fail;
	}

	if (dm_pp_get_static_clocks(ctx, &static_clk_info))
		pool->base.dccg->max_clks_state =
					static_clk_info.max_clocks_state;

	{
		struct irq_service_init_data init_data;
		init_data.ctx = dc->ctx;
		pool->base.irqs = dal_irq_service_dce80_create(&init_data);
		if (!pool->base.irqs)
			goto res_create_fail;
	}

	for (i = 0; i < pool->base.pipe_count; i++) {
		pool->base.timing_generators[i] = dce80_timing_generator_create(
				ctx, i, &dce80_tg_offsets[i]);
		if (pool->base.timing_generators[i] == NULL) {
			BREAK_TO_DEBUGGER();
			dm_error("DC: failed to create tg!\n");
			goto res_create_fail;
		}

		pool->base.mis[i] = dce80_mem_input_create(ctx, i);
		if (pool->base.mis[i] == NULL) {
			BREAK_TO_DEBUGGER();
			dm_error("DC: failed to create memory input!\n");
			goto res_create_fail;
		}

		pool->base.ipps[i] = dce80_ipp_create(ctx, i);
		if (pool->base.ipps[i] == NULL) {
			BREAK_TO_DEBUGGER();
			dm_error("DC: failed to create input pixel processor!\n");
			goto res_create_fail;
		}

		pool->base.transforms[i] = dce80_transform_create(ctx, i);
		if (pool->base.transforms[i] == NULL) {
			BREAK_TO_DEBUGGER();
			dm_error("DC: failed to create transform!\n");
			goto res_create_fail;
		}

		pool->base.opps[i] = dce80_opp_create(ctx, i);
		if (pool->base.opps[i] == NULL) {
			BREAK_TO_DEBUGGER();
			dm_error("DC: failed to create output pixel processor!\n");
			goto res_create_fail;
		}
	}

	dc->caps.max_planes =  pool->base.pipe_count;
	dc->caps.disable_dp_clk_share = true;

	if (!resource_construct(num_virtual_links, dc, &pool->base,
			&res_create_funcs))
		goto res_create_fail;

	/* Create hardware sequencer */
	dce80_hw_sequencer_construct(dc);

	return true;

res_create_fail:
	destruct(pool);
	return false;
}