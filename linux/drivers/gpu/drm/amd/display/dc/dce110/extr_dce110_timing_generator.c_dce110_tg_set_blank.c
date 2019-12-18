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
struct timing_generator {int /*<<< orphan*/  ctx; } ;
struct dce110_timing_generator {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC_BLANK_CONTROL ; 
 int /*<<< orphan*/  CRTC_BLANK_DATA_DOUBLE_BUFFER_EN ; 
 int /*<<< orphan*/  CRTC_BLANK_DATA_EN ; 
 int /*<<< orphan*/  CRTC_DOUBLE_BUFFER_CONTROL ; 
 int /*<<< orphan*/  CRTC_REG (int /*<<< orphan*/ ) ; 
 struct dce110_timing_generator* DCE110TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mmCRTC_BLANK_CONTROL ; 
 int /*<<< orphan*/  mmCRTC_DOUBLE_BUFFER_CONTROL ; 
 int /*<<< orphan*/  set_reg_field_value (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dce110_tg_set_blank(struct timing_generator *tg,
		bool enable_blanking)
{
	struct dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uint32_t value = 0;

	set_reg_field_value(
		value,
		1,
		CRTC_DOUBLE_BUFFER_CONTROL,
		CRTC_BLANK_DATA_DOUBLE_BUFFER_EN);

	dm_write_reg(tg->ctx, CRTC_REG(mmCRTC_DOUBLE_BUFFER_CONTROL), value);
	value = 0;

	if (enable_blanking) {
		set_reg_field_value(
			value,
			1,
			CRTC_BLANK_CONTROL,
			CRTC_BLANK_DATA_EN);

		dm_write_reg(tg->ctx, CRTC_REG(mmCRTC_BLANK_CONTROL), value);

	} else
		dm_write_reg(tg->ctx, CRTC_REG(mmCRTC_BLANK_CONTROL), 0);
}