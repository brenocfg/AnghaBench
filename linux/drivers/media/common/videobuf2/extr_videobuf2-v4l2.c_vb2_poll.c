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
struct video_device {int /*<<< orphan*/  flags; } ;
struct vb2_queue {int dummy; } ;
struct v4l2_fh {int /*<<< orphan*/  wait; } ;
struct file {struct v4l2_fh* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLPRI ; 
 int /*<<< orphan*/  V4L2_FL_USES_V4L2_FH ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_event_pending (struct v4l2_fh*) ; 
 int /*<<< orphan*/  vb2_core_poll (struct vb2_queue*,struct file*,int /*<<< orphan*/ *) ; 
 struct video_device* video_devdata (struct file*) ; 

__poll_t vb2_poll(struct vb2_queue *q, struct file *file, poll_table *wait)
{
	struct video_device *vfd = video_devdata(file);
	__poll_t res;

	res = vb2_core_poll(q, file, wait);

	if (test_bit(V4L2_FL_USES_V4L2_FH, &vfd->flags)) {
		struct v4l2_fh *fh = file->private_data;

		poll_wait(file, &fh->wait, wait);
		if (v4l2_event_pending(fh))
			res |= EPOLLPRI;
	}

	return res;
}