#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  vertical_addressable; int /*<<< orphan*/  horizontal_addressable; } ;
struct embedded_panel_info {TYPE_6__ lcd_timing; } ;
struct TYPE_7__ {int FBC_SUPPORT; int LPT_SUPPORT; int DUMMY_BACKEND; int CLK_GATING_DISABLED; } ;
struct TYPE_8__ {TYPE_1__ bits; scalar_t__ raw; } ;
struct TYPE_11__ {int lpt_channels_num; int memory_bus_width; int is_enabled; int /*<<< orphan*/  embedded_panel_v_size; int /*<<< orphan*/  embedded_panel_h_size; scalar_t__ attached_inst; scalar_t__ dram_channels_num; scalar_t__ channel_interleave_size; scalar_t__ raw_size; scalar_t__ banks_num; int /*<<< orphan*/  min_compress_ratio; scalar_t__ preferred_requested_size; scalar_t__ allocated_size; struct dc_context* ctx; TYPE_2__ options; } ;
struct dce112_compressor {TYPE_5__ base; } ;
struct TYPE_9__ {int vram_width; } ;
struct dc_context {TYPE_3__ asic_id; struct dc_bios* dc_bios; } ;
struct dc_bios {TYPE_4__* funcs; } ;
struct TYPE_10__ {scalar_t__ (* get_embedded_panel_info ) (struct dc_bios*,struct embedded_panel_info*) ;} ;

/* Variables and functions */
 scalar_t__ BP_RESULT_OK ; 
 int /*<<< orphan*/  FBC_COMPRESS_RATIO_INVALID ; 
 scalar_t__ stub1 (struct dc_bios*,struct embedded_panel_info*) ; 

void dce112_compressor_construct(struct dce112_compressor *compressor,
	struct dc_context *ctx)
{
	struct dc_bios *bp = ctx->dc_bios;
	struct embedded_panel_info panel_info;

	compressor->base.options.raw = 0;
	compressor->base.options.bits.FBC_SUPPORT = true;
	compressor->base.options.bits.LPT_SUPPORT = true;
	 /* For DCE 11 always use one DRAM channel for LPT */
	compressor->base.lpt_channels_num = 1;
	compressor->base.options.bits.DUMMY_BACKEND = false;

	/* Check if this system has more than 1 DRAM channel; if only 1 then LPT
	 * should not be supported */
	if (compressor->base.memory_bus_width == 64)
		compressor->base.options.bits.LPT_SUPPORT = false;

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

	if (BP_RESULT_OK ==
			bp->funcs->get_embedded_panel_info(bp, &panel_info)) {
		compressor->base.embedded_panel_h_size =
			panel_info.lcd_timing.horizontal_addressable;
		compressor->base.embedded_panel_v_size =
			panel_info.lcd_timing.vertical_addressable;
	}
}