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
struct mxl111sf_demod_state {int dummy; } ;

/* Variables and functions */
 int mxl111sf_demod_write_reg (struct mxl111sf_demod_state*,int,int) ; 

__attribute__((used)) static int mxl1x1sf_demod_reset_irq_status(struct mxl111sf_demod_state *state)
{
	return mxl111sf_demod_write_reg(state, 0x0e, 0xff);
}