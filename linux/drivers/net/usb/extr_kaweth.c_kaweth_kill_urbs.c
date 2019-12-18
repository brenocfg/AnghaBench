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
struct kaweth_device {int /*<<< orphan*/  rx_urb; int /*<<< orphan*/  irq_urb; int /*<<< orphan*/  lowmem_work; int /*<<< orphan*/  tx_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kaweth_kill_urbs(struct kaweth_device *kaweth)
{
	usb_kill_urb(kaweth->irq_urb);
	usb_kill_urb(kaweth->rx_urb);
	usb_kill_urb(kaweth->tx_urb);

	cancel_delayed_work_sync(&kaweth->lowmem_work);

	/* a scheduled work may have resubmitted,
	   we hit them again */
	usb_kill_urb(kaweth->irq_urb);
	usb_kill_urb(kaweth->rx_urb);
}