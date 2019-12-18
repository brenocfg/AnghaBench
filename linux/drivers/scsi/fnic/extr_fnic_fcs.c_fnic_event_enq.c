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
struct fnic_event {int event; int /*<<< orphan*/  list; struct fnic* fnic; } ;
struct fnic {int /*<<< orphan*/  event_work; int /*<<< orphan*/  fnic_lock; int /*<<< orphan*/  evlist; } ;
typedef  enum fnic_evt { ____Placeholder_fnic_evt } fnic_evt ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct fnic_event* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void fnic_event_enq(struct fnic *fnic, enum fnic_evt ev)
{
	struct fnic_event *fevt;
	unsigned long flags;

	fevt = kmalloc(sizeof(*fevt), GFP_ATOMIC);
	if (!fevt)
		return;

	fevt->fnic = fnic;
	fevt->event = ev;

	spin_lock_irqsave(&fnic->fnic_lock, flags);
	list_add_tail(&fevt->list, &fnic->evlist);
	spin_unlock_irqrestore(&fnic->fnic_lock, flags);

	schedule_work(&fnic->event_work);
}