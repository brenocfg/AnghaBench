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
struct analogix_dp_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  analogix_dp_set_lane0_pre_emphasis (struct analogix_dp_device*,int) ; 
 int /*<<< orphan*/  analogix_dp_set_lane1_pre_emphasis (struct analogix_dp_device*,int) ; 
 int /*<<< orphan*/  analogix_dp_set_lane2_pre_emphasis (struct analogix_dp_device*,int) ; 
 int /*<<< orphan*/  analogix_dp_set_lane3_pre_emphasis (struct analogix_dp_device*,int) ; 

__attribute__((used)) static void
analogix_dp_set_lane_lane_pre_emphasis(struct analogix_dp_device *dp,
				       int pre_emphasis, int lane)
{
	switch (lane) {
	case 0:
		analogix_dp_set_lane0_pre_emphasis(dp, pre_emphasis);
		break;
	case 1:
		analogix_dp_set_lane1_pre_emphasis(dp, pre_emphasis);
		break;

	case 2:
		analogix_dp_set_lane2_pre_emphasis(dp, pre_emphasis);
		break;

	case 3:
		analogix_dp_set_lane3_pre_emphasis(dp, pre_emphasis);
		break;
	}
}