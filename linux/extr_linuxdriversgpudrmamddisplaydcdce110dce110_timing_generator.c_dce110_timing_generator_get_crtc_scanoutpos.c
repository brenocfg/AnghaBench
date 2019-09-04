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
struct crtc_position {int /*<<< orphan*/  vertical_count; int /*<<< orphan*/  horizontal_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRTC_V_BLANK_END ; 
 int /*<<< orphan*/  CRTC_V_BLANK_START ; 
 int /*<<< orphan*/  CRTC_V_BLANK_START_END ; 
 struct dce110_timing_generator* DCE110TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  dce110_timing_generator_get_position (struct timing_generator*,struct crtc_position*) ; 
 int /*<<< orphan*/  dm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_reg_field_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCRTC_V_BLANK_START_END ; 

void dce110_timing_generator_get_crtc_scanoutpos(
	struct timing_generator *tg,
	uint32_t *v_blank_start,
	uint32_t *v_blank_end,
	uint32_t *h_position,
	uint32_t *v_position)
{
	struct dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	struct crtc_position position;

	uint32_t value  = dm_read_reg(tg->ctx,
			CRTC_REG(mmCRTC_V_BLANK_START_END));

	*v_blank_start = get_reg_field_value(value,
					     CRTC_V_BLANK_START_END,
					     CRTC_V_BLANK_START);
	*v_blank_end = get_reg_field_value(value,
					   CRTC_V_BLANK_START_END,
					   CRTC_V_BLANK_END);

	dce110_timing_generator_get_position(
			tg, &position);

	*h_position = position.horizontal_count;
	*v_position = position.vertical_count;
}