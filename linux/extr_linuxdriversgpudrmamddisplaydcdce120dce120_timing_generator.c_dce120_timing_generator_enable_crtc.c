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
struct timing_generator {TYPE_2__* bp; } ;
struct dce110_timing_generator {int /*<<< orphan*/  controller_id; } ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;
struct TYPE_4__ {TYPE_1__* funcs; } ;
struct TYPE_3__ {int (* enable_crtc ) (TYPE_2__*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int BP_RESULT_OK ; 
 int /*<<< orphan*/  CRTC0_CRTC_MASTER_UPDATE_LOCK ; 
 int /*<<< orphan*/  CRTC0_CRTC_MASTER_UPDATE_MODE ; 
 int /*<<< orphan*/  CRTC_REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dce110_timing_generator* DCE110TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  MASTER_UPDATE_MODE ; 
 int /*<<< orphan*/  UNDERFLOW_UPDATE_LOCK ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

bool dce120_timing_generator_enable_crtc(struct timing_generator *tg)
{
	enum bp_result result;
	struct dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	/* Set MASTER_UPDATE_MODE to 0
	 * This is needed for DRR, and also suggested to be default value by Syed.*/

	CRTC_REG_UPDATE(CRTC0_CRTC_MASTER_UPDATE_MODE,
			MASTER_UPDATE_MODE, 0);

	CRTC_REG_UPDATE(CRTC0_CRTC_MASTER_UPDATE_LOCK,
			UNDERFLOW_UPDATE_LOCK, 0);

	/* TODO API for AtomFirmware didn't change*/
	result = tg->bp->funcs->enable_crtc(tg->bp, tg110->controller_id, true);

	return result == BP_RESULT_OK;
}