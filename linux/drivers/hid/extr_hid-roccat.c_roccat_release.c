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
struct roccat_reader {int /*<<< orphan*/  hid; scalar_t__ exist; int /*<<< orphan*/  open; int /*<<< orphan*/  readers_lock; int /*<<< orphan*/  node; } ;
struct roccat_device {int /*<<< orphan*/  hid; scalar_t__ exist; int /*<<< orphan*/  open; int /*<<< orphan*/  readers_lock; int /*<<< orphan*/  node; } ;
struct inode {int dummy; } ;
struct file {struct roccat_reader* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PM_HINT_NORMAL ; 
 struct roccat_reader** devices ; 
 int /*<<< orphan*/  devices_lock ; 
 int /*<<< orphan*/  hid_hw_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_hw_power (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int iminor (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct roccat_reader*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_emerg (char*,unsigned int) ; 

__attribute__((used)) static int roccat_release(struct inode *inode, struct file *file)
{
	unsigned int minor = iminor(inode);
	struct roccat_reader *reader = file->private_data;
	struct roccat_device *device;

	mutex_lock(&devices_lock);

	device = devices[minor];
	if (!device) {
		mutex_unlock(&devices_lock);
		pr_emerg("roccat device with minor %d doesn't exist\n", minor);
		return -ENODEV;
	}

	mutex_lock(&device->readers_lock);
	list_del(&reader->node);
	mutex_unlock(&device->readers_lock);
	kfree(reader);

	if (!--device->open) {
		/* removing last reader */
		if (device->exist) {
			hid_hw_power(device->hid, PM_HINT_NORMAL);
			hid_hw_close(device->hid);
		} else {
			kfree(device);
		}
	}

	mutex_unlock(&devices_lock);

	return 0;
}