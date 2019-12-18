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
struct usb_idmouse {scalar_t__ open; int /*<<< orphan*/  lock; int /*<<< orphan*/  present; } ;
struct inode {int dummy; } ;
struct file {struct usb_idmouse* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  idmouse_delete (struct usb_idmouse*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_disc_mutex ; 

__attribute__((used)) static int idmouse_release(struct inode *inode, struct file *file)
{
	struct usb_idmouse *dev;

	dev = file->private_data;

	if (dev == NULL)
		return -ENODEV;

	mutex_lock(&open_disc_mutex);
	/* lock our device */
	mutex_lock(&dev->lock);

	/* are we really open? */
	if (dev->open <= 0) {
		mutex_unlock(&dev->lock);
		mutex_unlock(&open_disc_mutex);
		return -ENODEV;
	}

	--dev->open;

	if (!dev->present) {
		/* the device was unplugged before the file was released */
		mutex_unlock(&dev->lock);
		mutex_unlock(&open_disc_mutex);
		idmouse_delete(dev);
	} else {
		mutex_unlock(&dev->lock);
		mutex_unlock(&open_disc_mutex);
	}
	return 0;
}