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
struct eeh_pe {int dummy; } ;
struct eeh_event {int /*<<< orphan*/  list; struct eeh_pe* pe; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  eeh_eventlist ; 
 int /*<<< orphan*/  eeh_eventlist_lock ; 
 int /*<<< orphan*/  eeh_eventlist_sem ; 
 struct eeh_event* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

int eeh_send_failure_event(struct eeh_pe *pe)
{
	unsigned long flags;
	struct eeh_event *event;

	event = kzalloc(sizeof(*event), GFP_ATOMIC);
	if (!event) {
		pr_err("EEH: out of memory, event not handled\n");
		return -ENOMEM;
	}
	event->pe = pe;

	/* We may or may not be called in an interrupt context */
	spin_lock_irqsave(&eeh_eventlist_lock, flags);
	list_add(&event->list, &eeh_eventlist);
	spin_unlock_irqrestore(&eeh_eventlist_lock, flags);

	/* For EEH deamon to knick in */
	up(&eeh_eventlist_sem);

	return 0;
}