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
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pll_settings {int /*<<< orphan*/  use_external_clk; int /*<<< orphan*/  pix_clk_post_divider; int /*<<< orphan*/  fract_feedback_divider; int /*<<< orphan*/  feedback_divider; int /*<<< orphan*/  reference_divider; int /*<<< orphan*/  actual_pix_clk; } ;
struct TYPE_10__ {int /*<<< orphan*/  SUPPORT_YCBCR420; int /*<<< orphan*/  ENABLE_SS; } ;
struct pixel_clk_params {TYPE_4__ flags; int /*<<< orphan*/  color_depth; int /*<<< orphan*/  signal_type; int /*<<< orphan*/  encoder_object_id; int /*<<< orphan*/  controller_id; } ;
struct dce110_clk_src {TYPE_5__* bios; } ;
struct clock_source {scalar_t__ id; TYPE_1__* ctx; } ;
struct TYPE_8__ {int SET_XTALIN_REF_SRC; int SUPPORT_YUV_420; int /*<<< orphan*/  SET_GENLOCK_REF_DIV_SRC; int /*<<< orphan*/  SET_EXTERNAL_REF_DIV_SRC; } ;
struct bp_pixel_clock_parameters {scalar_t__ pll_id; TYPE_2__ flags; int /*<<< orphan*/  pixel_clock_post_divider; int /*<<< orphan*/  fractional_feedback_divider; int /*<<< orphan*/  feedback_divider; int /*<<< orphan*/  reference_divider; int /*<<< orphan*/  signal_type; int /*<<< orphan*/  encoder_object_id; int /*<<< orphan*/  target_pixel_clock; int /*<<< orphan*/  controller_id; int /*<<< orphan*/  member_0; } ;
struct TYPE_11__ {TYPE_3__* funcs; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* set_pixel_clock ) (TYPE_5__*,struct bp_pixel_clock_parameters*) ;} ;
struct TYPE_7__ {int dce_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  BP_RESULT_OK ; 
 scalar_t__ CLOCK_SOURCE_ID_DP_DTO ; 
 scalar_t__ CLOCK_SOURCE_ID_EXTERNAL ; 
#define  DCE_VERSION_10_0 135 
#define  DCE_VERSION_11_0 134 
#define  DCE_VERSION_11_2 133 
#define  DCE_VERSION_11_22 132 
#define  DCE_VERSION_12_0 131 
#define  DCE_VERSION_8_0 130 
#define  DCE_VERSION_8_1 129 
#define  DCE_VERSION_8_3 128 
 struct dce110_clk_src* TO_DCE110_CLK_SRC (struct clock_source*) ; 
 int /*<<< orphan*/  dc_is_dp_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dce110_program_pixel_clk_resync (struct dce110_clk_src*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dce112_program_pixel_clk_resync (struct dce110_clk_src*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_spread_spectrum (struct dce110_clk_src*) ; 
 int /*<<< orphan*/  enable_spread_spectrum (struct dce110_clk_src*,int /*<<< orphan*/ ,struct pll_settings*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,struct bp_pixel_clock_parameters*) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,struct bp_pixel_clock_parameters*) ; 

__attribute__((used)) static bool dce110_program_pix_clk(
		struct clock_source *clock_source,
		struct pixel_clk_params *pix_clk_params,
		struct pll_settings *pll_settings)
{
	struct dce110_clk_src *clk_src = TO_DCE110_CLK_SRC(clock_source);
	struct bp_pixel_clock_parameters bp_pc_params = {0};

#if defined(CONFIG_DRM_AMD_DC_DCN1_0)
	if (IS_FPGA_MAXIMUS_DC(clock_source->ctx->dce_environment)) {
		unsigned int inst = pix_clk_params->controller_id - CONTROLLER_ID_D0;
		unsigned dp_dto_ref_kHz = 700000;
		unsigned clock_kHz = pll_settings->actual_pix_clk;

		/* Set DTO values: phase = target clock, modulo = reference clock */
		REG_WRITE(PHASE[inst], clock_kHz);
		REG_WRITE(MODULO[inst], dp_dto_ref_kHz);

		/* Enable DTO */
		REG_UPDATE(PIXEL_RATE_CNTL[inst], DP_DTO0_ENABLE, 1);
		return true;
	}
#endif
	/* First disable SS
	 * ATOMBIOS will enable by default SS on PLL for DP,
	 * do not disable it here
	 */
	if (clock_source->id != CLOCK_SOURCE_ID_EXTERNAL &&
			!dc_is_dp_signal(pix_clk_params->signal_type) &&
			clock_source->ctx->dce_version <= DCE_VERSION_11_0)
		disable_spread_spectrum(clk_src);

	/*ATOMBIOS expects pixel rate adjusted by deep color ratio)*/
	bp_pc_params.controller_id = pix_clk_params->controller_id;
	bp_pc_params.pll_id = clock_source->id;
	bp_pc_params.target_pixel_clock = pll_settings->actual_pix_clk;
	bp_pc_params.encoder_object_id = pix_clk_params->encoder_object_id;
	bp_pc_params.signal_type = pix_clk_params->signal_type;

	switch (clock_source->ctx->dce_version) {
	case DCE_VERSION_8_0:
	case DCE_VERSION_8_1:
	case DCE_VERSION_8_3:
	case DCE_VERSION_10_0:
	case DCE_VERSION_11_0:
		bp_pc_params.reference_divider = pll_settings->reference_divider;
		bp_pc_params.feedback_divider = pll_settings->feedback_divider;
		bp_pc_params.fractional_feedback_divider =
				pll_settings->fract_feedback_divider;
		bp_pc_params.pixel_clock_post_divider =
				pll_settings->pix_clk_post_divider;
		bp_pc_params.flags.SET_EXTERNAL_REF_DIV_SRC =
						pll_settings->use_external_clk;

		if (clk_src->bios->funcs->set_pixel_clock(
				clk_src->bios, &bp_pc_params) != BP_RESULT_OK)
			return false;
		/* Enable SS
		 * ATOMBIOS will enable by default SS for DP on PLL ( DP ID clock),
		 * based on HW display PLL team, SS control settings should be programmed
		 * during PLL Reset, but they do not have effect
		 * until SS_EN is asserted.*/
		if (clock_source->id != CLOCK_SOURCE_ID_EXTERNAL
				&& !dc_is_dp_signal(pix_clk_params->signal_type)) {

			if (pix_clk_params->flags.ENABLE_SS)
				if (!enable_spread_spectrum(clk_src,
								pix_clk_params->signal_type,
								pll_settings))
					return false;

			/* Resync deep color DTO */
			dce110_program_pixel_clk_resync(clk_src,
						pix_clk_params->signal_type,
						pix_clk_params->color_depth);
		}

		break;
	case DCE_VERSION_11_2:
	case DCE_VERSION_11_22:
	case DCE_VERSION_12_0:
#if defined(CONFIG_DRM_AMD_DC_DCN1_0)
	case DCN_VERSION_1_0:
#endif

		if (clock_source->id != CLOCK_SOURCE_ID_DP_DTO) {
			bp_pc_params.flags.SET_GENLOCK_REF_DIV_SRC =
							pll_settings->use_external_clk;
			bp_pc_params.flags.SET_XTALIN_REF_SRC =
							!pll_settings->use_external_clk;
			if (pix_clk_params->flags.SUPPORT_YCBCR420) {
				bp_pc_params.flags.SUPPORT_YUV_420 = 1;
			}
		}
		if (clk_src->bios->funcs->set_pixel_clock(
				clk_src->bios, &bp_pc_params) != BP_RESULT_OK)
			return false;
		/* Resync deep color DTO */
		if (clock_source->id != CLOCK_SOURCE_ID_DP_DTO)
			dce112_program_pixel_clk_resync(clk_src,
						pix_clk_params->signal_type,
						pix_clk_params->color_depth,
						pix_clk_params->flags.SUPPORT_YCBCR420);
		break;
	default:
		break;
	}

	return true;
}