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
struct v4l2_fh {TYPE_1__* vdev; } ;
struct v4l2_event_subscription {int type; } ;
struct TYPE_2__ {int /*<<< orphan*/  vfl_dir; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_EVENT_SOURCE_CHANGE 128 
 int /*<<< orphan*/  VFL_DIR_RX ; 
 int v4l2_ctrl_subscribe_event (struct v4l2_fh*,struct v4l2_event_subscription const*) ; 
 int v4l2_src_change_event_subscribe (struct v4l2_fh*,struct v4l2_event_subscription const*) ; 

int vidioc_subscribe_event(struct v4l2_fh *fh,
			const struct v4l2_event_subscription *sub)
{
	switch (sub->type) {
	case V4L2_EVENT_SOURCE_CHANGE:
		if (fh->vdev->vfl_dir == VFL_DIR_RX)
			return v4l2_src_change_event_subscribe(fh, sub);
		break;
	default:
		return v4l2_ctrl_subscribe_event(fh, sub);
	}
	return -EINVAL;
}