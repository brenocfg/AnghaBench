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
 int /*<<< orphan*/  CRTCV_CONTROL ; 
 int /*<<< orphan*/  CRTC_HBLANK_EARLY_CONTROL ; 
 int /*<<< orphan*/  dm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCRTC_CONTROL ; 
 int /*<<< orphan*/  set_reg_field_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dce110_timing_generator_v_set_early_control(
		struct timing_generator *tg,
		uint32_t early_cntl)
{
	uint32_t regval;
	uint32_t address = mmCRTC_CONTROL;

	regval = dm_read_reg(tg->ctx, address);
	set_reg_field_value(regval, early_cntl,
			CRTCV_CONTROL, CRTC_HBLANK_EARLY_CONTROL);
	dm_write_reg(tg->ctx, address, regval);
}