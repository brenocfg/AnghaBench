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
 int mxl111sf_write_reg_mask (struct mxl111sf_state*,int,int,int) ; 
 int /*<<< orphan*/  mxl_debug (char*) ; 

int mxl111sf_enable_usb_output(struct mxl111sf_state *state)
{
	mxl_debug("()");

	return mxl111sf_write_reg_mask(state, 0x17, 0x40, 0x00);
}