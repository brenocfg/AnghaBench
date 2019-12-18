#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct timing_generator {struct dc_context* ctx; } ;
struct tg_color {int /*<<< orphan*/  color_g_y; int /*<<< orphan*/  color_r_cr; int /*<<< orphan*/  color_b_cb; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC_OVERSCAN_COLOR ; 
 int /*<<< orphan*/  CRTC_OVERSCAN_COLOR_BLUE ; 
 int /*<<< orphan*/  CRTC_OVERSCAN_COLOR_GREEN ; 
 int /*<<< orphan*/  CRTC_OVERSCAN_COLOR_RED ; 
 int /*<<< orphan*/  dm_write_reg (struct dc_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCRTCV_BLACK_COLOR ; 
 int /*<<< orphan*/  mmCRTCV_BLANK_DATA_COLOR ; 
 int /*<<< orphan*/  mmCRTCV_OVERSCAN_COLOR ; 
 int /*<<< orphan*/  set_reg_field_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dce110_timing_generator_v_set_overscan_color_black(
	struct timing_generator *tg,
	const struct tg_color *color)
{
	struct dc_context *ctx = tg->ctx;
	uint32_t addr;
	uint32_t value = 0;

	set_reg_field_value(
			value,
			color->color_b_cb,
			CRTC_OVERSCAN_COLOR,
			CRTC_OVERSCAN_COLOR_BLUE);

	set_reg_field_value(
			value,
			color->color_r_cr,
			CRTC_OVERSCAN_COLOR,
			CRTC_OVERSCAN_COLOR_RED);

	set_reg_field_value(
			value,
			color->color_g_y,
			CRTC_OVERSCAN_COLOR,
			CRTC_OVERSCAN_COLOR_GREEN);

	addr = mmCRTCV_OVERSCAN_COLOR;
	dm_write_reg(ctx, addr, value);
	addr = mmCRTCV_BLACK_COLOR;
	dm_write_reg(ctx, addr, value);
	/* This is desirable to have a constant DAC output voltage during the
	 * blank time that is higher than the 0 volt reference level that the
	 * DAC outputs when the NBLANK signal
	 * is asserted low, such as for output to an analog TV. */
	addr = mmCRTCV_BLANK_DATA_COLOR;
	dm_write_reg(ctx, addr, value);

	/* TO DO we have to program EXT registers and we need to know LB DATA
	 * format because it is used when more 10 , i.e. 12 bits per color
	 *
	 * m_mmDxCRTC_OVERSCAN_COLOR_EXT
	 * m_mmDxCRTC_BLACK_COLOR_EXT
	 * m_mmDxCRTC_BLANK_DATA_COLOR_EXT
	 */
}