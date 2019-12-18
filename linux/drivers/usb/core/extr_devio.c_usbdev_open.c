#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_device {scalar_t__ state; int /*<<< orphan*/  dev; int /*<<< orphan*/  filelist; } ;
struct usb_dev_state {int interface_allowed_mask; int /*<<< orphan*/  list; int /*<<< orphan*/  cred; int /*<<< orphan*/  disc_pid; int /*<<< orphan*/  wait_for_resume; int /*<<< orphan*/  wait; int /*<<< orphan*/  memory_list; int /*<<< orphan*/  async_completed; int /*<<< orphan*/  async_pending; int /*<<< orphan*/  lock; struct file* file; struct usb_device* dev; } ;
struct inode {int /*<<< orphan*/  i_rdev; } ;
struct file {struct usb_dev_state* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ USB_DEVICE_MAJOR ; 
 scalar_t__ USB_STATE_NOTATTACHED ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  get_current_cred () ; 
 int /*<<< orphan*/  get_pid (int /*<<< orphan*/ ) ; 
 scalar_t__ imajor (struct inode*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct usb_dev_state*) ; 
 struct usb_dev_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  snoop (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_pid (TYPE_1__*) ; 
 int /*<<< orphan*/  task_pid_nr (TYPE_1__*) ; 
 int usb_autoresume_device (struct usb_device*) ; 
 int /*<<< orphan*/  usb_lock_device (struct usb_device*) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_unlock_device (struct usb_device*) ; 
 struct usb_device* usbdev_lookup_by_devt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbdev_open(struct inode *inode, struct file *file)
{
	struct usb_device *dev = NULL;
	struct usb_dev_state *ps;
	int ret;

	ret = -ENOMEM;
	ps = kzalloc(sizeof(struct usb_dev_state), GFP_KERNEL);
	if (!ps)
		goto out_free_ps;

	ret = -ENODEV;

	/* usbdev device-node */
	if (imajor(inode) == USB_DEVICE_MAJOR)
		dev = usbdev_lookup_by_devt(inode->i_rdev);
	if (!dev)
		goto out_free_ps;

	usb_lock_device(dev);
	if (dev->state == USB_STATE_NOTATTACHED)
		goto out_unlock_device;

	ret = usb_autoresume_device(dev);
	if (ret)
		goto out_unlock_device;

	ps->dev = dev;
	ps->file = file;
	ps->interface_allowed_mask = 0xFFFFFFFF; /* 32 bits */
	spin_lock_init(&ps->lock);
	INIT_LIST_HEAD(&ps->list);
	INIT_LIST_HEAD(&ps->async_pending);
	INIT_LIST_HEAD(&ps->async_completed);
	INIT_LIST_HEAD(&ps->memory_list);
	init_waitqueue_head(&ps->wait);
	init_waitqueue_head(&ps->wait_for_resume);
	ps->disc_pid = get_pid(task_pid(current));
	ps->cred = get_current_cred();
	smp_wmb();

	/* Can't race with resume; the device is already active */
	list_add_tail(&ps->list, &dev->filelist);
	file->private_data = ps;
	usb_unlock_device(dev);
	snoop(&dev->dev, "opened by process %d: %s\n", task_pid_nr(current),
			current->comm);
	return ret;

 out_unlock_device:
	usb_unlock_device(dev);
	usb_put_dev(dev);
 out_free_ps:
	kfree(ps);
	return ret;
}