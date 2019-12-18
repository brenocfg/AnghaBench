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
struct usb_gadget {int /*<<< orphan*/  dev; } ;
struct dummy_hcd {int dummy; } ;
struct dummy {int pullup; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  dummy_hcd_to_hcd (struct dummy_hcd*) ; 
 struct dummy* gadget_dev_to_dummy (int /*<<< orphan*/ *) ; 
 struct dummy_hcd* gadget_to_dummy_hcd (struct usb_gadget*) ; 
 int /*<<< orphan*/  set_link_state (struct dummy_hcd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_hcd_poll_rh_status (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dummy_pullup(struct usb_gadget *_gadget, int value)
{
	struct dummy_hcd *dum_hcd;
	struct dummy	*dum;
	unsigned long	flags;

	dum = gadget_dev_to_dummy(&_gadget->dev);
	dum_hcd = gadget_to_dummy_hcd(_gadget);

	spin_lock_irqsave(&dum->lock, flags);
	dum->pullup = (value != 0);
	set_link_state(dum_hcd);
	spin_unlock_irqrestore(&dum->lock, flags);

	usb_hcd_poll_rh_status(dummy_hcd_to_hcd(dum_hcd));
	return 0;
}