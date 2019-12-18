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
struct timing_generator {int /*<<< orphan*/  ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  crtc; } ;
struct dce110_timing_generator {TYPE_1__ offsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC0_CRTC_BLANK_CONTROL ; 
 int /*<<< orphan*/  CRTC0_CRTC_DOUBLE_BUFFER_CONTROL ; 
 int /*<<< orphan*/  CRTC_BLANK_DATA_DOUBLE_BUFFER_EN ; 
 int /*<<< orphan*/  CRTC_BLANK_DATA_EN ; 
 int /*<<< orphan*/  CRTC_REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dce110_timing_generator* DCE110TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  dm_write_reg_soc15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCRTC0_CRTC_BLANK_CONTROL ; 

void dce120_tg_set_blank(struct timing_generator *tg,
		bool enable_blanking)
{
	struct dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	CRTC_REG_SET(
		CRTC0_CRTC_DOUBLE_BUFFER_CONTROL,
		CRTC_BLANK_DATA_DOUBLE_BUFFER_EN, 1);

	if (enable_blanking)
		CRTC_REG_SET(CRTC0_CRTC_BLANK_CONTROL, CRTC_BLANK_DATA_EN, 1);
	else
		dm_write_reg_soc15(tg->ctx, mmCRTC0_CRTC_BLANK_CONTROL,
			tg110->offsets.crtc, 0);
}