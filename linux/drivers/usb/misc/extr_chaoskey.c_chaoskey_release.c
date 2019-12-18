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
struct inode {int dummy; } ;
struct file {struct chaoskey* private_data; } ;
struct chaoskey {scalar_t__ open; int /*<<< orphan*/  lock; int /*<<< orphan*/  present; struct usb_interface* interface; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  chaoskey_free (struct chaoskey*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_dbg (struct usb_interface*,char*,...) ; 

__attribute__((used)) static int chaoskey_release(struct inode *inode, struct file *file)
{
	struct chaoskey *dev = file->private_data;
	struct usb_interface *interface;

	if (dev == NULL)
		return -ENODEV;

	interface = dev->interface;

	usb_dbg(interface, "release");

	mutex_lock(&dev->lock);

	usb_dbg(interface, "open count at release is %d", dev->open);

	if (dev->open <= 0) {
		usb_dbg(interface, "invalid open count (%d)", dev->open);
		mutex_unlock(&dev->lock);
		return -ENODEV;
	}

	--dev->open;

	if (!dev->present) {
		if (dev->open == 0) {
			mutex_unlock(&dev->lock);
			chaoskey_free(dev);
		} else
			mutex_unlock(&dev->lock);
	} else
		mutex_unlock(&dev->lock);

	usb_dbg(interface, "release success");
	return 0;
}