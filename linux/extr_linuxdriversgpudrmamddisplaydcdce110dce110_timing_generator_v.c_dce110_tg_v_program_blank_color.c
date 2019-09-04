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
struct timing_generator {int /*<<< orphan*/  ctx; } ;
struct tg_color {int /*<<< orphan*/  color_r_cr; int /*<<< orphan*/  color_g_y; int /*<<< orphan*/  color_b_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTCV_BLACK_COLOR ; 
 int /*<<< orphan*/  CRTC_BLACK_COLOR_B_CB ; 
 int /*<<< orphan*/  CRTC_BLACK_COLOR_G_Y ; 
 int /*<<< orphan*/  CRTC_BLACK_COLOR_R_CR ; 
 int /*<<< orphan*/  dm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCRTCV_BLACK_COLOR ; 
 int /*<<< orphan*/  mmCRTCV_BLANK_DATA_COLOR ; 
 int /*<<< orphan*/  set_reg_field_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dce110_tg_v_program_blank_color(struct timing_generator *tg,
		const struct tg_color *black_color)
{
	uint32_t addr = mmCRTCV_BLACK_COLOR;
	uint32_t value = dm_read_reg(tg->ctx, addr);

	set_reg_field_value(
		value,
		black_color->color_b_cb,
		CRTCV_BLACK_COLOR,
		CRTC_BLACK_COLOR_B_CB);
	set_reg_field_value(
		value,
		black_color->color_g_y,
		CRTCV_BLACK_COLOR,
		CRTC_BLACK_COLOR_G_Y);
	set_reg_field_value(
		value,
		black_color->color_r_cr,
		CRTCV_BLACK_COLOR,
		CRTC_BLACK_COLOR_R_CR);

	dm_write_reg(tg->ctx, addr, value);

	addr = mmCRTCV_BLANK_DATA_COLOR;
	dm_write_reg(tg->ctx, addr, value);
}