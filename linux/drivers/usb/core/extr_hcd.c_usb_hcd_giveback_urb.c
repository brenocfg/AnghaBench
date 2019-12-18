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
struct giveback_urb_bh {int running; int /*<<< orphan*/  bh; int /*<<< orphan*/  lock; int /*<<< orphan*/  head; } ;
struct usb_hcd {struct giveback_urb_bh low_prio_bh; struct giveback_urb_bh high_prio_bh; } ;
struct urb {int unlinked; int /*<<< orphan*/  urb_list; int /*<<< orphan*/  pipe; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __usb_hcd_giveback_urb (struct urb*) ; 
 int /*<<< orphan*/  hcd_giveback_urb_in_bh (struct usb_hcd*) ; 
 int /*<<< orphan*/  is_root_hub (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_pipeint (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_pipeisoc (int /*<<< orphan*/ ) ; 

void usb_hcd_giveback_urb(struct usb_hcd *hcd, struct urb *urb, int status)
{
	struct giveback_urb_bh *bh;
	bool running, high_prio_bh;

	/* pass status to tasklet via unlinked */
	if (likely(!urb->unlinked))
		urb->unlinked = status;

	if (!hcd_giveback_urb_in_bh(hcd) && !is_root_hub(urb->dev)) {
		__usb_hcd_giveback_urb(urb);
		return;
	}

	if (usb_pipeisoc(urb->pipe) || usb_pipeint(urb->pipe)) {
		bh = &hcd->high_prio_bh;
		high_prio_bh = true;
	} else {
		bh = &hcd->low_prio_bh;
		high_prio_bh = false;
	}

	spin_lock(&bh->lock);
	list_add_tail(&urb->urb_list, &bh->head);
	running = bh->running;
	spin_unlock(&bh->lock);

	if (running)
		;
	else if (high_prio_bh)
		tasklet_hi_schedule(&bh->bh);
	else
		tasklet_schedule(&bh->bh);
}