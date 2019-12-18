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
struct v4l2_subdev {int dummy; } ;
struct noon010_info {TYPE_2__* curr_fmt; TYPE_1__* curr_win; } ;
struct TYPE_4__ {int /*<<< orphan*/  ispctl1_reg; } ;
struct TYPE_3__ {int /*<<< orphan*/  vid_ctl1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_CTL_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VDO_CTL_REG (int /*<<< orphan*/ ) ; 
 int cam_i2c_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct noon010_info* to_noon010 (struct v4l2_subdev*) ; 

__attribute__((used)) static int noon010_set_params(struct v4l2_subdev *sd)
{
	struct noon010_info *info = to_noon010(sd);

	int ret = cam_i2c_write(sd, VDO_CTL_REG(0),
				info->curr_win->vid_ctl1);
	if (ret)
		return ret;
	return cam_i2c_write(sd, ISP_CTL_REG(0),
			     info->curr_fmt->ispctl1_reg);
}