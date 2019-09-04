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
struct dce110_timing_generator {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC_AUTO_FORCE_VSYNC_MODE ; 
 int /*<<< orphan*/  CRTC_FORCE_COUNT_NOW_CLEAR ; 
 int /*<<< orphan*/  CRTC_FORCE_COUNT_NOW_CNTL ; 
 int /*<<< orphan*/  CRTC_FORCE_COUNT_NOW_MODE ; 
 int /*<<< orphan*/  CRTC_FORCE_VSYNC_NEXT_LINE_CLEAR ; 
 int /*<<< orphan*/  CRTC_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRTC_TRIGB_CLEAR ; 
 int /*<<< orphan*/  CRTC_TRIGB_CNTL ; 
 int /*<<< orphan*/  CRTC_TRIGB_POLARITY_SELECT ; 
 int /*<<< orphan*/  CRTC_TRIGB_SOURCE_SELECT ; 
 int /*<<< orphan*/  CRTC_VERT_SYNC_CONTROL ; 
 struct dce110_timing_generator* DCE110TG_FROM_TG (struct timing_generator*) ; 
 int TRIGGER_POLARITY_SELECT_LOGIC_ZERO ; 
 int TRIGGER_SOURCE_SELECT_LOGIC_ZERO ; 
 int /*<<< orphan*/  dm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCRTC_FORCE_COUNT_NOW_CNTL ; 
 int /*<<< orphan*/  mmCRTC_TRIGB_CNTL ; 
 int /*<<< orphan*/  mmCRTC_VERT_SYNC_CONTROL ; 
 int /*<<< orphan*/  set_reg_field_value (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dce110_timing_generator_disable_reset_trigger(
	struct timing_generator *tg)
{
	uint32_t value;
	struct dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	value = dm_read_reg(tg->ctx, CRTC_REG(mmCRTC_FORCE_COUNT_NOW_CNTL));

	set_reg_field_value(value,
			    0, /* force counter now mode is disabled */
			    CRTC_FORCE_COUNT_NOW_CNTL,
			    CRTC_FORCE_COUNT_NOW_MODE);

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
			    0,
			    CRTC_VERT_SYNC_CONTROL,
			    CRTC_AUTO_FORCE_VSYNC_MODE);

	dm_write_reg(tg->ctx, CRTC_REG(mmCRTC_VERT_SYNC_CONTROL), value);

	/********************************************************************/
	value = dm_read_reg(tg->ctx, CRTC_REG(mmCRTC_TRIGB_CNTL));

	set_reg_field_value(value,
			    TRIGGER_SOURCE_SELECT_LOGIC_ZERO,
			    CRTC_TRIGB_CNTL,
			    CRTC_TRIGB_SOURCE_SELECT);

	set_reg_field_value(value,
			    TRIGGER_POLARITY_SELECT_LOGIC_ZERO,
			    CRTC_TRIGB_CNTL,
			    CRTC_TRIGB_POLARITY_SELECT);

	set_reg_field_value(value,
			    1, /* clear trigger status */
			    CRTC_TRIGB_CNTL,
			    CRTC_TRIGB_CLEAR);

	dm_write_reg(tg->ctx, CRTC_REG(mmCRTC_TRIGB_CNTL), value);
}