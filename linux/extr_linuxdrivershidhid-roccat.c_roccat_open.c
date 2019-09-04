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
struct roccat_reader {int /*<<< orphan*/  node; int /*<<< orphan*/  cbuf_start; struct roccat_device* device; } ;
struct roccat_device {int /*<<< orphan*/  readers_lock; int /*<<< orphan*/  readers; int /*<<< orphan*/  cbuf_end; int /*<<< orphan*/  open; int /*<<< orphan*/  hid; } ;
struct inode {int dummy; } ;
struct file {struct roccat_reader* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PM_HINT_FULLON ; 
 int /*<<< orphan*/  PM_HINT_NORMAL ; 
 struct roccat_device** devices ; 
 int /*<<< orphan*/  devices_lock ; 
 int hid_hw_open (int /*<<< orphan*/ ) ; 
 int hid_hw_power (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int iminor (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct roccat_reader*) ; 
 struct roccat_reader* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_emerg (char*,unsigned int) ; 

__attribute__((used)) static int roccat_open(struct inode *inode, struct file *file)
{
	unsigned int minor = iminor(inode);
	struct roccat_reader *reader;
	struct roccat_device *device;
	int error = 0;

	reader = kzalloc(sizeof(struct roccat_reader), GFP_KERNEL);
	if (!reader)
		return -ENOMEM;

	mutex_lock(&devices_lock);

	device = devices[minor];

	if (!device) {
		pr_emerg("roccat device with minor %d doesn't exist\n", minor);
		error = -ENODEV;
		goto exit_err_devices;
	}

	mutex_lock(&device->readers_lock);

	if (!device->open++) {
		/* power on device on adding first reader */
		error = hid_hw_power(device->hid, PM_HINT_FULLON);
		if (error < 0) {
			--device->open;
			goto exit_err_readers;
		}

		error = hid_hw_open(device->hid);
		if (error < 0) {
			hid_hw_power(device->hid, PM_HINT_NORMAL);
			--device->open;
			goto exit_err_readers;
		}
	}

	reader->device = device;
	/* new reader doesn't get old events */
	reader->cbuf_start = device->cbuf_end;

	list_add_tail(&reader->node, &device->readers);
	file->private_data = reader;

exit_err_readers:
	mutex_unlock(&device->readers_lock);
exit_err_devices:
	mutex_unlock(&devices_lock);
	if (error)
		kfree(reader);
	return error;
}