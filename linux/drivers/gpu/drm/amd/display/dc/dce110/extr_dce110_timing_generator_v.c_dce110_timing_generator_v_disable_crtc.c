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
 int /*<<< orphan*/  CRTC_DISABLE_POINT_CNTL ; 
 int /*<<< orphan*/  CRTC_MASTER_EN ; 
 int /*<<< orphan*/  dm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCRTCV_CONTROL ; 
 int /*<<< orphan*/  set_reg_field_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool dce110_timing_generator_v_disable_crtc(struct timing_generator *tg)
{
	uint32_t value;

	value = dm_read_reg(tg->ctx,
			mmCRTCV_CONTROL);
	set_reg_field_value(value, 0,
			CRTCV_CONTROL, CRTC_DISABLE_POINT_CNTL);
	set_reg_field_value(value, 0,
				CRTCV_CONTROL, CRTC_MASTER_EN);
	dm_write_reg(tg->ctx,
			mmCRTCV_CONTROL, value);
	/*
	 * TODO: call this when adding stereo support
	 * tg->funcs->disable_stereo(tg);
	 */
	return true;
}