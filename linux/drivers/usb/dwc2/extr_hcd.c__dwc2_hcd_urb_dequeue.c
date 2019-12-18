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
struct urb {int /*<<< orphan*/  status; int /*<<< orphan*/ * hcpriv; } ;
struct dwc2_hsotg {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dwc2_dump_urb_info (struct usb_hcd*,struct urb*,char*) ; 
 struct dwc2_hsotg* dwc2_hcd_to_hsotg (struct usb_hcd*) ; 
 int dwc2_hcd_urb_dequeue (struct dwc2_hsotg*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int usb_hcd_check_unlink_urb (struct usb_hcd*,struct urb*,int) ; 
 int /*<<< orphan*/  usb_hcd_giveback_urb (struct usb_hcd*,struct urb*,int) ; 
 int /*<<< orphan*/  usb_hcd_unlink_urb_from_ep (struct usb_hcd*,struct urb*) ; 

__attribute__((used)) static int _dwc2_hcd_urb_dequeue(struct usb_hcd *hcd, struct urb *urb,
				 int status)
{
	struct dwc2_hsotg *hsotg = dwc2_hcd_to_hsotg(hcd);
	int rc;
	unsigned long flags;

	dev_dbg(hsotg->dev, "DWC OTG HCD URB Dequeue\n");
	dwc2_dump_urb_info(hcd, urb, "urb_dequeue");

	spin_lock_irqsave(&hsotg->lock, flags);

	rc = usb_hcd_check_unlink_urb(hcd, urb, status);
	if (rc)
		goto out;

	if (!urb->hcpriv) {
		dev_dbg(hsotg->dev, "## urb->hcpriv is NULL ##\n");
		goto out;
	}

	rc = dwc2_hcd_urb_dequeue(hsotg, urb->hcpriv);

	usb_hcd_unlink_urb_from_ep(hcd, urb);

	kfree(urb->hcpriv);
	urb->hcpriv = NULL;

	/* Higher layer software sets URB status */
	spin_unlock(&hsotg->lock);
	usb_hcd_giveback_urb(hcd, urb, status);
	spin_lock(&hsotg->lock);

	dev_dbg(hsotg->dev, "Called usb_hcd_giveback_urb()\n");
	dev_dbg(hsotg->dev, "  urb->status = %d\n", urb->status);
out:
	spin_unlock_irqrestore(&hsotg->lock, flags);

	return rc;
}