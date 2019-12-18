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
struct zd_usb_rx {int urbs_count; int /*<<< orphan*/  lock; struct urb** urbs; } ;
struct zd_usb {struct zd_usb_rx rx; } ;
struct urb {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RX_URBS_COUNT ; 
 int /*<<< orphan*/  ZD_ASSERT (int) ; 
 struct urb* alloc_rx_urb (struct zd_usb*) ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_rx_urb (struct urb*) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 struct urb** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (struct urb*) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zd_usb_dev (struct zd_usb*) ; 

__attribute__((used)) static int __zd_usb_enable_rx(struct zd_usb *usb)
{
	int i, r;
	struct zd_usb_rx *rx = &usb->rx;
	struct urb **urbs;

	dev_dbg_f(zd_usb_dev(usb), "\n");

	r = -ENOMEM;
	urbs = kcalloc(RX_URBS_COUNT, sizeof(struct urb *), GFP_KERNEL);
	if (!urbs)
		goto error;
	for (i = 0; i < RX_URBS_COUNT; i++) {
		urbs[i] = alloc_rx_urb(usb);
		if (!urbs[i])
			goto error;
	}

	ZD_ASSERT(!irqs_disabled());
	spin_lock_irq(&rx->lock);
	if (rx->urbs) {
		spin_unlock_irq(&rx->lock);
		r = 0;
		goto error;
	}
	rx->urbs = urbs;
	rx->urbs_count = RX_URBS_COUNT;
	spin_unlock_irq(&rx->lock);

	for (i = 0; i < RX_URBS_COUNT; i++) {
		r = usb_submit_urb(urbs[i], GFP_KERNEL);
		if (r)
			goto error_submit;
	}

	return 0;
error_submit:
	for (i = 0; i < RX_URBS_COUNT; i++) {
		usb_kill_urb(urbs[i]);
	}
	spin_lock_irq(&rx->lock);
	rx->urbs = NULL;
	rx->urbs_count = 0;
	spin_unlock_irq(&rx->lock);
error:
	if (urbs) {
		for (i = 0; i < RX_URBS_COUNT; i++)
			free_rx_urb(urbs[i]);
	}
	return r;
}