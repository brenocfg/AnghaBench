#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct irq_service_init_data {struct dc_context* ctx; } ;
struct TYPE_7__ {int clk_src_count; unsigned int pipe_count; unsigned int timing_generator_count; int /*<<< orphan*/ ** sw_i2cs; int /*<<< orphan*/ ** hw_i2cs; int /*<<< orphan*/ ** engines; TYPE_4__* res_cap; int /*<<< orphan*/ ** opps; int /*<<< orphan*/ ** transforms; int /*<<< orphan*/ ** ipps; int /*<<< orphan*/ ** mis; int /*<<< orphan*/ ** timing_generators; void* underlay_pipe_index; int /*<<< orphan*/  irqs; int /*<<< orphan*/ * abm; int /*<<< orphan*/ * dmcu; int /*<<< orphan*/ ** clock_sources; int /*<<< orphan*/ * dp_clock_source; int /*<<< orphan*/ * funcs; } ;
struct dce110_resource_pool {TYPE_3__ base; } ;
struct dc_context {struct dc_bios* dc_bios; } ;
struct TYPE_6__ {scalar_t__ external_clock_source_frequency_for_dp; } ;
struct dc_bios {TYPE_2__ fw_info; scalar_t__ fw_info_valid; int /*<<< orphan*/ * regs; } ;
struct TYPE_5__ {int max_downscale_ratio; int i2c_speed_in_khz; int max_cursor_size; int dual_link_dvi; int disable_dp_clk_share; unsigned int max_planes; int /*<<< orphan*/ * planes; } ;
struct dc {TYPE_1__ caps; struct dc_context* ctx; } ;
struct TYPE_8__ {unsigned int num_timing_generator; unsigned int num_ddc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  CLOCK_SOURCE_ID_EXTERNAL ; 
 int /*<<< orphan*/  CLOCK_SOURCE_ID_PLL0 ; 
 int /*<<< orphan*/  CLOCK_SOURCE_ID_PLL1 ; 
 int /*<<< orphan*/  CLOCK_SOURCE_ID_PLL2 ; 
 void* NO_UNDERLAY_PIPE ; 
 int /*<<< orphan*/  abm_mask ; 
 int /*<<< orphan*/  abm_regs ; 
 int /*<<< orphan*/  abm_shift ; 
 int /*<<< orphan*/  bios_regs ; 
 int /*<<< orphan*/ * clk_src_regs ; 
 int /*<<< orphan*/  dal_irq_service_dce110_create (struct irq_service_init_data*) ; 
 int /*<<< orphan*/ * dce100_aux_engine_create (struct dc_context*,unsigned int) ; 
 void* dce100_clock_source_create (struct dc_context*,struct dc_bios*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dce100_hw_sequencer_construct (struct dc*) ; 
 int /*<<< orphan*/ * dce100_i2c_hw_create (struct dc_context*,unsigned int) ; 
 int /*<<< orphan*/ * dce100_ipp_create (struct dc_context*,unsigned int) ; 
 int /*<<< orphan*/ * dce100_mem_input_create (struct dc_context*,unsigned int) ; 
 int /*<<< orphan*/ * dce100_opp_create (struct dc_context*,unsigned int) ; 
 int /*<<< orphan*/  dce100_res_pool_funcs ; 
 int /*<<< orphan*/ * dce100_tg_offsets ; 
 int /*<<< orphan*/ * dce100_timing_generator_create (struct dc_context*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dce100_transform_create (struct dc_context*,unsigned int) ; 
 int /*<<< orphan*/ * dce_abm_create (struct dc_context*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dce_dmcu_create (struct dc_context*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destruct (struct dce110_resource_pool*) ; 
 int /*<<< orphan*/  dm_error (char*) ; 
 int /*<<< orphan*/  dmcu_mask ; 
 int /*<<< orphan*/  dmcu_regs ; 
 int /*<<< orphan*/  dmcu_shift ; 
 int /*<<< orphan*/  plane_cap ; 
 TYPE_4__ res_cap ; 
 int /*<<< orphan*/  res_create_funcs ; 
 int /*<<< orphan*/  resource_construct (int /*<<< orphan*/ ,struct dc*,TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool construct(
	uint8_t num_virtual_links,
	struct dc  *dc,
	struct dce110_resource_pool *pool)
{
	unsigned int i;
	struct dc_context *ctx = dc->ctx;
	struct dc_bios *bp;

	ctx->dc_bios->regs = &bios_regs;

	pool->base.res_cap = &res_cap;
	pool->base.funcs = &dce100_res_pool_funcs;
	pool->base.underlay_pipe_index = NO_UNDERLAY_PIPE;

	bp = ctx->dc_bios;

	if (bp->fw_info_valid && bp->fw_info.external_clock_source_frequency_for_dp != 0) {
		pool->base.dp_clock_source =
				dce100_clock_source_create(ctx, bp, CLOCK_SOURCE_ID_EXTERNAL, NULL, true);

		pool->base.clock_sources[0] =
				dce100_clock_source_create(ctx, bp, CLOCK_SOURCE_ID_PLL0, &clk_src_regs[0], false);
		pool->base.clock_sources[1] =
				dce100_clock_source_create(ctx, bp, CLOCK_SOURCE_ID_PLL1, &clk_src_regs[1], false);
		pool->base.clock_sources[2] =
				dce100_clock_source_create(ctx, bp, CLOCK_SOURCE_ID_PLL2, &clk_src_regs[2], false);
		pool->base.clk_src_count = 3;

	} else {
		pool->base.dp_clock_source =
				dce100_clock_source_create(ctx, bp, CLOCK_SOURCE_ID_PLL0, &clk_src_regs[0], true);

		pool->base.clock_sources[0] =
				dce100_clock_source_create(ctx, bp, CLOCK_SOURCE_ID_PLL1, &clk_src_regs[1], false);
		pool->base.clock_sources[1] =
				dce100_clock_source_create(ctx, bp, CLOCK_SOURCE_ID_PLL2, &clk_src_regs[2], false);
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

	{
		struct irq_service_init_data init_data;
		init_data.ctx = dc->ctx;
		pool->base.irqs = dal_irq_service_dce110_create(&init_data);
		if (!pool->base.irqs)
			goto res_create_fail;
	}

	/*************************************************
	*  Resource + asic cap harcoding                *
	*************************************************/
	pool->base.underlay_pipe_index = NO_UNDERLAY_PIPE;
	pool->base.pipe_count = res_cap.num_timing_generator;
	pool->base.timing_generator_count = pool->base.res_cap->num_timing_generator;
	dc->caps.max_downscale_ratio = 200;
	dc->caps.i2c_speed_in_khz = 40;
	dc->caps.max_cursor_size = 128;
	dc->caps.dual_link_dvi = true;
	dc->caps.disable_dp_clk_share = true;
	for (i = 0; i < pool->base.pipe_count; i++) {
		pool->base.timing_generators[i] =
			dce100_timing_generator_create(
				ctx,
				i,
				&dce100_tg_offsets[i]);
		if (pool->base.timing_generators[i] == NULL) {
			BREAK_TO_DEBUGGER();
			dm_error("DC: failed to create tg!\n");
			goto res_create_fail;
		}

		pool->base.mis[i] = dce100_mem_input_create(ctx, i);
		if (pool->base.mis[i] == NULL) {
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create memory input!\n");
			goto res_create_fail;
		}

		pool->base.ipps[i] = dce100_ipp_create(ctx, i);
		if (pool->base.ipps[i] == NULL) {
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create input pixel processor!\n");
			goto res_create_fail;
		}

		pool->base.transforms[i] = dce100_transform_create(ctx, i);
		if (pool->base.transforms[i] == NULL) {
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create transform!\n");
			goto res_create_fail;
		}

		pool->base.opps[i] = dce100_opp_create(ctx, i);
		if (pool->base.opps[i] == NULL) {
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create output pixel processor!\n");
			goto res_create_fail;
		}
	}

	for (i = 0; i < pool->base.res_cap->num_ddc; i++) {
		pool->base.engines[i] = dce100_aux_engine_create(ctx, i);
		if (pool->base.engines[i] == NULL) {
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC:failed to create aux engine!!\n");
			goto res_create_fail;
		}
		pool->base.hw_i2cs[i] = dce100_i2c_hw_create(ctx, i);
		if (pool->base.hw_i2cs[i] == NULL) {
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC:failed to create i2c engine!!\n");
			goto res_create_fail;
		}
		pool->base.sw_i2cs[i] = NULL;
	}

	dc->caps.max_planes =  pool->base.pipe_count;

	for (i = 0; i < dc->caps.max_planes; ++i)
		dc->caps.planes[i] = plane_cap;

	if (!resource_construct(num_virtual_links, dc, &pool->base,
			&res_create_funcs))
		goto res_create_fail;

	/* Create hardware sequencer */
	dce100_hw_sequencer_construct(dc);
	return true;

res_create_fail:
	destruct(pool);

	return false;
}