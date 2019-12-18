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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct v4l2_subdev {int dummy; } ;
struct gs {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int MASK_H_LOCK ; 
 int MASK_STD_LOCK ; 
 int MASK_V_LOCK ; 
 scalar_t__ REG_LINES_PER_FRAME ; 
 scalar_t__ REG_STATUS ; 
 int /*<<< orphan*/  V4L2_IN_ST_NO_H_LOCK ; 
 int /*<<< orphan*/  V4L2_IN_ST_NO_POWER ; 
 int /*<<< orphan*/  V4L2_IN_ST_NO_SIGNAL ; 
 int /*<<< orphan*/  V4L2_IN_ST_NO_STD_LOCK ; 
 int /*<<< orphan*/  V4L2_IN_ST_NO_V_LOCK ; 
 int gs_read_register (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 struct gs* to_gs (struct v4l2_subdev*) ; 

__attribute__((used)) static int gs_g_input_status(struct v4l2_subdev *sd, u32 *status)
{
	struct gs *gs = to_gs(sd);
	u16 reg_value, i;
	int ret;

	/*
	 * Check if the component detect a line, a frame or something else
	 * which looks like a video signal activity.
	 */
	for (i = 0; i < 4; i++) {
		ret = gs_read_register(gs->pdev,
				       REG_LINES_PER_FRAME + i, &reg_value);
		if (reg_value)
			break;
		if (ret) {
			*status = V4L2_IN_ST_NO_POWER;
			return ret;
		}
	}

	/* If no register reports a video signal */
	if (i >= 4)
		*status |= V4L2_IN_ST_NO_SIGNAL;

	ret = gs_read_register(gs->pdev, REG_STATUS, &reg_value);
	if (!(reg_value & MASK_H_LOCK))
		*status |=  V4L2_IN_ST_NO_H_LOCK;
	if (!(reg_value & MASK_V_LOCK))
		*status |=  V4L2_IN_ST_NO_V_LOCK;
	if (!(reg_value & MASK_STD_LOCK))
		*status |=  V4L2_IN_ST_NO_STD_LOCK;

	return ret;
}