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
struct v4l2_subdev {int /*<<< orphan*/  ctrl_handler; } ;
struct v4l2_fh {int dummy; } ;
struct v4l2_event_subscription {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int v4l2_ctrl_subscribe_event (struct v4l2_fh*,struct v4l2_event_subscription*) ; 

int v4l2_ctrl_subdev_subscribe_event(struct v4l2_subdev *sd, struct v4l2_fh *fh,
				     struct v4l2_event_subscription *sub)
{
	if (!sd->ctrl_handler)
		return -EINVAL;
	return v4l2_ctrl_subscribe_event(fh, sub);
}