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
struct TYPE_3__ {int h_taps; int v_taps; } ;
struct scaler_data {scalar_t__ format; TYPE_1__ taps; } ;
struct dce_transform {TYPE_2__* xfm_mask; } ;
struct TYPE_4__ {scalar_t__ SCL_PSCL_EN; } ;

/* Variables and functions */
 scalar_t__ PIXEL_FORMAT_GRPH_END ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCL_BOUNDARY_MODE ; 
 int /*<<< orphan*/  SCL_BYPASS_CONTROL ; 
 int /*<<< orphan*/  SCL_BYPASS_MODE ; 
 int /*<<< orphan*/  SCL_CONTROL ; 
 int /*<<< orphan*/  SCL_H_NUM_OF_TAPS ; 
 int /*<<< orphan*/  SCL_MODE ; 
 int /*<<< orphan*/  SCL_PSCL_EN ; 
 int /*<<< orphan*/  SCL_TAP_CONTROL ; 
 int /*<<< orphan*/  SCL_V_NUM_OF_TAPS ; 

__attribute__((used)) static bool setup_scaling_configuration(
	struct dce_transform *xfm_dce,
	const struct scaler_data *data)
{
	REG_SET(SCL_BYPASS_CONTROL, 0, SCL_BYPASS_MODE, 0);

	if (data->taps.h_taps + data->taps.v_taps <= 2) {
		/* Set bypass */
		if (xfm_dce->xfm_mask->SCL_PSCL_EN != 0)
			REG_UPDATE_2(SCL_MODE, SCL_MODE, 0, SCL_PSCL_EN, 0);
		else
			REG_UPDATE(SCL_MODE, SCL_MODE, 0);
		return false;
	}

	REG_SET_2(SCL_TAP_CONTROL, 0,
			SCL_H_NUM_OF_TAPS, data->taps.h_taps - 1,
			SCL_V_NUM_OF_TAPS, data->taps.v_taps - 1);

	if (data->format <= PIXEL_FORMAT_GRPH_END)
		REG_UPDATE(SCL_MODE, SCL_MODE, 1);
	else
		REG_UPDATE(SCL_MODE, SCL_MODE, 2);

	if (xfm_dce->xfm_mask->SCL_PSCL_EN != 0)
		REG_UPDATE(SCL_MODE, SCL_PSCL_EN, 1);

	/* 1 - Replace out of bound pixels with edge */
	REG_SET(SCL_CONTROL, 0, SCL_BOUNDARY_MODE, 1);

	return true;
}