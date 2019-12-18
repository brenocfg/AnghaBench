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
struct urb {int status; int /*<<< orphan*/  hcpriv; TYPE_1__* ep; int /*<<< orphan*/  dev; } ;
struct octeon_hcd {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  hcpriv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cvmx_usb_cancel (struct octeon_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct octeon_hcd* hcd_to_octeon (struct usb_hcd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int usb_hcd_check_unlink_urb (struct usb_hcd*,struct urb*,int) ; 

__attribute__((used)) static int octeon_usb_urb_dequeue(struct usb_hcd *hcd,
				  struct urb *urb,
				  int status)
{
	struct octeon_hcd *usb = hcd_to_octeon(hcd);
	unsigned long flags;
	int rc;

	if (!urb->dev)
		return -EINVAL;

	spin_lock_irqsave(&usb->lock, flags);

	rc = usb_hcd_check_unlink_urb(hcd, urb, status);
	if (rc)
		goto out;

	urb->status = status;
	cvmx_usb_cancel(usb, urb->ep->hcpriv, urb->hcpriv);

out:
	spin_unlock_irqrestore(&usb->lock, flags);

	return rc;
}