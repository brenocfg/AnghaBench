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
struct v4l2_subscribed_event_ops {int (* add ) (struct v4l2_subscribed_event*,unsigned int) ;} ;
struct v4l2_subscribed_event {scalar_t__ type; unsigned int elems; struct v4l2_subscribed_event_ops const* ops; int /*<<< orphan*/  list; struct v4l2_fh* fh; int /*<<< orphan*/  flags; int /*<<< orphan*/  id; TYPE_1__* events; } ;
struct v4l2_fh {int /*<<< orphan*/  subscribe_lock; TYPE_2__* vdev; int /*<<< orphan*/  subscribed; } ;
struct v4l2_event_subscription {scalar_t__ type; int /*<<< orphan*/  id; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  fh_lock; } ;
struct TYPE_3__ {struct v4l2_subscribed_event* sev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ V4L2_EVENT_ALL ; 
 int /*<<< orphan*/  __v4l2_event_unsubscribe (struct v4l2_subscribed_event*) ; 
 int /*<<< orphan*/  events ; 
 int /*<<< orphan*/  kvfree (struct v4l2_subscribed_event*) ; 
 struct v4l2_subscribed_event* kvzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  struct_size (struct v4l2_subscribed_event*,int /*<<< orphan*/ ,unsigned int) ; 
 int stub1 (struct v4l2_subscribed_event*,unsigned int) ; 
 struct v4l2_subscribed_event* v4l2_event_subscribed (struct v4l2_fh*,scalar_t__,int /*<<< orphan*/ ) ; 

int v4l2_event_subscribe(struct v4l2_fh *fh,
			 const struct v4l2_event_subscription *sub, unsigned elems,
			 const struct v4l2_subscribed_event_ops *ops)
{
	struct v4l2_subscribed_event *sev, *found_ev;
	unsigned long flags;
	unsigned i;
	int ret = 0;

	if (sub->type == V4L2_EVENT_ALL)
		return -EINVAL;

	if (elems < 1)
		elems = 1;

	sev = kvzalloc(struct_size(sev, events, elems), GFP_KERNEL);
	if (!sev)
		return -ENOMEM;
	for (i = 0; i < elems; i++)
		sev->events[i].sev = sev;
	sev->type = sub->type;
	sev->id = sub->id;
	sev->flags = sub->flags;
	sev->fh = fh;
	sev->ops = ops;
	sev->elems = elems;

	mutex_lock(&fh->subscribe_lock);

	spin_lock_irqsave(&fh->vdev->fh_lock, flags);
	found_ev = v4l2_event_subscribed(fh, sub->type, sub->id);
	if (!found_ev)
		list_add(&sev->list, &fh->subscribed);
	spin_unlock_irqrestore(&fh->vdev->fh_lock, flags);

	if (found_ev) {
		/* Already listening */
		kvfree(sev);
	} else if (sev->ops && sev->ops->add) {
		ret = sev->ops->add(sev, elems);
		if (ret) {
			spin_lock_irqsave(&fh->vdev->fh_lock, flags);
			__v4l2_event_unsubscribe(sev);
			spin_unlock_irqrestore(&fh->vdev->fh_lock, flags);
			kvfree(sev);
		}
	}

	mutex_unlock(&fh->subscribe_lock);

	return ret;
}