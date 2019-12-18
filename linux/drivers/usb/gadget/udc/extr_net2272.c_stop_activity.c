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
struct usb_gadget_driver {int /*<<< orphan*/  (* disconnect ) (TYPE_1__*) ;} ;
struct TYPE_2__ {scalar_t__ speed; } ;
struct net2272 {int /*<<< orphan*/  lock; TYPE_1__ gadget; int /*<<< orphan*/ * ep; } ;

/* Variables and functions */
 scalar_t__ USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  net2272_dequeue_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net2272_usb_reinit (struct net2272*) ; 
 int /*<<< orphan*/  net2272_usb_reset (struct net2272*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void
stop_activity(struct net2272 *dev, struct usb_gadget_driver *driver)
{
	int i;

	/* don't disconnect if it's not connected */
	if (dev->gadget.speed == USB_SPEED_UNKNOWN)
		driver = NULL;

	/* stop hardware; prevent new request submissions;
	 * and kill any outstanding requests.
	 */
	net2272_usb_reset(dev);
	for (i = 0; i < 4; ++i)
		net2272_dequeue_all(&dev->ep[i]);

	/* report disconnect; the driver is already quiesced */
	if (driver) {
		spin_unlock(&dev->lock);
		driver->disconnect(&dev->gadget);
		spin_lock(&dev->lock);
	}

	net2272_usb_reinit(dev);
}