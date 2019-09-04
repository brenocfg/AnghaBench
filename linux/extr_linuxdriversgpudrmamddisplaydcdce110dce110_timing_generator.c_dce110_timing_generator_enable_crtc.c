#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct timing_generator {TYPE_2__* bp; int /*<<< orphan*/  ctx; } ;
struct dce110_timing_generator {int /*<<< orphan*/  controller_id; } ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;
struct TYPE_4__ {TYPE_1__* funcs; } ;
struct TYPE_3__ {int (* enable_crtc ) (TYPE_2__*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int BP_RESULT_OK ; 
 int /*<<< orphan*/  CRTC_MASTER_UPDATE_MODE ; 
 int /*<<< orphan*/  CRTC_REG (int /*<<< orphan*/ ) ; 
 struct dce110_timing_generator* DCE110TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  MASTER_UPDATE_MODE ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mmCRTC_MASTER_UPDATE_LOCK ; 
 int /*<<< orphan*/  mmCRTC_MASTER_UPDATE_MODE ; 
 int /*<<< orphan*/  set_reg_field_value (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

bool dce110_timing_generator_enable_crtc(struct timing_generator *tg)
{
	enum bp_result result;

	struct dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uint32_t value = 0;

	/*
	 * 3 is used to make sure V_UPDATE occurs at the beginning of the first
	 * line of vertical front porch
	 */
	set_reg_field_value(
		value,
		0,
		CRTC_MASTER_UPDATE_MODE,
		MASTER_UPDATE_MODE);

	dm_write_reg(tg->ctx, CRTC_REG(mmCRTC_MASTER_UPDATE_MODE), value);

	/* TODO: may want this on to catch underflow */
	value = 0;
	dm_write_reg(tg->ctx, CRTC_REG(mmCRTC_MASTER_UPDATE_LOCK), value);

	result = tg->bp->funcs->enable_crtc(tg->bp, tg110->controller_id, true);

	return result == BP_RESULT_OK;
}