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
struct TYPE_3__ {int flags; } ;
struct TYPE_4__ {TYPE_1__ bt; } ;
struct ad9389b_state {TYPE_2__ dv_timings; } ;

/* Variables and functions */
 int V4L2_DV_FL_IS_CE_VIDEO ; 
 int /*<<< orphan*/  ad9389b_wr_and_or (struct v4l2_subdev*,int,int,int) ; 
 struct ad9389b_state* get_ad9389b_state (struct v4l2_subdev*) ; 

__attribute__((used)) static void ad9389b_set_IT_content_AVI_InfoFrame(struct v4l2_subdev *sd)
{
	struct ad9389b_state *state = get_ad9389b_state(sd);

	if (state->dv_timings.bt.flags & V4L2_DV_FL_IS_CE_VIDEO) {
		/* CE format, not IT  */
		ad9389b_wr_and_or(sd, 0xcd, 0xbf, 0x00);
	} else {
		/* IT format */
		ad9389b_wr_and_or(sd, 0xcd, 0xbf, 0x40);
	}
}