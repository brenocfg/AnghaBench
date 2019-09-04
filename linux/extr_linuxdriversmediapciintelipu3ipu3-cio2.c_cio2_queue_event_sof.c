#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  frame_sequence; } ;
struct TYPE_5__ {TYPE_1__ frame_sync; } ;
struct v4l2_event {TYPE_2__ u; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int /*<<< orphan*/  devnode; } ;
struct cio2_queue {TYPE_3__ subdev; int /*<<< orphan*/  frame_sequence; } ;
struct cio2_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_EVENT_FRAME_SYNC ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_event_queue (int /*<<< orphan*/ ,struct v4l2_event*) ; 

__attribute__((used)) static void cio2_queue_event_sof(struct cio2_device *cio2, struct cio2_queue *q)
{
	/*
	 * For the user space camera control algorithms it is essential
	 * to know when the reception of a frame has begun. That's often
	 * the best timing information to get from the hardware.
	 */
	struct v4l2_event event = {
		.type = V4L2_EVENT_FRAME_SYNC,
		.u.frame_sync.frame_sequence = atomic_read(&q->frame_sequence),
	};

	v4l2_event_queue(q->subdev.devnode, &event);
}