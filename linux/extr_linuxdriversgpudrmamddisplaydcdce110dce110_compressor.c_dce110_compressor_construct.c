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
struct TYPE_5__ {int FBC_SUPPORT; int DUMMY_BACKEND; int CLK_GATING_DISABLED; } ;
struct TYPE_6__ {TYPE_1__ bits; scalar_t__ raw; } ;
struct TYPE_8__ {int lpt_channels_num; int is_enabled; int /*<<< orphan*/ * funcs; scalar_t__ attached_inst; scalar_t__ dram_channels_num; scalar_t__ channel_interleave_size; scalar_t__ raw_size; scalar_t__ banks_num; int /*<<< orphan*/  min_compress_ratio; scalar_t__ preferred_requested_size; scalar_t__ allocated_size; int /*<<< orphan*/  memory_bus_width; scalar_t__ embedded_panel_v_size; scalar_t__ embedded_panel_h_size; struct dc_context* ctx; TYPE_2__ options; } ;
struct dce110_compressor {TYPE_4__ base; } ;
struct TYPE_7__ {int /*<<< orphan*/  vram_width; } ;
struct dc_context {TYPE_3__ asic_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  FBC_COMPRESS_RATIO_INVALID ; 
 int /*<<< orphan*/  dce110_compressor_funcs ; 

void dce110_compressor_construct(struct dce110_compressor *compressor,
	struct dc_context *ctx)
{

	compressor->base.options.raw = 0;
	compressor->base.options.bits.FBC_SUPPORT = true;

	/* for dce 11 always use one dram channel for lpt */
	compressor->base.lpt_channels_num = 1;
	compressor->base.options.bits.DUMMY_BACKEND = false;

	/*
	 * check if this system has more than 1 dram channel; if only 1 then lpt
	 * should not be supported
	 */


	compressor->base.options.bits.CLK_GATING_DISABLED = false;

	compressor->base.ctx = ctx;
	compressor->base.embedded_panel_h_size = 0;
	compressor->base.embedded_panel_v_size = 0;
	compressor->base.memory_bus_width = ctx->asic_id.vram_width;
	compressor->base.allocated_size = 0;
	compressor->base.preferred_requested_size = 0;
	compressor->base.min_compress_ratio = FBC_COMPRESS_RATIO_INVALID;
	compressor->base.banks_num = 0;
	compressor->base.raw_size = 0;
	compressor->base.channel_interleave_size = 0;
	compressor->base.dram_channels_num = 0;
	compressor->base.lpt_channels_num = 0;
	compressor->base.attached_inst = 0;
	compressor->base.is_enabled = false;
	compressor->base.funcs = &dce110_compressor_funcs;

}