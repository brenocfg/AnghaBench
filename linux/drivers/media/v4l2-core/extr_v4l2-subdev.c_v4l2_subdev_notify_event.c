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
struct v4l2_subdev {int /*<<< orphan*/  devnode; } ;
struct v4l2_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_DEVICE_NOTIFY_EVENT ; 
 int /*<<< orphan*/  v4l2_event_queue (int /*<<< orphan*/ ,struct v4l2_event const*) ; 
 int /*<<< orphan*/  v4l2_subdev_notify (struct v4l2_subdev*,int /*<<< orphan*/ ,void*) ; 

void v4l2_subdev_notify_event(struct v4l2_subdev *sd,
			      const struct v4l2_event *ev)
{
	v4l2_event_queue(sd->devnode, ev);
	v4l2_subdev_notify(sd, V4L2_DEVICE_NOTIFY_EVENT, (void *)ev);
}