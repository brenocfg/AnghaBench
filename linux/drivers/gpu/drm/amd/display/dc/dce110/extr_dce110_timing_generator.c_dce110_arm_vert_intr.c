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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
struct timing_generator {int /*<<< orphan*/  ctx; TYPE_1__* funcs; } ;
struct dce110_timing_generator {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_scanoutpos ) (struct timing_generator*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRTC_VERTICAL_INTERRUPT0_LINE_END ; 
 int /*<<< orphan*/  CRTC_VERTICAL_INTERRUPT0_LINE_START ; 
 int /*<<< orphan*/  CRTC_VERTICAL_INTERRUPT0_POSITION ; 
 struct dce110_timing_generator* DCE110TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mmCRTC_VERTICAL_INTERRUPT0_POSITION ; 
 int /*<<< orphan*/  set_reg_field_value (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct timing_generator*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 

bool dce110_arm_vert_intr(struct timing_generator *tg, uint8_t width)
{
	struct dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uint32_t v_blank_start = 0;
	uint32_t v_blank_end = 0;
	uint32_t val = 0;
	uint32_t h_position, v_position;

	tg->funcs->get_scanoutpos(
			tg,
			&v_blank_start,
			&v_blank_end,
			&h_position,
			&v_position);

	if (v_blank_start == 0 || v_blank_end == 0)
		return false;

	set_reg_field_value(
		val,
		v_blank_start,
		CRTC_VERTICAL_INTERRUPT0_POSITION,
		CRTC_VERTICAL_INTERRUPT0_LINE_START);

	/* Set interval width for interrupt to fire to 1 scanline */
	set_reg_field_value(
		val,
		v_blank_start + width,
		CRTC_VERTICAL_INTERRUPT0_POSITION,
		CRTC_VERTICAL_INTERRUPT0_LINE_END);

	dm_write_reg(tg->ctx, CRTC_REG(mmCRTC_VERTICAL_INTERRUPT0_POSITION), val);

	return true;
}