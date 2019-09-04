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
typedef  unsigned int u32 ;
struct analogix_dp_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned int analogix_dp_get_lane0_link_training (struct analogix_dp_device*) ; 
 unsigned int analogix_dp_get_lane1_link_training (struct analogix_dp_device*) ; 
 unsigned int analogix_dp_get_lane2_link_training (struct analogix_dp_device*) ; 
 unsigned int analogix_dp_get_lane3_link_training (struct analogix_dp_device*) ; 

__attribute__((used)) static unsigned int
analogix_dp_get_lane_link_training(struct analogix_dp_device *dp,
				   int lane)
{
	u32 reg;

	switch (lane) {
	case 0:
		reg = analogix_dp_get_lane0_link_training(dp);
		break;
	case 1:
		reg = analogix_dp_get_lane1_link_training(dp);
		break;
	case 2:
		reg = analogix_dp_get_lane2_link_training(dp);
		break;
	case 3:
		reg = analogix_dp_get_lane3_link_training(dp);
		break;
	default:
		WARN_ON(1);
		return 0;
	}

	return reg;
}