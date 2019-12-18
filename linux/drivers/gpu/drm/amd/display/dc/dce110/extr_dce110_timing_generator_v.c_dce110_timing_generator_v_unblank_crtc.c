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
 int /*<<< orphan*/  CRTCV_BLANK_CONTROL ; 
 int /*<<< orphan*/  CRTC_BLANK_DATA_EN ; 
 int /*<<< orphan*/  CRTC_BLANK_DE_MODE ; 
 int /*<<< orphan*/  dm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCRTCV_BLANK_CONTROL ; 
 int /*<<< orphan*/  set_reg_field_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dce110_timing_generator_v_unblank_crtc(struct timing_generator *tg)
{
	uint32_t addr = mmCRTCV_BLANK_CONTROL;
	uint32_t value = dm_read_reg(tg->ctx, addr);

	set_reg_field_value(
		value,
		0,
		CRTCV_BLANK_CONTROL,
		CRTC_BLANK_DATA_EN);

	set_reg_field_value(
		value,
		0,
		CRTCV_BLANK_CONTROL,
		CRTC_BLANK_DE_MODE);

	dm_write_reg(tg->ctx, addr, value);
}