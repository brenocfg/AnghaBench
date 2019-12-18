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
typedef  scalar_t__ uint32_t ;
struct timing_generator {struct dc_context* ctx; } ;
struct dce110_timing_generator {int dummy; } ;
struct dc_crtc_timing {scalar_t__ v_border_bottom; scalar_t__ v_border_top; scalar_t__ v_addressable; scalar_t__ v_total; scalar_t__ h_border_right; scalar_t__ h_border_left; scalar_t__ h_addressable; scalar_t__ h_total; scalar_t__ h_front_porch; scalar_t__ v_front_porch; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC_H_BLANK_END ; 
 int /*<<< orphan*/  CRTC_H_BLANK_START ; 
 int /*<<< orphan*/  CRTC_H_BLANK_START_END ; 
 int /*<<< orphan*/  CRTC_H_TOTAL ; 
 scalar_t__ CRTC_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRTC_V_BLANK_END ; 
 int /*<<< orphan*/  CRTC_V_BLANK_START ; 
 int /*<<< orphan*/  CRTC_V_BLANK_START_END ; 
 int /*<<< orphan*/  CRTC_V_TOTAL ; 
 int /*<<< orphan*/  CRTC_V_TOTAL_MAX ; 
 int /*<<< orphan*/  CRTC_V_TOTAL_MIN ; 
 struct dce110_timing_generator* DCE110TG_FROM_TG (struct timing_generator*) ; 
 scalar_t__ dm_read_reg (struct dc_context*,scalar_t__) ; 
 int /*<<< orphan*/  dm_write_reg (struct dc_context*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mmCRTC_H_BLANK_START_END ; 
 int /*<<< orphan*/  mmCRTC_H_TOTAL ; 
 int /*<<< orphan*/  mmCRTC_V_BLANK_START_END ; 
 int /*<<< orphan*/  mmCRTC_V_TOTAL ; 
 int /*<<< orphan*/  mmCRTC_V_TOTAL_MAX ; 
 int /*<<< orphan*/  mmCRTC_V_TOTAL_MIN ; 
 int /*<<< orphan*/  set_reg_field_value (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dce110_timing_generator_program_blanking(
	struct timing_generator *tg,
	const struct dc_crtc_timing *timing)
{
	uint32_t vsync_offset = timing->v_border_bottom +
			timing->v_front_porch;
	uint32_t v_sync_start =timing->v_addressable + vsync_offset;

	uint32_t hsync_offset = timing->h_border_right +
			timing->h_front_porch;
	uint32_t h_sync_start = timing->h_addressable + hsync_offset;
	struct dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	struct dc_context *ctx = tg->ctx;
	uint32_t value = 0;
	uint32_t addr = 0;
	uint32_t tmp = 0;

	addr = CRTC_REG(mmCRTC_H_TOTAL);
	value = dm_read_reg(ctx, addr);
	set_reg_field_value(
		value,
		timing->h_total - 1,
		CRTC_H_TOTAL,
		CRTC_H_TOTAL);
	dm_write_reg(ctx, addr, value);

	addr = CRTC_REG(mmCRTC_V_TOTAL);
	value = dm_read_reg(ctx, addr);
	set_reg_field_value(
		value,
		timing->v_total - 1,
		CRTC_V_TOTAL,
		CRTC_V_TOTAL);
	dm_write_reg(ctx, addr, value);

	/* In case of V_TOTAL_CONTROL is on, make sure V_TOTAL_MAX and
	 * V_TOTAL_MIN are equal to V_TOTAL.
	 */
	addr = CRTC_REG(mmCRTC_V_TOTAL_MAX);
	value = dm_read_reg(ctx, addr);
	set_reg_field_value(
		value,
		timing->v_total - 1,
		CRTC_V_TOTAL_MAX,
		CRTC_V_TOTAL_MAX);
	dm_write_reg(ctx, addr, value);

	addr = CRTC_REG(mmCRTC_V_TOTAL_MIN);
	value = dm_read_reg(ctx, addr);
	set_reg_field_value(
		value,
		timing->v_total - 1,
		CRTC_V_TOTAL_MIN,
		CRTC_V_TOTAL_MIN);
	dm_write_reg(ctx, addr, value);

	addr = CRTC_REG(mmCRTC_H_BLANK_START_END);
	value = dm_read_reg(ctx, addr);

	tmp = timing->h_total -
		(h_sync_start + timing->h_border_left);

	set_reg_field_value(
		value,
		tmp,
		CRTC_H_BLANK_START_END,
		CRTC_H_BLANK_END);

	tmp = tmp + timing->h_addressable +
		timing->h_border_left + timing->h_border_right;

	set_reg_field_value(
		value,
		tmp,
		CRTC_H_BLANK_START_END,
		CRTC_H_BLANK_START);

	dm_write_reg(ctx, addr, value);

	addr = CRTC_REG(mmCRTC_V_BLANK_START_END);
	value = dm_read_reg(ctx, addr);

	tmp = timing->v_total - (v_sync_start + timing->v_border_top);

	set_reg_field_value(
		value,
		tmp,
		CRTC_V_BLANK_START_END,
		CRTC_V_BLANK_END);

	tmp = tmp + timing->v_addressable + timing->v_border_top +
		timing->v_border_bottom;

	set_reg_field_value(
		value,
		tmp,
		CRTC_V_BLANK_START_END,
		CRTC_V_BLANK_START);

	dm_write_reg(ctx, addr, value);
}