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
struct tg_color {int /*<<< orphan*/  color_r_cr; int /*<<< orphan*/  color_g_y; int /*<<< orphan*/  color_b_cb; } ;
struct dce110_timing_generator {int dummy; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC_OVERSCAN_COLOR ; 
 int /*<<< orphan*/  CRTC_OVERSCAN_COLOR_BLUE ; 
 int /*<<< orphan*/  CRTC_OVERSCAN_COLOR_GREEN ; 
 int /*<<< orphan*/  CRTC_OVERSCAN_COLOR_RED ; 
 int /*<<< orphan*/  CRTC_REG (int /*<<< orphan*/ ) ; 
 struct dce110_timing_generator* DCE110TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  dm_write_reg (struct dc_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCRTC_OVERSCAN_COLOR ; 
 int /*<<< orphan*/  set_reg_field_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dce110_tg_set_overscan_color(struct timing_generator *tg,
	const struct tg_color *overscan_color)
{
	struct dc_context *ctx = tg->ctx;
	uint32_t value = 0;
	uint32_t addr;
	struct dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	set_reg_field_value(
		value,
		overscan_color->color_b_cb,
		CRTC_OVERSCAN_COLOR,
		CRTC_OVERSCAN_COLOR_BLUE);

	set_reg_field_value(
		value,
		overscan_color->color_g_y,
		CRTC_OVERSCAN_COLOR,
		CRTC_OVERSCAN_COLOR_GREEN);

	set_reg_field_value(
		value,
		overscan_color->color_r_cr,
		CRTC_OVERSCAN_COLOR,
		CRTC_OVERSCAN_COLOR_RED);

	addr = CRTC_REG(mmCRTC_OVERSCAN_COLOR);
	dm_write_reg(ctx, addr, value);
}