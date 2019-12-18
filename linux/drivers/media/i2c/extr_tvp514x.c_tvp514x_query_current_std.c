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
typedef  enum tvp514x_std { ____Placeholder_tvp514x_std } tvp514x_std ;

/* Variables and functions */
 int /*<<< orphan*/  REG_VIDEO_STD ; 
 int /*<<< orphan*/  REG_VIDEO_STD_STATUS ; 
 int STD_INVALID ; 
 int STD_NTSC_MJ ; 
 int STD_PAL_BDGHIN ; 
 int VIDEO_STD_AUTO_SWITCH_BIT ; 
 int VIDEO_STD_MASK ; 
#define  VIDEO_STD_NTSC_MJ_BIT 129 
#define  VIDEO_STD_PAL_BDGHIN_BIT 128 
 int tvp514x_read_reg (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum tvp514x_std tvp514x_query_current_std(struct v4l2_subdev *sd)
{
	u8 std, std_status;

	std = tvp514x_read_reg(sd, REG_VIDEO_STD);
	if ((std & VIDEO_STD_MASK) == VIDEO_STD_AUTO_SWITCH_BIT)
		/* use the standard status register */
		std_status = tvp514x_read_reg(sd, REG_VIDEO_STD_STATUS);
	else
		/* use the standard register itself */
		std_status = std;

	switch (std_status & VIDEO_STD_MASK) {
	case VIDEO_STD_NTSC_MJ_BIT:
		return STD_NTSC_MJ;

	case VIDEO_STD_PAL_BDGHIN_BIT:
		return STD_PAL_BDGHIN;

	default:
		return STD_INVALID;
	}

	return STD_INVALID;
}