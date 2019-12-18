#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct line_buffer_params {int interleave_en; int alpha_en; int /*<<< orphan*/  pixel_expan_mode; int /*<<< orphan*/  dynamic_pixel_depth; int /*<<< orphan*/  depth; } ;
struct TYPE_4__ {TYPE_1__* caps; } ;
struct dcn10_dpp {TYPE_2__ base; } ;
typedef  enum lb_memory_config { ____Placeholder_lb_memory_config } lb_memory_config ;
struct TYPE_3__ {scalar_t__ dscl_data_proc_format; } ;

/* Variables and functions */
 int /*<<< orphan*/  DITHER_EN ; 
 scalar_t__ DSCL_DATA_PRCESSING_FIXED_FORMAT ; 
 int /*<<< orphan*/  DYNAMIC_PIXEL_DEPTH ; 
 int /*<<< orphan*/  INTERLEAVE_EN ; 
 int /*<<< orphan*/  LB_DATA_FORMAT ; 
 int /*<<< orphan*/  LB_DATA_FORMAT__ALPHA_EN ; 
 int /*<<< orphan*/  LB_MAX_PARTITIONS ; 
 int /*<<< orphan*/  LB_MEMORY_CTRL ; 
 int /*<<< orphan*/  MEMORY_CONFIG ; 
 int /*<<< orphan*/  PIXEL_DEPTH ; 
 int /*<<< orphan*/  PIXEL_EXPAN_MODE ; 
 int /*<<< orphan*/  PIXEL_REDUCE_MODE ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dpp1_dscl_get_pixel_depth_val (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dpp1_dscl_set_lb(
	struct dcn10_dpp *dpp,
	const struct line_buffer_params *lb_params,
	enum lb_memory_config mem_size_config)
{
	/* LB */
	if (dpp->base.caps->dscl_data_proc_format == DSCL_DATA_PRCESSING_FIXED_FORMAT) {
		/* DSCL caps: pixel data processed in fixed format */
		uint32_t pixel_depth = dpp1_dscl_get_pixel_depth_val(lb_params->depth);
		uint32_t dyn_pix_depth = lb_params->dynamic_pixel_depth;

		REG_SET_7(LB_DATA_FORMAT, 0,
			PIXEL_DEPTH, pixel_depth, /* Pixel depth stored in LB */
			PIXEL_EXPAN_MODE, lb_params->pixel_expan_mode, /* Pixel expansion mode */
			PIXEL_REDUCE_MODE, 1, /* Pixel reduction mode: Rounding */
			DYNAMIC_PIXEL_DEPTH, dyn_pix_depth, /* Dynamic expansion pixel depth */
			DITHER_EN, 0, /* Dithering enable: Disabled */
			INTERLEAVE_EN, lb_params->interleave_en, /* Interleave source enable */
			LB_DATA_FORMAT__ALPHA_EN, lb_params->alpha_en); /* Alpha enable */
	}
#if defined(CONFIG_DRM_AMD_DC_DCN2_0)
	else {
		/* DSCL caps: pixel data processed in float format */
		REG_SET_2(LB_DATA_FORMAT, 0,
			INTERLEAVE_EN, lb_params->interleave_en, /* Interleave source enable */
			LB_DATA_FORMAT__ALPHA_EN, lb_params->alpha_en); /* Alpha enable */
	}
#endif

	REG_SET_2(LB_MEMORY_CTRL, 0,
		MEMORY_CONFIG, mem_size_config,
		LB_MAX_PARTITIONS, 63);
}