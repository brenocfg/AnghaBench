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
struct chaoskey {int /*<<< orphan*/  lock; int /*<<< orphan*/  open; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  chaoskey_driver ; 
 int /*<<< orphan*/  iminor (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_dbg (struct usb_interface*,char*) ; 
 struct usb_interface* usb_find_interface (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct chaoskey* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int chaoskey_open(struct inode *inode, struct file *file)
{
	struct chaoskey *dev;
	struct usb_interface *interface;

	/* get the interface from minor number and driver information */
	interface = usb_find_interface(&chaoskey_driver, iminor(inode));
	if (!interface)
		return -ENODEV;

	usb_dbg(interface, "open");

	dev = usb_get_intfdata(interface);
	if (!dev) {
		usb_dbg(interface, "open (dev)");
		return -ENODEV;
	}

	file->private_data = dev;
	mutex_lock(&dev->lock);
	++dev->open;
	mutex_unlock(&dev->lock);

	usb_dbg(interface, "open success");
	return 0;
}