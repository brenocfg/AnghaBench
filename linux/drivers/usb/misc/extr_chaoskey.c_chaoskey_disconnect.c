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
struct usb_interface {int dummy; } ;
struct chaoskey {int present; int /*<<< orphan*/  lock; int /*<<< orphan*/  open; int /*<<< orphan*/  urb; int /*<<< orphan*/  hwrng; scalar_t__ hwrng_registered; } ;

/* Variables and functions */
 int /*<<< orphan*/  chaoskey_class ; 
 int /*<<< orphan*/  chaoskey_free (struct chaoskey*) ; 
 int /*<<< orphan*/  hwrng_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_dbg (struct usb_interface*,char*) ; 
 int /*<<< orphan*/  usb_deregister_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 struct chaoskey* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_poison_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void chaoskey_disconnect(struct usb_interface *interface)
{
	struct chaoskey	*dev;

	usb_dbg(interface, "disconnect");
	dev = usb_get_intfdata(interface);
	if (!dev) {
		usb_dbg(interface, "disconnect failed - no dev");
		return;
	}

	if (dev->hwrng_registered)
		hwrng_unregister(&dev->hwrng);

	usb_deregister_dev(interface, &chaoskey_class);

	usb_set_intfdata(interface, NULL);
	mutex_lock(&dev->lock);

	dev->present = false;
	usb_poison_urb(dev->urb);

	if (!dev->open) {
		mutex_unlock(&dev->lock);
		chaoskey_free(dev);
	} else
		mutex_unlock(&dev->lock);

	usb_dbg(interface, "disconnect done");
}