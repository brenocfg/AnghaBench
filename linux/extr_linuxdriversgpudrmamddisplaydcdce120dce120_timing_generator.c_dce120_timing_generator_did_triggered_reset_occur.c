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
typedef  int /*<<< orphan*/  uint32_t ;
struct timing_generator {int /*<<< orphan*/  ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  crtc; } ;
struct dce110_timing_generator {TYPE_1__ offsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC0_CRTC_FORCE_COUNT_NOW_CNTL ; 
 int /*<<< orphan*/  CRTC_FORCE_COUNT_NOW_OCCURRED ; 
 struct dce110_timing_generator* DCE110TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  dm_read_reg_soc15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_reg_field_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCRTC0_CRTC_FORCE_COUNT_NOW_CNTL ; 

bool dce120_timing_generator_did_triggered_reset_occur(
	struct timing_generator *tg)
{
	struct dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uint32_t value = dm_read_reg_soc15(
			tg->ctx,
			mmCRTC0_CRTC_FORCE_COUNT_NOW_CNTL,
			tg110->offsets.crtc);

	return get_reg_field_value(value,
			CRTC0_CRTC_FORCE_COUNT_NOW_CNTL,
			CRTC_FORCE_COUNT_NOW_OCCURRED) != 0;
}