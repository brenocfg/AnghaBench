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
 int /*<<< orphan*/  CRTC_FRAME_COUNT ; 
 int /*<<< orphan*/  CRTC_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRTC_STATUS_FRAME_COUNT ; 
 struct dce110_timing_generator* DCE110TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  dm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_reg_field_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCRTC_STATUS_FRAME_COUNT ; 

uint32_t dce110_timing_generator_get_vblank_counter(struct timing_generator *tg)
{
	struct dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uint32_t addr = CRTC_REG(mmCRTC_STATUS_FRAME_COUNT);
	uint32_t value = dm_read_reg(tg->ctx, addr);
	uint32_t field = get_reg_field_value(
			value, CRTC_STATUS_FRAME_COUNT, CRTC_FRAME_COUNT);

	return field;
}