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
typedef  int uint32_t ;
struct timing_generator {int /*<<< orphan*/  ctx; } ;
struct dce110_timing_generator {int dummy; } ;
struct crtc_trigger_info {int event; int delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC_AUTO_FORCE_VSYNC_MODE ; 
#define  CRTC_EVENT_VSYNC_FALLING 131 
#define  CRTC_EVENT_VSYNC_RISING 130 
 int /*<<< orphan*/  CRTC_FORCE_COUNT_NOW_CLEAR ; 
 int /*<<< orphan*/  CRTC_FORCE_COUNT_NOW_CNTL ; 
 int /*<<< orphan*/  CRTC_FORCE_COUNT_NOW_MODE ; 
 int /*<<< orphan*/  CRTC_FORCE_COUNT_NOW_TRIG_SEL ; 
 int /*<<< orphan*/  CRTC_FORCE_VSYNC_NEXT_LINE_CLEAR ; 
 int /*<<< orphan*/  CRTC_MASTER_UPDATE_MODE ; 
 int /*<<< orphan*/  CRTC_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRTC_TRIGB_CLEAR ; 
 int /*<<< orphan*/  CRTC_TRIGB_CNTL ; 
 int /*<<< orphan*/  CRTC_TRIGB_FALLING_EDGE_DETECT_CNTL ; 
 int /*<<< orphan*/  CRTC_TRIGB_POLARITY_SELECT ; 
 int /*<<< orphan*/  CRTC_TRIGB_RISING_EDGE_DETECT_CNTL ; 
 int /*<<< orphan*/  CRTC_TRIGB_SOURCE_SELECT ; 
 int /*<<< orphan*/  CRTC_VERT_SYNC_CONTROL ; 
 struct dce110_timing_generator* DCE110TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  MASTER_UPDATE_MODE ; 
#define  TRIGGER_DELAY_NEXT_LINE 129 
#define  TRIGGER_DELAY_NEXT_PIXEL 128 
 int TRIGGER_POLARITY_SELECT_LOGIC_ZERO ; 
 int dm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmCRTC_FORCE_COUNT_NOW_CNTL ; 
 int /*<<< orphan*/  mmCRTC_MASTER_UPDATE_MODE ; 
 int /*<<< orphan*/  mmCRTC_TRIGB_CNTL ; 
 int /*<<< orphan*/  mmCRTC_VERT_SYNC_CONTROL ; 
 int /*<<< orphan*/  set_reg_field_value (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dce110_timing_generator_enable_crtc_reset(
		struct timing_generator *tg,
		int source_tg_inst,
		struct crtc_trigger_info *crtc_tp)
{
	uint32_t value = 0;
	uint32_t rising_edge = 0;
	uint32_t falling_edge = 0;
	struct dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	/* Setup trigger edge */
	switch (crtc_tp->event) {
	case CRTC_EVENT_VSYNC_RISING:
			rising_edge = 1;
			break;

	case CRTC_EVENT_VSYNC_FALLING:
		falling_edge = 1;
		break;
	}

	value = dm_read_reg(tg->ctx, CRTC_REG(mmCRTC_TRIGB_CNTL));

	set_reg_field_value(value,
			    source_tg_inst,
			    CRTC_TRIGB_CNTL,
			    CRTC_TRIGB_SOURCE_SELECT);

	set_reg_field_value(value,
			    TRIGGER_POLARITY_SELECT_LOGIC_ZERO,
			    CRTC_TRIGB_CNTL,
			    CRTC_TRIGB_POLARITY_SELECT);

	set_reg_field_value(value,
			    rising_edge,
			    CRTC_TRIGB_CNTL,
			    CRTC_TRIGB_RISING_EDGE_DETECT_CNTL);

	set_reg_field_value(value,
			    falling_edge,
			    CRTC_TRIGB_CNTL,
			    CRTC_TRIGB_FALLING_EDGE_DETECT_CNTL);

	set_reg_field_value(value,
			    1, /* clear trigger status */
			    CRTC_TRIGB_CNTL,
			    CRTC_TRIGB_CLEAR);

	dm_write_reg(tg->ctx, CRTC_REG(mmCRTC_TRIGB_CNTL), value);

	/**************************************************************/

	switch (crtc_tp->delay) {
	case TRIGGER_DELAY_NEXT_LINE:
		value = dm_read_reg(tg->ctx, CRTC_REG(mmCRTC_FORCE_COUNT_NOW_CNTL));

		set_reg_field_value(value,
				    0, /* force H count to H_TOTAL and V count to V_TOTAL */
				    CRTC_FORCE_COUNT_NOW_CNTL,
				    CRTC_FORCE_COUNT_NOW_MODE);

		set_reg_field_value(value,
				    0, /* TriggerB - we never use TriggerA */
				    CRTC_FORCE_COUNT_NOW_CNTL,
				    CRTC_FORCE_COUNT_NOW_TRIG_SEL);

		set_reg_field_value(value,
				    1, /* clear trigger status */
				    CRTC_FORCE_COUNT_NOW_CNTL,
				    CRTC_FORCE_COUNT_NOW_CLEAR);

		dm_write_reg(tg->ctx, CRTC_REG(mmCRTC_FORCE_COUNT_NOW_CNTL), value);

		value = dm_read_reg(tg->ctx, CRTC_REG(mmCRTC_VERT_SYNC_CONTROL));

		set_reg_field_value(value,
				    1,
				    CRTC_VERT_SYNC_CONTROL,
				    CRTC_FORCE_VSYNC_NEXT_LINE_CLEAR);

		set_reg_field_value(value,
				    2,
				    CRTC_VERT_SYNC_CONTROL,
				    CRTC_AUTO_FORCE_VSYNC_MODE);

		break;

	case TRIGGER_DELAY_NEXT_PIXEL:
		value = dm_read_reg(tg->ctx, CRTC_REG(mmCRTC_VERT_SYNC_CONTROL));

		set_reg_field_value(value,
				    1,
				    CRTC_VERT_SYNC_CONTROL,
				    CRTC_FORCE_VSYNC_NEXT_LINE_CLEAR);

		set_reg_field_value(value,
				    0,
				    CRTC_VERT_SYNC_CONTROL,
				    CRTC_AUTO_FORCE_VSYNC_MODE);

		dm_write_reg(tg->ctx, CRTC_REG(mmCRTC_VERT_SYNC_CONTROL), value);

		value = dm_read_reg(tg->ctx, CRTC_REG(mmCRTC_FORCE_COUNT_NOW_CNTL));

		set_reg_field_value(value,
				    2, /* force H count to H_TOTAL and V count to V_TOTAL */
				    CRTC_FORCE_COUNT_NOW_CNTL,
				    CRTC_FORCE_COUNT_NOW_MODE);

		set_reg_field_value(value,
				    1, /* TriggerB - we never use TriggerA */
				    CRTC_FORCE_COUNT_NOW_CNTL,
				    CRTC_FORCE_COUNT_NOW_TRIG_SEL);

		set_reg_field_value(value,
				    1, /* clear trigger status */
				    CRTC_FORCE_COUNT_NOW_CNTL,
				    CRTC_FORCE_COUNT_NOW_CLEAR);

		dm_write_reg(tg->ctx, CRTC_REG(mmCRTC_FORCE_COUNT_NOW_CNTL), value);
		break;
	}

	value = dm_read_reg(tg->ctx, CRTC_REG(mmCRTC_MASTER_UPDATE_MODE));

	set_reg_field_value(value,
			    2,
			    CRTC_MASTER_UPDATE_MODE,
			    MASTER_UPDATE_MODE);

	dm_write_reg(tg->ctx, CRTC_REG(mmCRTC_MASTER_UPDATE_MODE), value);
}