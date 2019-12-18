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
struct usb_hcd {int dummy; } ;
struct urb {int dummy; } ;
struct c67x00_hcd {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  c67x00_release_urb (struct c67x00_hcd*,struct urb*) ; 
 struct c67x00_hcd* hcd_to_c67x00_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int usb_hcd_check_unlink_urb (struct usb_hcd*,struct urb*,int) ; 
 int /*<<< orphan*/  usb_hcd_giveback_urb (struct usb_hcd*,struct urb*,int) ; 
 int /*<<< orphan*/  usb_hcd_unlink_urb_from_ep (struct usb_hcd*,struct urb*) ; 

int c67x00_urb_dequeue(struct usb_hcd *hcd, struct urb *urb, int status)
{
	struct c67x00_hcd *c67x00 = hcd_to_c67x00_hcd(hcd);
	unsigned long flags;
	int rc;

	spin_lock_irqsave(&c67x00->lock, flags);
	rc = usb_hcd_check_unlink_urb(hcd, urb, status);
	if (rc)
		goto done;

	c67x00_release_urb(c67x00, urb);
	usb_hcd_unlink_urb_from_ep(hcd, urb);

	spin_unlock(&c67x00->lock);
	usb_hcd_giveback_urb(hcd, urb, status);
	spin_lock(&c67x00->lock);

	spin_unlock_irqrestore(&c67x00->lock, flags);

	return 0;

 done:
	spin_unlock_irqrestore(&c67x00->lock, flags);
	return rc;
}