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
struct imon_context {int display_isopen; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  display_supported; } ;
struct file {struct imon_context* private_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  driver_lock ; 
 int iminor (struct inode*) ; 
 int /*<<< orphan*/  imon_driver ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 struct usb_interface* usb_find_interface (int /*<<< orphan*/ *,int) ; 
 struct imon_context* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int display_open(struct inode *inode, struct file *file)
{
	struct usb_interface *interface;
	struct imon_context *ictx = NULL;
	int subminor;
	int retval = 0;

	/* prevent races with disconnect */
	mutex_lock(&driver_lock);

	subminor = iminor(inode);
	interface = usb_find_interface(&imon_driver, subminor);
	if (!interface) {
		pr_err("could not find interface for minor %d\n", subminor);
		retval = -ENODEV;
		goto exit;
	}
	ictx = usb_get_intfdata(interface);

	if (!ictx) {
		pr_err("no context found for minor %d\n", subminor);
		retval = -ENODEV;
		goto exit;
	}

	mutex_lock(&ictx->lock);

	if (!ictx->display_supported) {
		pr_err("display not supported by device\n");
		retval = -ENODEV;
	} else if (ictx->display_isopen) {
		pr_err("display port is already open\n");
		retval = -EBUSY;
	} else {
		ictx->display_isopen = true;
		file->private_data = ictx;
		dev_dbg(ictx->dev, "display port opened\n");
	}

	mutex_unlock(&ictx->lock);

exit:
	mutex_unlock(&driver_lock);
	return retval;
}