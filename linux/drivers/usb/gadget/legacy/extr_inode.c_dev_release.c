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
struct inode {int dummy; } ;
struct file {struct dev_data* private_data; } ;
struct dev_data {int gadget_registered; int /*<<< orphan*/  lock; int /*<<< orphan*/  state; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_DEV_DISABLED ; 
 int /*<<< orphan*/  gadgetfs_driver ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_dev (struct dev_data*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_gadget_unregister_driver (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dev_release (struct inode *inode, struct file *fd)
{
	struct dev_data		*dev = fd->private_data;

	/* closing ep0 === shutdown all */

	if (dev->gadget_registered) {
		usb_gadget_unregister_driver (&gadgetfs_driver);
		dev->gadget_registered = false;
	}

	/* at this point "good" hardware has disconnected the
	 * device from USB; the host won't see it any more.
	 * alternatively, all host requests will time out.
	 */

	kfree (dev->buf);
	dev->buf = NULL;

	/* other endpoints were all decoupled from this device */
	spin_lock_irq(&dev->lock);
	dev->state = STATE_DEV_DISABLED;
	spin_unlock_irq(&dev->lock);

	put_dev (dev);
	return 0;
}