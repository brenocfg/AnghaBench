#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct v4l2_subscribed_event {int in_use; int elems; int first; struct v4l2_kevent* events; TYPE_1__* ops; } ;
struct TYPE_6__ {scalar_t__ sequence; int /*<<< orphan*/  id; int /*<<< orphan*/  u; int /*<<< orphan*/  type; } ;
struct v4l2_kevent {int /*<<< orphan*/  list; TYPE_2__ event; int /*<<< orphan*/  ts; } ;
struct v4l2_fh {int /*<<< orphan*/  wait; int /*<<< orphan*/  navailable; int /*<<< orphan*/  available; scalar_t__ sequence; } ;
struct v4l2_event {int /*<<< orphan*/  id; int /*<<< orphan*/  u; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* merge ) (TYPE_2__*,TYPE_2__*) ;int /*<<< orphan*/  (* replace ) (TYPE_2__*,struct v4l2_event const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int sev_pos (struct v4l2_subscribed_event*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct v4l2_event const*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,TYPE_2__*) ; 
 struct v4l2_subscribed_event* v4l2_event_subscribed (struct v4l2_fh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __v4l2_event_queue_fh(struct v4l2_fh *fh,
				  const struct v4l2_event *ev, u64 ts)
{
	struct v4l2_subscribed_event *sev;
	struct v4l2_kevent *kev;
	bool copy_payload = true;

	/* Are we subscribed? */
	sev = v4l2_event_subscribed(fh, ev->type, ev->id);
	if (sev == NULL)
		return;

	/* Increase event sequence number on fh. */
	fh->sequence++;

	/* Do we have any free events? */
	if (sev->in_use == sev->elems) {
		/* no, remove the oldest one */
		kev = sev->events + sev_pos(sev, 0);
		list_del(&kev->list);
		sev->in_use--;
		sev->first = sev_pos(sev, 1);
		fh->navailable--;
		if (sev->elems == 1) {
			if (sev->ops && sev->ops->replace) {
				sev->ops->replace(&kev->event, ev);
				copy_payload = false;
			}
		} else if (sev->ops && sev->ops->merge) {
			struct v4l2_kevent *second_oldest =
				sev->events + sev_pos(sev, 0);
			sev->ops->merge(&kev->event, &second_oldest->event);
		}
	}

	/* Take one and fill it. */
	kev = sev->events + sev_pos(sev, sev->in_use);
	kev->event.type = ev->type;
	if (copy_payload)
		kev->event.u = ev->u;
	kev->event.id = ev->id;
	kev->ts = ts;
	kev->event.sequence = fh->sequence;
	sev->in_use++;
	list_add_tail(&kev->list, &fh->available);

	fh->navailable++;

	wake_up_all(&fh->wait);
}