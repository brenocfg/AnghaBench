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
struct v4l2_fh {scalar_t__ navailable; TYPE_1__* vdev; int /*<<< orphan*/  wait; } ;
struct v4l2_event {int dummy; } ;
struct TYPE_2__ {scalar_t__ lock; } ;

/* Variables and functions */
 int ENOENT ; 
 int __v4l2_event_dequeue (struct v4l2_fh*,struct v4l2_event*) ; 
 int /*<<< orphan*/  mutex_lock (scalar_t__) ; 
 int /*<<< orphan*/  mutex_unlock (scalar_t__) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

int v4l2_event_dequeue(struct v4l2_fh *fh, struct v4l2_event *event,
		       int nonblocking)
{
	int ret;

	if (nonblocking)
		return __v4l2_event_dequeue(fh, event);

	/* Release the vdev lock while waiting */
	if (fh->vdev->lock)
		mutex_unlock(fh->vdev->lock);

	do {
		ret = wait_event_interruptible(fh->wait,
					       fh->navailable != 0);
		if (ret < 0)
			break;

		ret = __v4l2_event_dequeue(fh, event);
	} while (ret == -ENOENT);

	if (fh->vdev->lock)
		mutex_lock(fh->vdev->lock);

	return ret;
}