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
struct TYPE_8__ {scalar_t__ h_taps_c; scalar_t__ v_taps_c; scalar_t__ h_taps; scalar_t__ v_taps; } ;
struct scaler_data {scalar_t__ format; TYPE_4__ taps; int /*<<< orphan*/  lb_params; } ;
struct dpp {TYPE_3__* ctx; } ;
struct dcn10_dpp {int dummy; } ;
typedef  enum lb_memory_config { ____Placeholder_lb_memory_config } lb_memory_config ;
typedef  enum dscl_mode_sel { ____Placeholder_dscl_mode_sel } dscl_mode_sel ;
struct TYPE_7__ {TYPE_2__* dc; } ;
struct TYPE_5__ {int /*<<< orphan*/  always_scale; } ;
struct TYPE_6__ {TYPE_1__ debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOCAL_MODE ; 
 int /*<<< orphan*/  AUTOCAL_MODE_AUTOSCALE ; 
 int /*<<< orphan*/  AUTOCAL_NUM_PIPE ; 
 int /*<<< orphan*/  AUTOCAL_PIPE_ID ; 
 int /*<<< orphan*/  BLACK_OFFSET_CBCR ; 
 int /*<<< orphan*/  BLACK_OFFSET_RGB_Y ; 
 int /*<<< orphan*/  DSCL_AUTOCAL ; 
 int /*<<< orphan*/  DSCL_MODE ; 
 int DSCL_MODE_DSCL_BYPASS ; 
 int DSCL_MODE_SCALING_444_BYPASS ; 
 scalar_t__ PIXEL_FORMAT_VIDEO_BEGIN ; 
 scalar_t__ PIXEL_FORMAT_VIDEO_END ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SCL_BLACK_OFFSET ; 
 int /*<<< orphan*/  SCL_BLACK_OFFSET_CBCR ; 
 int /*<<< orphan*/  SCL_BLACK_OFFSET_RGB_Y ; 
 int /*<<< orphan*/  SCL_H_NUM_TAPS ; 
 int /*<<< orphan*/  SCL_H_NUM_TAPS_C ; 
 int /*<<< orphan*/  SCL_MODE ; 
 int /*<<< orphan*/  SCL_TAP_CONTROL ; 
 int /*<<< orphan*/  SCL_V_NUM_TAPS ; 
 int /*<<< orphan*/  SCL_V_NUM_TAPS_C ; 
 struct dcn10_dpp* TO_DCN10_DPP (struct dpp*) ; 
 int dpp1_dscl_find_lb_memory_config (struct dcn10_dpp*,struct scaler_data const*) ; 
 int dpp1_dscl_get_dscl_mode (struct dpp*,struct scaler_data const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpp1_dscl_set_lb (struct dcn10_dpp*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dpp1_dscl_set_otg_blank (struct dcn10_dpp*,struct scaler_data const*) ; 
 int /*<<< orphan*/  dpp1_dscl_set_overscan (struct dcn10_dpp*,struct scaler_data const*) ; 
 int /*<<< orphan*/  dpp1_dscl_set_scl_filter (struct dcn10_dpp*,struct scaler_data const*,int) ; 

void dpp1_dscl_set_scaler_auto_scale(
	struct dpp *dpp_base,
	const struct scaler_data *scl_data)
{
	enum lb_memory_config lb_config;
	struct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);
	enum dscl_mode_sel dscl_mode = dpp1_dscl_get_dscl_mode(
			dpp_base, scl_data, dpp_base->ctx->dc->debug.always_scale);
	bool ycbcr = scl_data->format >= PIXEL_FORMAT_VIDEO_BEGIN
				&& scl_data->format <= PIXEL_FORMAT_VIDEO_END;

	dpp1_dscl_set_overscan(dpp, scl_data);

	dpp1_dscl_set_otg_blank(dpp, scl_data);

	REG_UPDATE(SCL_MODE, DSCL_MODE, dscl_mode);

	if (dscl_mode == DSCL_MODE_DSCL_BYPASS)
		return;

	lb_config =  dpp1_dscl_find_lb_memory_config(dpp, scl_data);
	dpp1_dscl_set_lb(dpp, &scl_data->lb_params, lb_config);

	if (dscl_mode == DSCL_MODE_SCALING_444_BYPASS)
		return;

	/* TODO: v_min */
	REG_SET_3(DSCL_AUTOCAL, 0,
		AUTOCAL_MODE, AUTOCAL_MODE_AUTOSCALE,
		AUTOCAL_NUM_PIPE, 0,
		AUTOCAL_PIPE_ID, 0);

	/* Black offsets */
	if (ycbcr)
		REG_SET_2(SCL_BLACK_OFFSET, 0,
				SCL_BLACK_OFFSET_RGB_Y, BLACK_OFFSET_RGB_Y,
				SCL_BLACK_OFFSET_CBCR, BLACK_OFFSET_CBCR);
	else

		REG_SET_2(SCL_BLACK_OFFSET, 0,
				SCL_BLACK_OFFSET_RGB_Y, BLACK_OFFSET_RGB_Y,
				SCL_BLACK_OFFSET_CBCR, BLACK_OFFSET_RGB_Y);

	REG_SET_4(SCL_TAP_CONTROL, 0,
		SCL_V_NUM_TAPS, scl_data->taps.v_taps - 1,
		SCL_H_NUM_TAPS, scl_data->taps.h_taps - 1,
		SCL_V_NUM_TAPS_C, scl_data->taps.v_taps_c - 1,
		SCL_H_NUM_TAPS_C, scl_data->taps.h_taps_c - 1);

	dpp1_dscl_set_scl_filter(dpp, scl_data, ycbcr);
}