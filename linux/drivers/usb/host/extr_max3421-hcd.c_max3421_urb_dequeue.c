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
struct max3421_hcd {int /*<<< orphan*/  lock; int /*<<< orphan*/  spi_thread; int /*<<< orphan*/  todo; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_UNLINK ; 
 struct max3421_hcd* hcd_to_max3421 (struct usb_hcd*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int usb_hcd_check_unlink_urb (struct usb_hcd*,struct urb*,int) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
max3421_urb_dequeue(struct usb_hcd *hcd, struct urb *urb, int status)
{
	struct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	unsigned long flags;
	int retval;

	spin_lock_irqsave(&max3421_hcd->lock, flags);

	/*
	 * This will set urb->unlinked which in turn causes the entry
	 * to be dropped at the next opportunity.
	 */
	retval = usb_hcd_check_unlink_urb(hcd, urb, status);
	if (retval == 0) {
		set_bit(CHECK_UNLINK, &max3421_hcd->todo);
		wake_up_process(max3421_hcd->spi_thread);
	}
	spin_unlock_irqrestore(&max3421_hcd->lock, flags);
	return retval;
}