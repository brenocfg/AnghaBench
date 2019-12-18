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
typedef  int /*<<< orphan*/  u64 ;
struct v4l2_fh {TYPE_1__* vdev; } ;
struct v4l2_event {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fh_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __v4l2_event_queue_fh (struct v4l2_fh*,struct v4l2_event const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void v4l2_event_queue_fh(struct v4l2_fh *fh, const struct v4l2_event *ev)
{
	unsigned long flags;
	u64 ts = ktime_get_ns();

	spin_lock_irqsave(&fh->vdev->fh_lock, flags);
	__v4l2_event_queue_fh(fh, ev, ts);
	spin_unlock_irqrestore(&fh->vdev->fh_lock, flags);
}