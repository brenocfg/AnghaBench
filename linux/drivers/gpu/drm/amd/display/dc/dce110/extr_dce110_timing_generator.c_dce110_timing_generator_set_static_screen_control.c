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

/* Variables and functions */
 int CRTC_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRTC_STATIC_SCREEN_CONTROL ; 
 int /*<<< orphan*/  CRTC_STATIC_SCREEN_EVENT_MASK ; 
 int /*<<< orphan*/  CRTC_STATIC_SCREEN_FRAME_COUNT ; 
 struct dce110_timing_generator* DCE110TG_FROM_TG (struct timing_generator*) ; 
 int dm_read_reg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mmCRTC_STATIC_SCREEN_CONTROL ; 
 int /*<<< orphan*/  set_reg_field_value (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dce110_timing_generator_set_static_screen_control(
	struct timing_generator *tg,
	uint32_t value)
{
	struct dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uint32_t static_screen_cntl = 0;
	uint32_t addr = 0;

	addr = CRTC_REG(mmCRTC_STATIC_SCREEN_CONTROL);
	static_screen_cntl = dm_read_reg(tg->ctx, addr);

	set_reg_field_value(static_screen_cntl,
				value,
				CRTC_STATIC_SCREEN_CONTROL,
				CRTC_STATIC_SCREEN_EVENT_MASK);

	set_reg_field_value(static_screen_cntl,
				2,
				CRTC_STATIC_SCREEN_CONTROL,
				CRTC_STATIC_SCREEN_FRAME_COUNT);

	dm_write_reg(tg->ctx, addr, static_screen_cntl);
}