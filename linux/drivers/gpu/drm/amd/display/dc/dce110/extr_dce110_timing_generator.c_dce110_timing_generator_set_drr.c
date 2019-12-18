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
struct drr_params {scalar_t__ vertical_total_max; scalar_t__ vertical_total_min; } ;
struct dce110_timing_generator {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC_FORCE_LOCK_ON_EVENT ; 
 int /*<<< orphan*/  CRTC_FORCE_LOCK_TO_MASTER_VSYNC ; 
 int /*<<< orphan*/  CRTC_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRTC_SET_V_TOTAL_MIN_MASK ; 
 int /*<<< orphan*/  CRTC_SET_V_TOTAL_MIN_MASK_EN ; 
 int /*<<< orphan*/  CRTC_V_TOTAL_CONTROL ; 
 int /*<<< orphan*/  CRTC_V_TOTAL_MAX ; 
 int /*<<< orphan*/  CRTC_V_TOTAL_MAX_SEL ; 
 int /*<<< orphan*/  CRTC_V_TOTAL_MIN ; 
 int /*<<< orphan*/  CRTC_V_TOTAL_MIN_SEL ; 
 struct dce110_timing_generator* DCE110TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  dm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCRTC_V_TOTAL_CONTROL ; 
 int /*<<< orphan*/  mmCRTC_V_TOTAL_MAX ; 
 int /*<<< orphan*/  mmCRTC_V_TOTAL_MIN ; 
 int /*<<< orphan*/  set_reg_field_value (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dce110_timing_generator_set_drr(
	struct timing_generator *tg,
	const struct drr_params *params)
{
	/* register values */
	uint32_t v_total_min = 0;
	uint32_t v_total_max = 0;
	uint32_t v_total_cntl = 0;
	struct dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	uint32_t addr = 0;

	addr = CRTC_REG(mmCRTC_V_TOTAL_MIN);
	v_total_min = dm_read_reg(tg->ctx, addr);

	addr = CRTC_REG(mmCRTC_V_TOTAL_MAX);
	v_total_max = dm_read_reg(tg->ctx, addr);

	addr = CRTC_REG(mmCRTC_V_TOTAL_CONTROL);
	v_total_cntl = dm_read_reg(tg->ctx, addr);

	if (params != NULL &&
		params->vertical_total_max > 0 &&
		params->vertical_total_min > 0) {

		set_reg_field_value(v_total_max,
				params->vertical_total_max - 1,
				CRTC_V_TOTAL_MAX,
				CRTC_V_TOTAL_MAX);

		set_reg_field_value(v_total_min,
				params->vertical_total_min - 1,
				CRTC_V_TOTAL_MIN,
				CRTC_V_TOTAL_MIN);

		set_reg_field_value(v_total_cntl,
				1,
				CRTC_V_TOTAL_CONTROL,
				CRTC_V_TOTAL_MIN_SEL);

		set_reg_field_value(v_total_cntl,
				1,
				CRTC_V_TOTAL_CONTROL,
				CRTC_V_TOTAL_MAX_SEL);

		set_reg_field_value(v_total_cntl,
				0,
				CRTC_V_TOTAL_CONTROL,
				CRTC_FORCE_LOCK_ON_EVENT);
		set_reg_field_value(v_total_cntl,
				0,
				CRTC_V_TOTAL_CONTROL,
				CRTC_FORCE_LOCK_TO_MASTER_VSYNC);

		set_reg_field_value(v_total_cntl,
				0,
				CRTC_V_TOTAL_CONTROL,
				CRTC_SET_V_TOTAL_MIN_MASK_EN);

		set_reg_field_value(v_total_cntl,
				0,
				CRTC_V_TOTAL_CONTROL,
				CRTC_SET_V_TOTAL_MIN_MASK);
	} else {
		set_reg_field_value(v_total_cntl,
			0,
			CRTC_V_TOTAL_CONTROL,
			CRTC_SET_V_TOTAL_MIN_MASK);
		set_reg_field_value(v_total_cntl,
				0,
				CRTC_V_TOTAL_CONTROL,
				CRTC_V_TOTAL_MIN_SEL);
		set_reg_field_value(v_total_cntl,
				0,
				CRTC_V_TOTAL_CONTROL,
				CRTC_V_TOTAL_MAX_SEL);
		set_reg_field_value(v_total_min,
				0,
				CRTC_V_TOTAL_MIN,
				CRTC_V_TOTAL_MIN);
		set_reg_field_value(v_total_max,
				0,
				CRTC_V_TOTAL_MAX,
				CRTC_V_TOTAL_MAX);
		set_reg_field_value(v_total_cntl,
				0,
				CRTC_V_TOTAL_CONTROL,
				CRTC_FORCE_LOCK_ON_EVENT);
		set_reg_field_value(v_total_cntl,
				0,
				CRTC_V_TOTAL_CONTROL,
				CRTC_FORCE_LOCK_TO_MASTER_VSYNC);
	}

	addr = CRTC_REG(mmCRTC_V_TOTAL_MIN);
	dm_write_reg(tg->ctx, addr, v_total_min);

	addr = CRTC_REG(mmCRTC_V_TOTAL_MAX);
	dm_write_reg(tg->ctx, addr, v_total_max);

	addr = CRTC_REG(mmCRTC_V_TOTAL_CONTROL);
	dm_write_reg(tg->ctx, addr, v_total_cntl);
}