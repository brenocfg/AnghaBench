#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int num_lanes; int /*<<< orphan*/  rate; } ;
struct edp_ctrl {int pixel_rate; int color_depth; int link_rate; int lane_cnt; TYPE_1__ dp_link; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int,int) ; 
 int drm_dp_link_rate_to_bw_code (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void edp_fill_link_cfg(struct edp_ctrl *ctrl)
{
	u32 prate;
	u32 lrate;
	u32 bpp;
	u8 max_lane = ctrl->dp_link.num_lanes;
	u8 lane;

	prate = ctrl->pixel_rate;
	bpp = ctrl->color_depth * 3;

	/*
	 * By default, use the maximum link rate and minimum lane count,
	 * so that we can do rate down shift during link training.
	 */
	ctrl->link_rate = drm_dp_link_rate_to_bw_code(ctrl->dp_link.rate);

	prate *= bpp;
	prate /= 8; /* in kByte */

	lrate = 270000; /* in kHz */
	lrate *= ctrl->link_rate;
	lrate /= 10; /* in kByte, 10 bits --> 8 bits */

	for (lane = 1; lane <= max_lane; lane <<= 1) {
		if (lrate >= prate)
			break;
		lrate <<= 1;
	}

	ctrl->lane_cnt = lane;
	DBG("rate=%d lane=%d", ctrl->link_rate, ctrl->lane_cnt);
}