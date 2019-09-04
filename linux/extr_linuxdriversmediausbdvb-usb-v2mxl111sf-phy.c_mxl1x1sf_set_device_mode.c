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
struct mxl111sf_state {int device_mode; } ;

/* Variables and functions */
 int MXL_SOC_MODE ; 
 int mxl111sf_write_reg (struct mxl111sf_state*,int,int) ; 
 int mxl111sf_write_reg_mask (struct mxl111sf_state*,int,int,int) ; 
 int /*<<< orphan*/  mxl_debug (char*,char*) ; 
 scalar_t__ mxl_fail (int) ; 

int mxl1x1sf_set_device_mode(struct mxl111sf_state *state, int mode)
{
	int ret;

	mxl_debug("(%s)", MXL_SOC_MODE == mode ?
		"MXL_SOC_MODE" : "MXL_TUNER_MODE");

	/* set device mode */
	ret = mxl111sf_write_reg(state, 0x03,
				 MXL_SOC_MODE == mode ? 0x01 : 0x00);
	if (mxl_fail(ret))
		goto fail;

	ret = mxl111sf_write_reg_mask(state,
				      0x7d, 0x40, MXL_SOC_MODE == mode ?
				      0x00 : /* enable impulse noise filter,
						INF_BYP = 0 */
				      0x40); /* disable impulse noise filter,
						INF_BYP = 1 */
	if (mxl_fail(ret))
		goto fail;

	state->device_mode = mode;
fail:
	return ret;
}