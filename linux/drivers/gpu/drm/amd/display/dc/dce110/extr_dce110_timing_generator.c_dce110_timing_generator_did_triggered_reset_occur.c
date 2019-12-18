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
 int /*<<< orphan*/  CRTC_FORCE_COUNT_NOW_CNTL ; 
 int /*<<< orphan*/  CRTC_FORCE_COUNT_NOW_OCCURRED ; 
 int /*<<< orphan*/  CRTC_FORCE_VSYNC_NEXT_LINE_OCCURRED ; 
 int /*<<< orphan*/  CRTC_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRTC_VERT_SYNC_CONTROL ; 
 struct dce110_timing_generator* DCE110TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  dm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_reg_field_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCRTC_FORCE_COUNT_NOW_CNTL ; 
 int /*<<< orphan*/  mmCRTC_VERT_SYNC_CONTROL ; 

bool dce110_timing_generator_did_triggered_reset_occur(
	struct timing_generator *tg)
{
	struct dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uint32_t value = dm_read_reg(tg->ctx,
			CRTC_REG(mmCRTC_FORCE_COUNT_NOW_CNTL));
	uint32_t value1 = dm_read_reg(tg->ctx,
			CRTC_REG(mmCRTC_VERT_SYNC_CONTROL));
	bool force = get_reg_field_value(value,
					 CRTC_FORCE_COUNT_NOW_CNTL,
					 CRTC_FORCE_COUNT_NOW_OCCURRED) != 0;
	bool vert_sync = get_reg_field_value(value1,
					     CRTC_VERT_SYNC_CONTROL,
					     CRTC_FORCE_VSYNC_NEXT_LINE_OCCURRED) != 0;

	return (force || vert_sync);
}