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
struct video_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ data; } ;
struct v4l2_event {int /*<<< orphan*/  type; TYPE_2__ u; } ;
struct omap3isp_stat_event_status {int buf_err; int /*<<< orphan*/  config_counter; int /*<<< orphan*/  frame_number; } ;
struct TYPE_3__ {struct video_device* devnode; } ;
struct ispstat {int /*<<< orphan*/  event_type; int /*<<< orphan*/  config_counter; int /*<<< orphan*/  frame_number; TYPE_1__ subdev; } ;
typedef  int /*<<< orphan*/  event ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct v4l2_event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_event_queue (struct video_device*,struct v4l2_event*) ; 

__attribute__((used)) static void isp_stat_queue_event(struct ispstat *stat, int err)
{
	struct video_device *vdev = stat->subdev.devnode;
	struct v4l2_event event;
	struct omap3isp_stat_event_status *status = (void *)event.u.data;

	memset(&event, 0, sizeof(event));
	if (!err) {
		status->frame_number = stat->frame_number;
		status->config_counter = stat->config_counter;
	} else {
		status->buf_err = 1;
	}
	event.type = stat->event_type;
	v4l2_event_queue(vdev, &event);
}