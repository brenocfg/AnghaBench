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
struct v4l2_subdev {int dummy; } ;
struct v4l2_fh {int dummy; } ;
struct v4l2_event_subscription {int type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_EVENT_CTRL 129 
#define  V4L2_EVENT_SOURCE_CHANGE 128 
 int v4l2_ctrl_subdev_subscribe_event (struct v4l2_subdev*,struct v4l2_fh*,struct v4l2_event_subscription*) ; 
 int v4l2_src_change_event_subdev_subscribe (struct v4l2_subdev*,struct v4l2_fh*,struct v4l2_event_subscription*) ; 

__attribute__((used)) static int adv7842_subscribe_event(struct v4l2_subdev *sd,
				   struct v4l2_fh *fh,
				   struct v4l2_event_subscription *sub)
{
	switch (sub->type) {
	case V4L2_EVENT_SOURCE_CHANGE:
		return v4l2_src_change_event_subdev_subscribe(sd, fh, sub);
	case V4L2_EVENT_CTRL:
		return v4l2_ctrl_subdev_subscribe_event(sd, fh, sub);
	default:
		return -EINVAL;
	}
}