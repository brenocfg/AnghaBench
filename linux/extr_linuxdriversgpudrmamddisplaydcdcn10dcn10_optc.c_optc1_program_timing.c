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
typedef  int uint32_t ;
struct TYPE_4__ {int vstartup_start; scalar_t__ signal; } ;
struct timing_generator {TYPE_2__ dlg_otg_param; } ;
struct optc {int dummy; } ;
struct TYPE_3__ {int INTERLACE; scalar_t__ VSYNC_POSITIVE_POLARITY; scalar_t__ HSYNC_POSITIVE_POLARITY; } ;
struct dc_crtc_timing {int h_total; int h_sync_width; int h_addressable; int h_border_right; int h_front_porch; int h_border_left; int v_total; int v_sync_width; int v_addressable; int v_border_bottom; int v_front_porch; int v_border_top; scalar_t__ pixel_encoding; TYPE_1__ flags; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONTROL ; 
 struct optc* DCN10TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  OTG_CONTROL ; 
 int /*<<< orphan*/  OTG_FIELD_NUMBER_CNTL ; 
 int /*<<< orphan*/  OTG_H_BLANK_END ; 
 int /*<<< orphan*/  OTG_H_BLANK_START ; 
 int /*<<< orphan*/  OTG_H_BLANK_START_END ; 
 int /*<<< orphan*/  OTG_H_SYNC_A ; 
 int /*<<< orphan*/  OTG_H_SYNC_A_CNTL ; 
 int /*<<< orphan*/  OTG_H_SYNC_A_END ; 
 int /*<<< orphan*/  OTG_H_SYNC_A_POL ; 
 int /*<<< orphan*/  OTG_H_SYNC_A_START ; 
 int /*<<< orphan*/  OTG_H_TIMING_CNTL ; 
 int /*<<< orphan*/  OTG_H_TIMING_DIV_BY2 ; 
 int /*<<< orphan*/  OTG_H_TOTAL ; 
 int /*<<< orphan*/  OTG_INTERLACE_CONTROL ; 
 int /*<<< orphan*/  OTG_INTERLACE_ENABLE ; 
 int /*<<< orphan*/  OTG_START_POINT_CNTL ; 
 int /*<<< orphan*/  OTG_VERTICAL_INTERRUPT2_LINE_START ; 
 int /*<<< orphan*/  OTG_VERTICAL_INTERRUPT2_POSITION ; 
 int /*<<< orphan*/  OTG_V_BLANK_END ; 
 int /*<<< orphan*/  OTG_V_BLANK_START ; 
 int /*<<< orphan*/  OTG_V_BLANK_START_END ; 
 int /*<<< orphan*/  OTG_V_SYNC_A ; 
 int /*<<< orphan*/  OTG_V_SYNC_A_CNTL ; 
 int /*<<< orphan*/  OTG_V_SYNC_A_END ; 
 int /*<<< orphan*/  OTG_V_SYNC_A_POL ; 
 int /*<<< orphan*/  OTG_V_SYNC_A_START ; 
 int /*<<< orphan*/  OTG_V_TOTAL ; 
 int /*<<< orphan*/  OTG_V_TOTAL_MAX ; 
 int /*<<< orphan*/  OTG_V_TOTAL_MIN ; 
 scalar_t__ PIXEL_ENCODING_YCBCR420 ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ SIGNAL_TYPE_DISPLAY_PORT ; 
 scalar_t__ SIGNAL_TYPE_DISPLAY_PORT_MST ; 
 scalar_t__ SIGNAL_TYPE_EDP ; 
 int /*<<< orphan*/  VTG0_ENABLE ; 
 int /*<<< orphan*/  VTG0_FP2 ; 
 int /*<<< orphan*/  VTG0_VCOUNT_INIT ; 
 int /*<<< orphan*/  optc1_apply_front_porch_workaround (struct timing_generator*,struct dc_crtc_timing*) ; 
 int /*<<< orphan*/  optc1_program_global_sync (struct timing_generator*) ; 

void optc1_program_timing(
	struct timing_generator *optc,
	const struct dc_crtc_timing *dc_crtc_timing,
	bool use_vbios)
{
	struct dc_crtc_timing patched_crtc_timing;
	uint32_t vesa_sync_start;
	uint32_t asic_blank_end;
	uint32_t asic_blank_start;
	uint32_t v_total;
	uint32_t v_sync_end;
	uint32_t v_init, v_fp2;
	uint32_t h_sync_polarity, v_sync_polarity;
	uint32_t interlace_factor;
	uint32_t start_point = 0;
	uint32_t field_num = 0;
	uint32_t h_div_2;
	int32_t vertical_line_start;

	struct optc *optc1 = DCN10TG_FROM_TG(optc);

	patched_crtc_timing = *dc_crtc_timing;
	optc1_apply_front_porch_workaround(optc, &patched_crtc_timing);

	/* Load horizontal timing */

	/* CRTC_H_TOTAL = vesa.h_total - 1 */
	REG_SET(OTG_H_TOTAL, 0,
			OTG_H_TOTAL,  patched_crtc_timing.h_total - 1);

	/* h_sync_start = 0, h_sync_end = vesa.h_sync_width */
	REG_UPDATE_2(OTG_H_SYNC_A,
			OTG_H_SYNC_A_START, 0,
			OTG_H_SYNC_A_END, patched_crtc_timing.h_sync_width);

	/* asic_h_blank_end = HsyncWidth + HbackPorch =
	 * vesa. usHorizontalTotal - vesa. usHorizontalSyncStart -
	 * vesa.h_left_border
	 */
	vesa_sync_start = patched_crtc_timing.h_addressable +
			patched_crtc_timing.h_border_right +
			patched_crtc_timing.h_front_porch;

	asic_blank_end = patched_crtc_timing.h_total -
			vesa_sync_start -
			patched_crtc_timing.h_border_left;

	/* h_blank_start = v_blank_end + v_active */
	asic_blank_start = asic_blank_end +
			patched_crtc_timing.h_border_left +
			patched_crtc_timing.h_addressable +
			patched_crtc_timing.h_border_right;

	REG_UPDATE_2(OTG_H_BLANK_START_END,
			OTG_H_BLANK_START, asic_blank_start,
			OTG_H_BLANK_END, asic_blank_end);

	/* h_sync polarity */
	h_sync_polarity = patched_crtc_timing.flags.HSYNC_POSITIVE_POLARITY ?
			0 : 1;

	REG_UPDATE(OTG_H_SYNC_A_CNTL,
			OTG_H_SYNC_A_POL, h_sync_polarity);

	/* Load vertical timing */

	/* CRTC_V_TOTAL = v_total - 1 */
	if (patched_crtc_timing.flags.INTERLACE) {
		interlace_factor = 2;
		v_total = 2 * patched_crtc_timing.v_total;
	} else {
		interlace_factor = 1;
		v_total = patched_crtc_timing.v_total - 1;
	}
	REG_SET(OTG_V_TOTAL, 0,
			OTG_V_TOTAL, v_total);

	/* In case of V_TOTAL_CONTROL is on, make sure OTG_V_TOTAL_MAX and
	 * OTG_V_TOTAL_MIN are equal to V_TOTAL.
	 */
	REG_SET(OTG_V_TOTAL_MAX, 0,
		OTG_V_TOTAL_MAX, v_total);
	REG_SET(OTG_V_TOTAL_MIN, 0,
		OTG_V_TOTAL_MIN, v_total);

	/* v_sync_start = 0, v_sync_end = v_sync_width */
	v_sync_end = patched_crtc_timing.v_sync_width * interlace_factor;

	REG_UPDATE_2(OTG_V_SYNC_A,
			OTG_V_SYNC_A_START, 0,
			OTG_V_SYNC_A_END, v_sync_end);

	vesa_sync_start = patched_crtc_timing.v_addressable +
			patched_crtc_timing.v_border_bottom +
			patched_crtc_timing.v_front_porch;

	asic_blank_end = (patched_crtc_timing.v_total -
			vesa_sync_start -
			patched_crtc_timing.v_border_top)
			* interlace_factor;

	/* v_blank_start = v_blank_end + v_active */
	asic_blank_start = asic_blank_end +
			(patched_crtc_timing.v_border_top +
			patched_crtc_timing.v_addressable +
			patched_crtc_timing.v_border_bottom)
			* interlace_factor;

	REG_UPDATE_2(OTG_V_BLANK_START_END,
			OTG_V_BLANK_START, asic_blank_start,
			OTG_V_BLANK_END, asic_blank_end);

	/* Use OTG_VERTICAL_INTERRUPT2 replace VUPDATE interrupt,
	 * program the reg for interrupt postition.
	 */
	vertical_line_start = asic_blank_end - optc->dlg_otg_param.vstartup_start + 1;
	if (vertical_line_start < 0) {
		ASSERT(0);
		vertical_line_start = 0;
	}
	REG_SET(OTG_VERTICAL_INTERRUPT2_POSITION, 0,
			OTG_VERTICAL_INTERRUPT2_LINE_START, vertical_line_start);

	/* v_sync polarity */
	v_sync_polarity = patched_crtc_timing.flags.VSYNC_POSITIVE_POLARITY ?
			0 : 1;

	REG_UPDATE(OTG_V_SYNC_A_CNTL,
			OTG_V_SYNC_A_POL, v_sync_polarity);

	v_init = asic_blank_start;
	if (optc->dlg_otg_param.signal == SIGNAL_TYPE_DISPLAY_PORT ||
		optc->dlg_otg_param.signal == SIGNAL_TYPE_DISPLAY_PORT_MST ||
		optc->dlg_otg_param.signal == SIGNAL_TYPE_EDP) {
		start_point = 1;
		if (patched_crtc_timing.flags.INTERLACE == 1)
			field_num = 1;
	}
	v_fp2 = 0;
	if (optc->dlg_otg_param.vstartup_start > asic_blank_end)
		v_fp2 = optc->dlg_otg_param.vstartup_start > asic_blank_end;

	/* Interlace */
	if (patched_crtc_timing.flags.INTERLACE == 1) {
		REG_UPDATE(OTG_INTERLACE_CONTROL,
				OTG_INTERLACE_ENABLE, 1);
		v_init = v_init / 2;
		if ((optc->dlg_otg_param.vstartup_start/2)*2 > asic_blank_end)
			v_fp2 = v_fp2 / 2;
	} else
		REG_UPDATE(OTG_INTERLACE_CONTROL,
				OTG_INTERLACE_ENABLE, 0);


	/* VTG enable set to 0 first VInit */
	REG_UPDATE(CONTROL,
			VTG0_ENABLE, 0);

	REG_UPDATE_2(CONTROL,
			VTG0_FP2, v_fp2,
			VTG0_VCOUNT_INIT, v_init);

	/* original code is using VTG offset to address OTG reg, seems wrong */
	REG_UPDATE_2(OTG_CONTROL,
			OTG_START_POINT_CNTL, start_point,
			OTG_FIELD_NUMBER_CNTL, field_num);

	optc1_program_global_sync(optc);

	/* TODO
	 * patched_crtc_timing.flags.HORZ_COUNT_BY_TWO == 1
	 * program_horz_count_by_2
	 * for DVI 30bpp mode, 0 otherwise
	 * program_horz_count_by_2(optc, &patched_crtc_timing);
	 */

	/* Enable stereo - only when we need to pack 3D frame. Other types
	 * of stereo handled in explicit call
	 */
	h_div_2 = (dc_crtc_timing->pixel_encoding == PIXEL_ENCODING_YCBCR420) ?
			1 : 0;

	REG_UPDATE(OTG_H_TIMING_CNTL,
			OTG_H_TIMING_DIV_BY2, h_div_2);

}