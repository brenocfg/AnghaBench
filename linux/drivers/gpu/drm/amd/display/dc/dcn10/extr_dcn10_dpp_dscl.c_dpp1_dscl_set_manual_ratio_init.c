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
typedef  int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  v_c_bot; int /*<<< orphan*/  v_c; int /*<<< orphan*/  v_bot; int /*<<< orphan*/  v; int /*<<< orphan*/  h_c; int /*<<< orphan*/  h; } ;
struct TYPE_3__ {int /*<<< orphan*/  vert_c; int /*<<< orphan*/  horz_c; int /*<<< orphan*/  vert; int /*<<< orphan*/  horz; } ;
struct scaler_data {TYPE_2__ inits; TYPE_1__ ratios; } ;
struct dcn10_dpp {int dummy; } ;

/* Variables and functions */
 scalar_t__ REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SCL_HORZ_FILTER_INIT ; 
 int /*<<< orphan*/  SCL_HORZ_FILTER_INIT_C ; 
 int /*<<< orphan*/  SCL_HORZ_FILTER_SCALE_RATIO ; 
 int /*<<< orphan*/  SCL_HORZ_FILTER_SCALE_RATIO_C ; 
 int /*<<< orphan*/  SCL_H_INIT_FRAC ; 
 int /*<<< orphan*/  SCL_H_INIT_FRAC_C ; 
 int /*<<< orphan*/  SCL_H_INIT_INT ; 
 int /*<<< orphan*/  SCL_H_INIT_INT_C ; 
 int /*<<< orphan*/  SCL_H_SCALE_RATIO ; 
 int /*<<< orphan*/  SCL_H_SCALE_RATIO_C ; 
 int /*<<< orphan*/  SCL_VERT_FILTER_INIT ; 
 int /*<<< orphan*/  SCL_VERT_FILTER_INIT_BOT ; 
 int /*<<< orphan*/  SCL_VERT_FILTER_INIT_BOT_C ; 
 int /*<<< orphan*/  SCL_VERT_FILTER_INIT_C ; 
 int /*<<< orphan*/  SCL_VERT_FILTER_SCALE_RATIO ; 
 int /*<<< orphan*/  SCL_VERT_FILTER_SCALE_RATIO_C ; 
 int /*<<< orphan*/  SCL_V_INIT_FRAC ; 
 int /*<<< orphan*/  SCL_V_INIT_FRAC_BOT ; 
 int /*<<< orphan*/  SCL_V_INIT_FRAC_BOT_C ; 
 int /*<<< orphan*/  SCL_V_INIT_FRAC_C ; 
 int /*<<< orphan*/  SCL_V_INIT_INT ; 
 int /*<<< orphan*/  SCL_V_INIT_INT_BOT ; 
 int /*<<< orphan*/  SCL_V_INIT_INT_BOT_C ; 
 int /*<<< orphan*/  SCL_V_INIT_INT_C ; 
 int /*<<< orphan*/  SCL_V_SCALE_RATIO ; 
 int /*<<< orphan*/  SCL_V_SCALE_RATIO_C ; 
 int dc_fixpt_floor (int /*<<< orphan*/ ) ; 
 int dc_fixpt_u0d19 (int /*<<< orphan*/ ) ; 
 int dc_fixpt_u3d19 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dpp1_dscl_set_manual_ratio_init(
		struct dcn10_dpp *dpp, const struct scaler_data *data)
{
	uint32_t init_frac = 0;
	uint32_t init_int = 0;

	REG_SET(SCL_HORZ_FILTER_SCALE_RATIO, 0,
			SCL_H_SCALE_RATIO, dc_fixpt_u3d19(data->ratios.horz) << 5);

	REG_SET(SCL_VERT_FILTER_SCALE_RATIO, 0,
			SCL_V_SCALE_RATIO, dc_fixpt_u3d19(data->ratios.vert) << 5);

	REG_SET(SCL_HORZ_FILTER_SCALE_RATIO_C, 0,
			SCL_H_SCALE_RATIO_C, dc_fixpt_u3d19(data->ratios.horz_c) << 5);

	REG_SET(SCL_VERT_FILTER_SCALE_RATIO_C, 0,
			SCL_V_SCALE_RATIO_C, dc_fixpt_u3d19(data->ratios.vert_c) << 5);

	/*
	 * 0.24 format for fraction, first five bits zeroed
	 */
	init_frac = dc_fixpt_u0d19(data->inits.h) << 5;
	init_int = dc_fixpt_floor(data->inits.h);
	REG_SET_2(SCL_HORZ_FILTER_INIT, 0,
		SCL_H_INIT_FRAC, init_frac,
		SCL_H_INIT_INT, init_int);

	init_frac = dc_fixpt_u0d19(data->inits.h_c) << 5;
	init_int = dc_fixpt_floor(data->inits.h_c);
	REG_SET_2(SCL_HORZ_FILTER_INIT_C, 0,
		SCL_H_INIT_FRAC_C, init_frac,
		SCL_H_INIT_INT_C, init_int);

	init_frac = dc_fixpt_u0d19(data->inits.v) << 5;
	init_int = dc_fixpt_floor(data->inits.v);
	REG_SET_2(SCL_VERT_FILTER_INIT, 0,
		SCL_V_INIT_FRAC, init_frac,
		SCL_V_INIT_INT, init_int);

	if (REG(SCL_VERT_FILTER_INIT_BOT)) {
		init_frac = dc_fixpt_u0d19(data->inits.v_bot) << 5;
		init_int = dc_fixpt_floor(data->inits.v_bot);
		REG_SET_2(SCL_VERT_FILTER_INIT_BOT, 0,
			SCL_V_INIT_FRAC_BOT, init_frac,
			SCL_V_INIT_INT_BOT, init_int);
	}

	init_frac = dc_fixpt_u0d19(data->inits.v_c) << 5;
	init_int = dc_fixpt_floor(data->inits.v_c);
	REG_SET_2(SCL_VERT_FILTER_INIT_C, 0,
		SCL_V_INIT_FRAC_C, init_frac,
		SCL_V_INIT_INT_C, init_int);

	if (REG(SCL_VERT_FILTER_INIT_BOT_C)) {
		init_frac = dc_fixpt_u0d19(data->inits.v_c_bot) << 5;
		init_int = dc_fixpt_floor(data->inits.v_c_bot);
		REG_SET_2(SCL_VERT_FILTER_INIT_BOT_C, 0,
			SCL_V_INIT_FRAC_BOT_C, init_frac,
			SCL_V_INIT_INT_BOT_C, init_int);
	}
}