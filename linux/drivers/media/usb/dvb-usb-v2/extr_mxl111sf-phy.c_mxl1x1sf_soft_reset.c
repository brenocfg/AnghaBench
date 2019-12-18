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
struct mxl111sf_state {int dummy; } ;

/* Variables and functions */
 int mxl111sf_write_reg (struct mxl111sf_state*,int,int) ; 
 int /*<<< orphan*/  mxl_debug (char*) ; 
 scalar_t__ mxl_fail (int) ; 

int mxl1x1sf_soft_reset(struct mxl111sf_state *state)
{
	int ret;
	mxl_debug("()");

	ret = mxl111sf_write_reg(state, 0xff, 0x00); /* AIC */
	if (mxl_fail(ret))
		goto fail;
	ret = mxl111sf_write_reg(state, 0x02, 0x01); /* get out of reset */
	mxl_fail(ret);
fail:
	return ret;
}