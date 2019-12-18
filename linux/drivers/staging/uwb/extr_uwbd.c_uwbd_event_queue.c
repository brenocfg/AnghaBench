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
struct TYPE_4__ {scalar_t__ pid; int /*<<< orphan*/  event_list_lock; int /*<<< orphan*/  wq; int /*<<< orphan*/  event_list; } ;
struct uwb_rc {TYPE_2__ uwbd; } ;
struct TYPE_3__ {struct uwb_event* rceb; } ;
struct uwb_event {scalar_t__ type; TYPE_1__ notif; struct uwb_rc* rc; int /*<<< orphan*/  list_node; } ;

/* Variables and functions */
 scalar_t__ UWB_EVT_TYPE_NOTIF ; 
 int /*<<< orphan*/  __uwb_rc_put (struct uwb_rc*) ; 
 int /*<<< orphan*/  kfree (struct uwb_event*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

void uwbd_event_queue(struct uwb_event *evt)
{
	struct uwb_rc *rc = evt->rc;
	unsigned long flags;

	spin_lock_irqsave(&rc->uwbd.event_list_lock, flags);
	if (rc->uwbd.pid != 0) {
		list_add(&evt->list_node, &rc->uwbd.event_list);
		wake_up_all(&rc->uwbd.wq);
	} else {
		__uwb_rc_put(evt->rc);
		if (evt->type == UWB_EVT_TYPE_NOTIF)
			kfree(evt->notif.rceb);
		kfree(evt);
	}
	spin_unlock_irqrestore(&rc->uwbd.event_list_lock, flags);
	return;
}