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
struct TYPE_2__ {int /*<<< orphan*/  max_link_rate; int /*<<< orphan*/  max_lane_count; } ;
struct analogix_dp_device {TYPE_1__ video_info; scalar_t__ fast_train_enable; } ;

/* Variables and functions */
 int analogix_dp_fast_link_train (struct analogix_dp_device*) ; 
 int analogix_dp_full_link_train (struct analogix_dp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int analogix_dp_train_link(struct analogix_dp_device *dp)
{
	if (dp->fast_train_enable)
		return analogix_dp_fast_link_train(dp);

	return analogix_dp_full_link_train(dp, dp->video_info.max_lane_count,
					   dp->video_info.max_link_rate);
}