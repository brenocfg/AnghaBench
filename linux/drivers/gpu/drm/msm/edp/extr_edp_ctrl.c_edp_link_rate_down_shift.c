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
struct TYPE_2__ {int num_lanes; } ;
struct edp_ctrl {int link_rate; int lane_cnt; int color_depth; int pixel_rate; TYPE_1__ dp_link; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int,int,...) ; 
 int DP_LINK_BW_1_62 ; 
 int EDP_LINK_BW_MAX ; 
 int EINVAL ; 

__attribute__((used)) static int edp_link_rate_down_shift(struct edp_ctrl *ctrl)
{
	u32 prate, lrate, bpp;
	u8 rate, lane, max_lane;
	int changed = 0;

	rate = ctrl->link_rate;
	lane = ctrl->lane_cnt;
	max_lane = ctrl->dp_link.num_lanes;

	bpp = ctrl->color_depth * 3;
	prate = ctrl->pixel_rate;
	prate *= bpp;
	prate /= 8; /* in kByte */

	if (rate > DP_LINK_BW_1_62 && rate <= EDP_LINK_BW_MAX) {
		rate -= 4;	/* reduce rate */
		changed++;
	}

	if (changed) {
		if (lane >= 1 && lane < max_lane)
			lane <<= 1;	/* increase lane */

		lrate = 270000; /* in kHz */
		lrate *= rate;
		lrate /= 10; /* kByte, 10 bits --> 8 bits */
		lrate *= lane;

		DBG("new lrate=%u prate=%u(kHz) rate=%d lane=%d p=%u b=%d",
			lrate, prate, rate, lane,
			ctrl->pixel_rate,
			bpp);

		if (lrate > prate) {
			ctrl->link_rate = rate;
			ctrl->lane_cnt = lane;
			DBG("new rate=%d %d", rate, lane);
			return 0;
		}
	}

	return -EINVAL;
}