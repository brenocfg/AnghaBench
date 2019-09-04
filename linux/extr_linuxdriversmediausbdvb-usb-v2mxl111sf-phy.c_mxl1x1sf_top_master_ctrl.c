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
 int /*<<< orphan*/  mxl_debug (char*,int) ; 

int mxl1x1sf_top_master_ctrl(struct mxl111sf_state *state, int onoff)
{
	mxl_debug("(%d)", onoff);

	return mxl111sf_write_reg(state, 0x01, onoff ? 0x01 : 0x00);
}