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
typedef  int uint32_t ;
struct timing_generator {int /*<<< orphan*/  ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  crtc; } ;
struct dce110_timing_generator {TYPE_1__ offsets; } ;
struct dc_crtc_timing {int v_total; int v_addressable; int v_border_bottom; int v_front_porch; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC0_CRTC_START_LINE_CONTROL ; 
 int /*<<< orphan*/  CRTC_ADVANCED_START_LINE_POSITION ; 
 int /*<<< orphan*/  CRTC_LEGACY_REQUESTOR_EN ; 
 struct dce110_timing_generator* DCE110TG_FROM_TG (struct timing_generator*) ; 
 int dm_read_reg_soc15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_write_reg_soc15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmCRTC0_CRTC_START_LINE_CONTROL ; 
 int /*<<< orphan*/  set_reg_field_value (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dce120_timing_generator_enable_advanced_request(
	struct timing_generator *tg,
	bool enable,
	const struct dc_crtc_timing *timing)
{
	struct dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uint32_t v_sync_width_and_b_porch =
				timing->v_total - timing->v_addressable -
				timing->v_border_bottom - timing->v_front_porch;
	uint32_t value = dm_read_reg_soc15(
				tg->ctx,
				mmCRTC0_CRTC_START_LINE_CONTROL,
				tg110->offsets.crtc);

	set_reg_field_value(
		value,
		enable ? 0 : 1,
		CRTC0_CRTC_START_LINE_CONTROL,
		CRTC_LEGACY_REQUESTOR_EN);

	/* Program advanced line position acc.to the best case from fetching data perspective to hide MC latency
	 * and prefilling Line Buffer in V Blank (to 10 lines as LB can store max 10 lines)
	 */
	if (v_sync_width_and_b_porch > 10)
		v_sync_width_and_b_porch = 10;

	set_reg_field_value(
		value,
		v_sync_width_and_b_porch,
		CRTC0_CRTC_START_LINE_CONTROL,
		CRTC_ADVANCED_START_LINE_POSITION);

	dm_write_reg_soc15(tg->ctx,
			mmCRTC0_CRTC_START_LINE_CONTROL,
			tg110->offsets.crtc,
			value);
}