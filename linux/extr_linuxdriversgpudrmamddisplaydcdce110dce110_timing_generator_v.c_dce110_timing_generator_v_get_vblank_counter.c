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

/* Variables and functions */
 int /*<<< orphan*/  CRTCV_STATUS_FRAME_COUNT ; 
 int /*<<< orphan*/  CRTC_FRAME_COUNT ; 
 int /*<<< orphan*/  dm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_reg_field_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCRTCV_STATUS_FRAME_COUNT ; 

__attribute__((used)) static uint32_t dce110_timing_generator_v_get_vblank_counter(struct timing_generator *tg)
{
	uint32_t addr = mmCRTCV_STATUS_FRAME_COUNT;
	uint32_t value = dm_read_reg(tg->ctx, addr);
	uint32_t field = get_reg_field_value(
			value, CRTCV_STATUS_FRAME_COUNT, CRTC_FRAME_COUNT);

	return field;
}