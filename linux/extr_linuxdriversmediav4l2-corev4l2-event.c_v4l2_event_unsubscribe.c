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
struct v4l2_subscribed_event {TYPE_2__* ops; } ;
struct v4l2_fh {int /*<<< orphan*/  subscribe_lock; TYPE_1__* vdev; } ;
struct v4l2_event_subscription {scalar_t__ type; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* del ) (struct v4l2_subscribed_event*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  fh_lock; } ;

/* Variables and functions */
 scalar_t__ V4L2_EVENT_ALL ; 
 int /*<<< orphan*/  __v4l2_event_unsubscribe (struct v4l2_subscribed_event*) ; 
 int /*<<< orphan*/  kvfree (struct v4l2_subscribed_event*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct v4l2_subscribed_event*) ; 
 struct v4l2_subscribed_event* v4l2_event_subscribed (struct v4l2_fh*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_event_unsubscribe_all (struct v4l2_fh*) ; 

int v4l2_event_unsubscribe(struct v4l2_fh *fh,
			   const struct v4l2_event_subscription *sub)
{
	struct v4l2_subscribed_event *sev;
	unsigned long flags;

	if (sub->type == V4L2_EVENT_ALL) {
		v4l2_event_unsubscribe_all(fh);
		return 0;
	}

	mutex_lock(&fh->subscribe_lock);

	spin_lock_irqsave(&fh->vdev->fh_lock, flags);

	sev = v4l2_event_subscribed(fh, sub->type, sub->id);
	if (sev != NULL)
		__v4l2_event_unsubscribe(sev);

	spin_unlock_irqrestore(&fh->vdev->fh_lock, flags);

	if (sev && sev->ops && sev->ops->del)
		sev->ops->del(sev);

	mutex_unlock(&fh->subscribe_lock);

	kvfree(sev);

	return 0;
}