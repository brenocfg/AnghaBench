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
struct file {struct cx231xx_fh* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  wait; } ;
struct cx231xx_fh {scalar_t__ type; int /*<<< orphan*/  vb_vidq; TYPE_1__ fh; struct cx231xx* dev; } ;
struct cx231xx {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLIN ; 
 int EPOLLPRI ; 
 int EPOLLRDNORM ; 
 scalar_t__ V4L2_BUF_TYPE_VBI_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int check_dev (struct cx231xx*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int poll_requested_events (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int res_get (struct cx231xx_fh*) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ v4l2_event_pending (TYPE_1__*) ; 
 int videobuf_poll_stream (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t cx231xx_v4l2_poll(struct file *filp, poll_table *wait)
{
	__poll_t req_events = poll_requested_events(wait);
	struct cx231xx_fh *fh = filp->private_data;
	struct cx231xx *dev = fh->dev;
	__poll_t res = 0;
	int rc;

	rc = check_dev(dev);
	if (rc < 0)
		return EPOLLERR;

	rc = res_get(fh);

	if (unlikely(rc < 0))
		return EPOLLERR;

	if (v4l2_event_pending(&fh->fh))
		res |= EPOLLPRI;
	else
		poll_wait(filp, &fh->fh.wait, wait);

	if (!(req_events & (EPOLLIN | EPOLLRDNORM)))
		return res;

	if ((V4L2_BUF_TYPE_VIDEO_CAPTURE == fh->type) ||
	    (V4L2_BUF_TYPE_VBI_CAPTURE == fh->type)) {
		mutex_lock(&dev->lock);
		res |= videobuf_poll_stream(filp, &fh->vb_vidq, wait);
		mutex_unlock(&dev->lock);
		return res;
	}
	return res | EPOLLERR;
}