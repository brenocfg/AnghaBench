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
struct dce110_timing_generator {int dummy; } ;
struct TYPE_2__ {scalar_t__ HORZ_COUNT_BY_TWO; } ;
struct dc_crtc_timing {TYPE_1__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC_COUNT_CONTROL ; 
 int /*<<< orphan*/  CRTC_HORZ_COUNT_BY2_EN ; 
 int /*<<< orphan*/  CRTC_REG (int /*<<< orphan*/ ) ; 
 struct dce110_timing_generator* DCE110TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  dm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCRTC_COUNT_CONTROL ; 
 int /*<<< orphan*/  set_reg_field_value (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void program_horz_count_by_2(
	struct timing_generator *tg,
	const struct dc_crtc_timing *timing)
{
	uint32_t regval;
	struct dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	regval = dm_read_reg(tg->ctx,
			CRTC_REG(mmCRTC_COUNT_CONTROL));

	set_reg_field_value(regval, 0, CRTC_COUNT_CONTROL,
			CRTC_HORZ_COUNT_BY2_EN);

	if (timing->flags.HORZ_COUNT_BY_TWO)
		set_reg_field_value(regval, 1, CRTC_COUNT_CONTROL,
					CRTC_HORZ_COUNT_BY2_EN);

	dm_write_reg(tg->ctx,
			CRTC_REG(mmCRTC_COUNT_CONTROL), regval);
}