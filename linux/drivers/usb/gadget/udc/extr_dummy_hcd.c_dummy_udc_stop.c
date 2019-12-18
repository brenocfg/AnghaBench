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
struct usb_gadget {int dummy; } ;
struct dummy_hcd {struct dummy* dum; } ;
struct dummy {scalar_t__ callback_usage; int /*<<< orphan*/  lock; int /*<<< orphan*/ * driver; scalar_t__ ints_enabled; } ;

/* Variables and functions */
 struct dummy_hcd* gadget_to_dummy_hcd (struct usb_gadget*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_activity (struct dummy*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int dummy_udc_stop(struct usb_gadget *g)
{
	struct dummy_hcd	*dum_hcd = gadget_to_dummy_hcd(g);
	struct dummy		*dum = dum_hcd->dum;

	spin_lock_irq(&dum->lock);
	dum->ints_enabled = 0;
	stop_activity(dum);

	/* emulate synchronize_irq(): wait for callbacks to finish */
	while (dum->callback_usage > 0) {
		spin_unlock_irq(&dum->lock);
		usleep_range(1000, 2000);
		spin_lock_irq(&dum->lock);
	}

	dum->driver = NULL;
	spin_unlock_irq(&dum->lock);

	return 0;
}