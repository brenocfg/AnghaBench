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
struct usb_yurex {int disconnected; int /*<<< orphan*/  kref; int /*<<< orphan*/  waitq; int /*<<< orphan*/  async_queue; int /*<<< orphan*/  io_mutex; int /*<<< orphan*/  cntl_urb; int /*<<< orphan*/  urb; } ;
struct usb_interface {int minor; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLL_IN ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_deregister_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 struct usb_yurex* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_poison_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yurex_class ; 
 int /*<<< orphan*/  yurex_delete ; 

__attribute__((used)) static void yurex_disconnect(struct usb_interface *interface)
{
	struct usb_yurex *dev;
	int minor = interface->minor;

	dev = usb_get_intfdata(interface);
	usb_set_intfdata(interface, NULL);

	/* give back our minor */
	usb_deregister_dev(interface, &yurex_class);

	/* prevent more I/O from starting */
	usb_poison_urb(dev->urb);
	usb_poison_urb(dev->cntl_urb);
	mutex_lock(&dev->io_mutex);
	dev->disconnected = 1;
	mutex_unlock(&dev->io_mutex);

	/* wakeup waiters */
	kill_fasync(&dev->async_queue, SIGIO, POLL_IN);
	wake_up_interruptible(&dev->waitq);

	/* decrement our usage count */
	kref_put(&dev->kref, yurex_delete);

	dev_info(&interface->dev, "USB YUREX #%d now disconnected\n", minor);
}