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
typedef  int u16 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_dv_timings {int dummy; } ;
struct gs {int /*<<< orphan*/  pdev; scalar_t__ enabled; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOLCK ; 
 int ENOLINK ; 
 int ERANGE ; 
 int MASK_H_LOCK ; 
 int MASK_STD_LOCK ; 
 int MASK_V_LOCK ; 
 scalar_t__ REG_LINES_PER_FRAME ; 
 scalar_t__ REG_STATUS ; 
 int /*<<< orphan*/  gs_read_register (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int gs_status_format (int,struct v4l2_dv_timings*) ; 
 struct gs* to_gs (struct v4l2_subdev*) ; 

__attribute__((used)) static int gs_query_dv_timings(struct v4l2_subdev *sd,
			struct v4l2_dv_timings *timings)
{
	struct gs *gs = to_gs(sd);
	struct v4l2_dv_timings fmt;
	u16 reg_value, i;
	int ret;

	if (gs->enabled)
		return -EBUSY;

	/*
	 * Check if the component detect a line, a frame or something else
	 * which looks like a video signal activity.
	 */
	for (i = 0; i < 4; i++) {
		gs_read_register(gs->pdev, REG_LINES_PER_FRAME + i, &reg_value);
		if (reg_value)
			break;
	}

	/* If no register reports a video signal */
	if (i >= 4)
		return -ENOLINK;

	gs_read_register(gs->pdev, REG_STATUS, &reg_value);
	if (!(reg_value & MASK_H_LOCK) || !(reg_value & MASK_V_LOCK))
		return -ENOLCK;
	if (!(reg_value & MASK_STD_LOCK))
		return -ERANGE;

	ret = gs_status_format(reg_value, &fmt);

	if (ret < 0)
		return ret;

	*timings = fmt;
	return 0;
}