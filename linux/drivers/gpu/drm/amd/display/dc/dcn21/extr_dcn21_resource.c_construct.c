#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct irq_service_init_data {struct dc_context* ctx; } ;
struct TYPE_9__ {int pipe_count; int clk_src_count; int timing_generator_count; int /*<<< orphan*/ ** dscs; TYPE_3__* res_cap; int /*<<< orphan*/ * hubbub; int /*<<< orphan*/ * mpc; int /*<<< orphan*/ ** timing_generators; int /*<<< orphan*/ ** opps; int /*<<< orphan*/ ** sw_i2cs; int /*<<< orphan*/ ** hw_i2cs; int /*<<< orphan*/ ** engines; int /*<<< orphan*/ ** dpps; int /*<<< orphan*/ ** ipps; int /*<<< orphan*/ ** hubps; int /*<<< orphan*/  irqs; int /*<<< orphan*/  pp_smu; int /*<<< orphan*/ * dmcub; int /*<<< orphan*/ * dccg; int /*<<< orphan*/ ** clock_sources; void* dp_clock_source; int /*<<< orphan*/  underlay_pipe_index; int /*<<< orphan*/ * funcs; } ;
struct dcn21_resource_pool {TYPE_2__ base; } ;
struct dc_context {scalar_t__ dce_environment; TYPE_5__* dc_bios; } ;
struct TYPE_8__ {int max_downscale_ratio; int i2c_speed_in_khz; int max_cursor_size; int dmdata_alloc_size; int hw_3d_lut; int max_slave_planes; int post_blend_color_processing; int force_dp_tps4_for_cp2520; int max_planes; int /*<<< orphan*/ * planes; } ;
struct dc {int /*<<< orphan*/  cap_funcs; TYPE_1__ caps; struct dc_context* ctx; int /*<<< orphan*/  dml; scalar_t__ vm_helper; void* debug; } ;
struct TYPE_11__ {int /*<<< orphan*/ * regs; } ;
struct TYPE_10__ {int num_ddc; int num_opp; int num_timing_generator; int num_dsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  CLOCK_SOURCE_COMBO_PHY_PLL0 ; 
 int /*<<< orphan*/  CLOCK_SOURCE_COMBO_PHY_PLL1 ; 
 int /*<<< orphan*/  CLOCK_SOURCE_ID_DP_DTO ; 
 scalar_t__ DCE_ENV_FPGA_MAXIMUS ; 
 scalar_t__ DCE_ENV_PRODUCTION_DRV ; 
 size_t DCN20_CLK_SRC_PLL0 ; 
 size_t DCN20_CLK_SRC_PLL1 ; 
 int DCN20_CLK_SRC_TOTAL_DCN21 ; 
 int /*<<< orphan*/  DML_PROJECT_DCN21 ; 
 scalar_t__ IS_FPGA_MAXIMUS_DC (scalar_t__) ; 
 int /*<<< orphan*/  NO_UNDERLAY_PIPE ; 
 int /*<<< orphan*/  bios_regs ; 
 int /*<<< orphan*/  cap_funcs ; 
 int /*<<< orphan*/ * clk_src_regs ; 
 int /*<<< orphan*/  dal_irq_service_dcn21_create (struct irq_service_init_data*) ; 
 int /*<<< orphan*/ * dccg2_create (struct dc_context*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dccg_mask ; 
 int /*<<< orphan*/  dccg_regs ; 
 int /*<<< orphan*/  dccg_shift ; 
 int /*<<< orphan*/  dcn20_dwbc_create (struct dc_context*,TYPE_2__*) ; 
 int /*<<< orphan*/  dcn20_hw_sequencer_construct (struct dc*) ; 
 int /*<<< orphan*/  dcn20_mmhubbub_create (struct dc_context*,TYPE_2__*) ; 
 int /*<<< orphan*/ * dcn21_aux_engine_create (struct dc_context*,int) ; 
 void* dcn21_clock_source_create (struct dc_context*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * dcn21_dmcub_create (struct dc_context*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dcn21_dpp_create (struct dc_context*,int) ; 
 int /*<<< orphan*/ * dcn21_dsc_create (struct dc_context*,int) ; 
 int /*<<< orphan*/ * dcn21_hubbub_create (struct dc_context*) ; 
 int /*<<< orphan*/ * dcn21_hubp_create (struct dc_context*,int) ; 
 int /*<<< orphan*/ * dcn21_i2c_hw_create (struct dc_context*,int) ; 
 int /*<<< orphan*/ * dcn21_ipp_create (struct dc_context*,int) ; 
 int /*<<< orphan*/ * dcn21_mpc_create (struct dc_context*) ; 
 int /*<<< orphan*/ * dcn21_opp_create (struct dc_context*,int) ; 
 int /*<<< orphan*/  dcn21_pp_smu_create (struct dc_context*) ; 
 int /*<<< orphan*/  dcn21_res_pool_funcs ; 
 int /*<<< orphan*/ * dcn21_timing_generator_create (struct dc_context*,int) ; 
 int /*<<< orphan*/  dcn2_1_ip ; 
 int /*<<< orphan*/  dcn2_1_soc ; 
 void* debug_defaults_diags ; 
 void* debug_defaults_drv ; 
 int /*<<< orphan*/  destruct (struct dcn21_resource_pool*) ; 
 int /*<<< orphan*/  dm_error (char*,...) ; 
 int /*<<< orphan*/  dmcub_mask ; 
 int /*<<< orphan*/  dmcub_regs ; 
 int /*<<< orphan*/  dmcub_shift ; 
 int /*<<< orphan*/  dml_init_instance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plane_cap ; 
 TYPE_3__ res_cap_rn ; 
 TYPE_3__ res_cap_rn_FPGA_4pipe ; 
 int /*<<< orphan*/  res_create_funcs ; 
 int /*<<< orphan*/  res_create_maximus_funcs ; 
 int /*<<< orphan*/  resource_construct (int /*<<< orphan*/ ,struct dc*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_helper_init (scalar_t__,int) ; 

__attribute__((used)) static bool construct(
	uint8_t num_virtual_links,
	struct dc *dc,
	struct dcn21_resource_pool *pool)
{
	int i;
	struct dc_context *ctx = dc->ctx;
	struct irq_service_init_data init_data;

	ctx->dc_bios->regs = &bios_regs;

	pool->base.res_cap = &res_cap_rn;
#ifdef DIAGS_BUILD
	if (IS_FPGA_MAXIMUS_DC(dc->ctx->dce_environment))
		//pool->base.res_cap = &res_cap_nv10_FPGA_2pipe_dsc;
		pool->base.res_cap = &res_cap_rn_FPGA_4pipe;
#endif

	pool->base.funcs = &dcn21_res_pool_funcs;

	/*************************************************
	 *  Resource + asic cap harcoding                *
	 *************************************************/
	pool->base.underlay_pipe_index = NO_UNDERLAY_PIPE;

	pool->base.pipe_count = 4;
	dc->caps.max_downscale_ratio = 200;
	dc->caps.i2c_speed_in_khz = 100;
	dc->caps.max_cursor_size = 256;
	dc->caps.dmdata_alloc_size = 2048;
	dc->caps.hw_3d_lut = true;

	dc->caps.max_slave_planes = 1;
	dc->caps.post_blend_color_processing = true;
	dc->caps.force_dp_tps4_for_cp2520 = true;

	if (dc->ctx->dce_environment == DCE_ENV_PRODUCTION_DRV)
		dc->debug = debug_defaults_drv;
	else if (dc->ctx->dce_environment == DCE_ENV_FPGA_MAXIMUS) {
		pool->base.pipe_count = 4;
		dc->debug = debug_defaults_diags;
	} else
		dc->debug = debug_defaults_diags;

	// Init the vm_helper
	if (dc->vm_helper)
		vm_helper_init(dc->vm_helper, 16);

	/*************************************************
	 *  Create resources                             *
	 *************************************************/

	pool->base.clock_sources[DCN20_CLK_SRC_PLL0] =
			dcn21_clock_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_COMBO_PHY_PLL0,
				&clk_src_regs[0], false);
	pool->base.clock_sources[DCN20_CLK_SRC_PLL1] =
			dcn21_clock_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_COMBO_PHY_PLL1,
				&clk_src_regs[1], false);

	pool->base.clk_src_count = DCN20_CLK_SRC_TOTAL_DCN21;

	/* todo: not reuse phy_pll registers */
	pool->base.dp_clock_source =
			dcn21_clock_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_ID_DP_DTO,
				&clk_src_regs[0], true);

	for (i = 0; i < pool->base.clk_src_count; i++) {
		if (pool->base.clock_sources[i] == NULL) {
			dm_error("DC: failed to create clock sources!\n");
			BREAK_TO_DEBUGGER();
			goto create_fail;
		}
	}

	pool->base.dccg = dccg2_create(ctx, &dccg_regs, &dccg_shift, &dccg_mask);
	if (pool->base.dccg == NULL) {
		dm_error("DC: failed to create dccg!\n");
		BREAK_TO_DEBUGGER();
		goto create_fail;
	}

#ifdef CONFIG_DRM_AMD_DC_DMUB
	pool->base.dmcub = dcn21_dmcub_create(ctx,
			&dmcub_regs,
			&dmcub_shift,
			&dmcub_mask);
	if (pool->base.dmcub == NULL) {
		dm_error("DC: failed to create dmcub!\n");
		BREAK_TO_DEBUGGER();
		goto create_fail;
	}
#endif

	pool->base.pp_smu = dcn21_pp_smu_create(ctx);

	dml_init_instance(&dc->dml, &dcn2_1_soc, &dcn2_1_ip, DML_PROJECT_DCN21);

	init_data.ctx = dc->ctx;
	pool->base.irqs = dal_irq_service_dcn21_create(&init_data);
	if (!pool->base.irqs)
		goto create_fail;

	/* mem input -> ipp -> dpp -> opp -> TG */
	for (i = 0; i < pool->base.pipe_count; i++) {
		pool->base.hubps[i] = dcn21_hubp_create(ctx, i);
		if (pool->base.hubps[i] == NULL) {
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create memory input!\n");
			goto create_fail;
		}

		pool->base.ipps[i] = dcn21_ipp_create(ctx, i);
		if (pool->base.ipps[i] == NULL) {
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create input pixel processor!\n");
			goto create_fail;
		}

		pool->base.dpps[i] = dcn21_dpp_create(ctx, i);
		if (pool->base.dpps[i] == NULL) {
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create dpps!\n");
			goto create_fail;
		}
	}

	for (i = 0; i < pool->base.res_cap->num_ddc; i++) {
		pool->base.engines[i] = dcn21_aux_engine_create(ctx, i);
		if (pool->base.engines[i] == NULL) {
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC:failed to create aux engine!!\n");
			goto create_fail;
		}
		pool->base.hw_i2cs[i] = dcn21_i2c_hw_create(ctx, i);
		if (pool->base.hw_i2cs[i] == NULL) {
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC:failed to create hw i2c!!\n");
			goto create_fail;
		}
		pool->base.sw_i2cs[i] = NULL;
	}

	for (i = 0; i < pool->base.res_cap->num_opp; i++) {
		pool->base.opps[i] = dcn21_opp_create(ctx, i);
		if (pool->base.opps[i] == NULL) {
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create output pixel processor!\n");
			goto create_fail;
		}
	}

	for (i = 0; i < pool->base.res_cap->num_timing_generator; i++) {
		pool->base.timing_generators[i] = dcn21_timing_generator_create(
				ctx, i);
		if (pool->base.timing_generators[i] == NULL) {
			BREAK_TO_DEBUGGER();
			dm_error("DC: failed to create tg!\n");
			goto create_fail;
		}
	}

	pool->base.timing_generator_count = i;

	pool->base.mpc = dcn21_mpc_create(ctx);
	if (pool->base.mpc == NULL) {
		BREAK_TO_DEBUGGER();
		dm_error("DC: failed to create mpc!\n");
		goto create_fail;
	}

	pool->base.hubbub = dcn21_hubbub_create(ctx);
	if (pool->base.hubbub == NULL) {
		BREAK_TO_DEBUGGER();
		dm_error("DC: failed to create hubbub!\n");
		goto create_fail;
	}

#ifdef CONFIG_DRM_AMD_DC_DSC_SUPPORT
	for (i = 0; i < pool->base.res_cap->num_dsc; i++) {
		pool->base.dscs[i] = dcn21_dsc_create(ctx, i);
		if (pool->base.dscs[i] == NULL) {
			BREAK_TO_DEBUGGER();
			dm_error("DC: failed to create display stream compressor %d!\n", i);
			goto create_fail;
		}
	}
#endif

	if (!dcn20_dwbc_create(ctx, &pool->base)) {
		BREAK_TO_DEBUGGER();
		dm_error("DC: failed to create dwbc!\n");
		goto create_fail;
	}
	if (!dcn20_mmhubbub_create(ctx, &pool->base)) {
		BREAK_TO_DEBUGGER();
		dm_error("DC: failed to create mcif_wb!\n");
		goto create_fail;
	}

	if (!resource_construct(num_virtual_links, dc, &pool->base,
			(!IS_FPGA_MAXIMUS_DC(dc->ctx->dce_environment) ?
			&res_create_funcs : &res_create_maximus_funcs)))
			goto create_fail;

	dcn20_hw_sequencer_construct(dc);

	dc->caps.max_planes =  pool->base.pipe_count;

	for (i = 0; i < dc->caps.max_planes; ++i)
		dc->caps.planes[i] = plane_cap;

	dc->cap_funcs = cap_funcs;

	return true;

create_fail:

	destruct(pool);

	return false;
}