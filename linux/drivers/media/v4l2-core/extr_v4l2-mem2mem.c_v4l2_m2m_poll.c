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
struct v4l2_m2m_ctx {int dummy; } ;
struct v4l2_fh {int /*<<< orphan*/  wait; } ;
struct poll_table_struct {int dummy; } ;
struct file {struct v4l2_fh* private_data; } ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLPRI ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 int /*<<< orphan*/  V4L2_FL_USES_V4L2_FH ; 
 int poll_requested_events (struct poll_table_struct*) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_event_pending (struct v4l2_fh*) ; 
 int v4l2_m2m_poll_for_data (struct file*,struct v4l2_m2m_ctx*,struct poll_table_struct*) ; 
 struct video_device* video_devdata (struct file*) ; 

__poll_t v4l2_m2m_poll(struct file *file, struct v4l2_m2m_ctx *m2m_ctx,
		       struct poll_table_struct *wait)
{
	struct video_device *vfd = video_devdata(file);
	__poll_t req_events = poll_requested_events(wait);
	__poll_t rc = 0;

	if (req_events & (EPOLLOUT | EPOLLWRNORM | EPOLLIN | EPOLLRDNORM))
		rc = v4l2_m2m_poll_for_data(file, m2m_ctx, wait);

	if (test_bit(V4L2_FL_USES_V4L2_FH, &vfd->flags)) {
		struct v4l2_fh *fh = file->private_data;

		poll_wait(file, &fh->wait, wait);
		if (v4l2_event_pending(fh))
			rc |= EPOLLPRI;
	}

	return rc;
}