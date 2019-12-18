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
typedef  int /*<<< orphan*/  uint8_t ;
struct timing_generator {TYPE_1__* funcs; } ;
struct optc {int dummy; } ;
struct drr_params {scalar_t__ vertical_total_max; scalar_t__ vertical_total_min; scalar_t__ vertical_total_mid; scalar_t__ vertical_total_mid_frame_num; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* setup_manual_trigger ) (struct timing_generator*) ;} ;

/* Variables and functions */
 struct optc* DCN10TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  OTG_FORCE_LOCK_ON_EVENT ; 
 int /*<<< orphan*/  OTG_SET_V_TOTAL_MIN_MASK ; 
 int /*<<< orphan*/  OTG_SET_V_TOTAL_MIN_MASK_EN ; 
 int /*<<< orphan*/  OTG_VTOTAL_MID_FRAME_NUM ; 
 int /*<<< orphan*/  OTG_VTOTAL_MID_REPLACING_MAX_EN ; 
 int /*<<< orphan*/  OTG_V_TOTAL_CONTROL ; 
 int /*<<< orphan*/  OTG_V_TOTAL_MAX ; 
 int /*<<< orphan*/  OTG_V_TOTAL_MAX_SEL ; 
 int /*<<< orphan*/  OTG_V_TOTAL_MID ; 
 int /*<<< orphan*/  OTG_V_TOTAL_MIN ; 
 int /*<<< orphan*/  OTG_V_TOTAL_MIN_SEL ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE_5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct timing_generator*) ; 

void optc1_set_drr(
	struct timing_generator *optc,
	const struct drr_params *params)
{
	struct optc *optc1 = DCN10TG_FROM_TG(optc);

	if (params != NULL &&
		params->vertical_total_max > 0 &&
		params->vertical_total_min > 0) {

		if (params->vertical_total_mid != 0) {

			REG_SET(OTG_V_TOTAL_MID, 0,
				OTG_V_TOTAL_MID, params->vertical_total_mid - 1);

			REG_UPDATE_2(OTG_V_TOTAL_CONTROL,
					OTG_VTOTAL_MID_REPLACING_MAX_EN, 1,
					OTG_VTOTAL_MID_FRAME_NUM,
					(uint8_t)params->vertical_total_mid_frame_num);

		}

		REG_SET(OTG_V_TOTAL_MAX, 0,
			OTG_V_TOTAL_MAX, params->vertical_total_max - 1);

		REG_SET(OTG_V_TOTAL_MIN, 0,
			OTG_V_TOTAL_MIN, params->vertical_total_min - 1);

		REG_UPDATE_5(OTG_V_TOTAL_CONTROL,
				OTG_V_TOTAL_MIN_SEL, 1,
				OTG_V_TOTAL_MAX_SEL, 1,
				OTG_FORCE_LOCK_ON_EVENT, 0,
				OTG_SET_V_TOTAL_MIN_MASK_EN, 0,
				OTG_SET_V_TOTAL_MIN_MASK, 0);

		// Setup manual flow control for EOF via TRIG_A
		optc->funcs->setup_manual_trigger(optc);

	} else {
		REG_UPDATE_4(OTG_V_TOTAL_CONTROL,
				OTG_SET_V_TOTAL_MIN_MASK, 0,
				OTG_V_TOTAL_MIN_SEL, 0,
				OTG_V_TOTAL_MAX_SEL, 0,
				OTG_FORCE_LOCK_ON_EVENT, 0);

		REG_SET(OTG_V_TOTAL_MIN, 0,
			OTG_V_TOTAL_MIN, 0);

		REG_SET(OTG_V_TOTAL_MAX, 0,
			OTG_V_TOTAL_MAX, 0);
	}
}