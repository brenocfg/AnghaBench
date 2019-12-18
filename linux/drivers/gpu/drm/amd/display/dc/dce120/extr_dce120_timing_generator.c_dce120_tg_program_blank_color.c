#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct timing_generator {int /*<<< orphan*/  ctx; } ;
struct tg_color {int /*<<< orphan*/  color_r_cr; int /*<<< orphan*/  color_g_y; int /*<<< orphan*/  color_b_cb; } ;
struct TYPE_2__ {int /*<<< orphan*/  crtc; } ;
struct dce110_timing_generator {TYPE_1__ offsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC0_CRTC_BLACK_COLOR ; 
 int /*<<< orphan*/  CRTC_BLACK_COLOR_B_CB ; 
 int /*<<< orphan*/  CRTC_BLACK_COLOR_G_Y ; 
 int /*<<< orphan*/  CRTC_BLACK_COLOR_R_CR ; 
 int /*<<< orphan*/  CRTC_REG_UPDATE_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dce110_timing_generator* DCE110TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  dm_read_reg_soc15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_write_reg_soc15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCRTC0_CRTC_BLACK_COLOR ; 
 int /*<<< orphan*/  mmCRTC0_CRTC_BLANK_DATA_COLOR ; 

void dce120_tg_program_blank_color(struct timing_generator *tg,
	const struct tg_color *black_color)
{
	struct dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uint32_t value = 0;

	CRTC_REG_UPDATE_3(
		CRTC0_CRTC_BLACK_COLOR,
		CRTC_BLACK_COLOR_B_CB, black_color->color_b_cb,
		CRTC_BLACK_COLOR_G_Y, black_color->color_g_y,
		CRTC_BLACK_COLOR_R_CR, black_color->color_r_cr);

	value = dm_read_reg_soc15(
				tg->ctx,
				mmCRTC0_CRTC_BLACK_COLOR,
				tg110->offsets.crtc);
	dm_write_reg_soc15(
		tg->ctx,
		mmCRTC0_CRTC_BLANK_DATA_COLOR,
		tg110->offsets.crtc,
		value);
}