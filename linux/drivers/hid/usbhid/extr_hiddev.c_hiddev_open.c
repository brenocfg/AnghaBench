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
struct hiddev_list {struct hiddev* hiddev; int /*<<< orphan*/  node; int /*<<< orphan*/  thread_lock; } ;
struct hiddev {int /*<<< orphan*/  list_lock; int /*<<< orphan*/  existancelock; struct hid_device* hid; scalar_t__ exist; int /*<<< orphan*/  open; int /*<<< orphan*/  list; } ;
struct hid_device {struct hiddev* hiddev; } ;
struct file {struct hiddev_list* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PM_HINT_FULLON ; 
 int /*<<< orphan*/  PM_HINT_NORMAL ; 
 int hid_hw_open (struct hid_device*) ; 
 int hid_hw_power (struct hid_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iminor (struct inode*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct hid_device* usb_get_intfdata (struct usb_interface*) ; 
 struct usb_interface* usbhid_find_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (struct hiddev_list*) ; 
 struct hiddev_list* vzalloc (int) ; 

__attribute__((used)) static int hiddev_open(struct inode *inode, struct file *file)
{
	struct hiddev_list *list;
	struct usb_interface *intf;
	struct hid_device *hid;
	struct hiddev *hiddev;
	int res;

	intf = usbhid_find_interface(iminor(inode));
	if (!intf)
		return -ENODEV;
	hid = usb_get_intfdata(intf);
	hiddev = hid->hiddev;

	if (!(list = vzalloc(sizeof(struct hiddev_list))))
		return -ENOMEM;
	mutex_init(&list->thread_lock);
	list->hiddev = hiddev;
	file->private_data = list;

	/*
	 * no need for locking because the USB major number
	 * is shared which usbcore guards against disconnect
	 */
	if (list->hiddev->exist) {
		if (!list->hiddev->open++) {
			res = hid_hw_open(hiddev->hid);
			if (res < 0)
				goto bail;
		}
	} else {
		res = -ENODEV;
		goto bail;
	}

	spin_lock_irq(&list->hiddev->list_lock);
	list_add_tail(&list->node, &hiddev->list);
	spin_unlock_irq(&list->hiddev->list_lock);

	mutex_lock(&hiddev->existancelock);
	/*
	 * recheck exist with existance lock held to
	 * avoid opening a disconnected device
	 */
	if (!list->hiddev->exist) {
		res = -ENODEV;
		goto bail_unlock;
	}
	if (!list->hiddev->open++)
		if (list->hiddev->exist) {
			struct hid_device *hid = hiddev->hid;
			res = hid_hw_power(hid, PM_HINT_FULLON);
			if (res < 0)
				goto bail_unlock;
			res = hid_hw_open(hid);
			if (res < 0)
				goto bail_normal_power;
		}
	mutex_unlock(&hiddev->existancelock);
	return 0;
bail_normal_power:
	hid_hw_power(hid, PM_HINT_NORMAL);
bail_unlock:
	mutex_unlock(&hiddev->existancelock);

	spin_lock_irq(&list->hiddev->list_lock);
	list_del(&list->node);
	spin_unlock_irq(&list->hiddev->list_lock);
bail:
	file->private_data = NULL;
	vfree(list);
	return res;
}