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
struct event_t {int type; int cid; int parameter; void* arg; void* ptr; struct at_state_t* at_state; } ;
struct cardstate {unsigned int ev_tail; unsigned int ev_head; int /*<<< orphan*/  ev_lock; struct event_t* events; int /*<<< orphan*/  dev; } ;
struct at_state_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_EVENT ; 
 unsigned int MAX_EVENTS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

struct event_t *gigaset_add_event(struct cardstate *cs,
				  struct at_state_t *at_state, int type,
				  void *ptr, int parameter, void *arg)
{
	unsigned long flags;
	unsigned next, tail;
	struct event_t *event = NULL;

	gig_dbg(DEBUG_EVENT, "queueing event %d", type);

	spin_lock_irqsave(&cs->ev_lock, flags);

	tail = cs->ev_tail;
	next = (tail + 1) % MAX_EVENTS;
	if (unlikely(next == cs->ev_head))
		dev_err(cs->dev, "event queue full\n");
	else {
		event = cs->events + tail;
		event->type = type;
		event->at_state = at_state;
		event->cid = -1;
		event->ptr = ptr;
		event->arg = arg;
		event->parameter = parameter;
		cs->ev_tail = next;
	}

	spin_unlock_irqrestore(&cs->ev_lock, flags);

	return event;
}