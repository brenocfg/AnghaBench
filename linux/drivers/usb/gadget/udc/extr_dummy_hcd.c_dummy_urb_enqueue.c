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
struct usb_hcd {int dummy; } ;
struct urbp {int /*<<< orphan*/  urbp_list; scalar_t__ miter_started; struct urb* urb; } ;
struct urb {scalar_t__ dev; int error_count; int /*<<< orphan*/  pipe; struct urbp* hcpriv; } ;
struct dummy_hcd {scalar_t__ udev; TYPE_1__* dum; int /*<<< orphan*/  timer; struct urbp* next_frame_urbp; int /*<<< orphan*/  urbp_list; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ PIPE_CONTROL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dummy_dev (struct dummy_hcd*) ; 
 int dummy_validate_stream (struct dummy_hcd*,struct urb*) ; 
 struct dummy_hcd* hcd_to_dummy_hcd (struct usb_hcd*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree (struct urbp*) ; 
 struct urbp* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usb_get_dev (scalar_t__) ; 
 int usb_hcd_link_urb_to_ep (struct usb_hcd*,struct urb*) ; 
 scalar_t__ usb_pipetype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dummy_urb_enqueue(
	struct usb_hcd			*hcd,
	struct urb			*urb,
	gfp_t				mem_flags
) {
	struct dummy_hcd *dum_hcd;
	struct urbp	*urbp;
	unsigned long	flags;
	int		rc;

	urbp = kmalloc(sizeof *urbp, mem_flags);
	if (!urbp)
		return -ENOMEM;
	urbp->urb = urb;
	urbp->miter_started = 0;

	dum_hcd = hcd_to_dummy_hcd(hcd);
	spin_lock_irqsave(&dum_hcd->dum->lock, flags);

	rc = dummy_validate_stream(dum_hcd, urb);
	if (rc) {
		kfree(urbp);
		goto done;
	}

	rc = usb_hcd_link_urb_to_ep(hcd, urb);
	if (rc) {
		kfree(urbp);
		goto done;
	}

	if (!dum_hcd->udev) {
		dum_hcd->udev = urb->dev;
		usb_get_dev(dum_hcd->udev);
	} else if (unlikely(dum_hcd->udev != urb->dev))
		dev_err(dummy_dev(dum_hcd), "usb_device address has changed!\n");

	list_add_tail(&urbp->urbp_list, &dum_hcd->urbp_list);
	urb->hcpriv = urbp;
	if (!dum_hcd->next_frame_urbp)
		dum_hcd->next_frame_urbp = urbp;
	if (usb_pipetype(urb->pipe) == PIPE_CONTROL)
		urb->error_count = 1;		/* mark as a new urb */

	/* kick the scheduler, it'll do the rest */
	if (!timer_pending(&dum_hcd->timer))
		mod_timer(&dum_hcd->timer, jiffies + 1);

 done:
	spin_unlock_irqrestore(&dum_hcd->dum->lock, flags);
	return rc;
}