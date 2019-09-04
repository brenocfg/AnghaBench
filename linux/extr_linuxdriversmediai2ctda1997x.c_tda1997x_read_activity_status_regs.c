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
typedef  int u8 ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int LAST_STATE_REACHED ; 
 int MASK_CLK_ACTIVE ; 
 int MASK_CLK_STABLE ; 
 int MASK_SUS_STATE ; 
 int MASK_SUS_STATUS ; 
 int /*<<< orphan*/  REG_CLK_A_STATUS ; 
 int /*<<< orphan*/  REG_CLK_B_STATUS ; 
 int /*<<< orphan*/  REG_SUS_STATUS ; 
 int io_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8
tda1997x_read_activity_status_regs(struct v4l2_subdev *sd)
{
	u8 reg, status = 0;

	/* Read CLK_A_STATUS register */
	reg = io_read(sd, REG_CLK_A_STATUS);
	/* ignore if not active */
	if ((reg & MASK_CLK_STABLE) && !(reg & MASK_CLK_ACTIVE))
		reg &= ~MASK_CLK_STABLE;
	status |= ((reg & MASK_CLK_STABLE) >> 2);

	/* Read CLK_B_STATUS register */
	reg = io_read(sd, REG_CLK_B_STATUS);
	/* ignore if not active */
	if ((reg & MASK_CLK_STABLE) && !(reg & MASK_CLK_ACTIVE))
		reg &= ~MASK_CLK_STABLE;
	status |= ((reg & MASK_CLK_STABLE) >> 1);

	/* Read the SUS_STATUS register */
	reg = io_read(sd, REG_SUS_STATUS);

	/* If state = 5 => TMDS is locked */
	if ((reg & MASK_SUS_STATUS) == LAST_STATE_REACHED)
		status |= MASK_SUS_STATE;
	else
		status &= ~MASK_SUS_STATE;

	return status;
}