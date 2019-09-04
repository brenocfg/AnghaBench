#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct roccat_device {unsigned int minor; int exist; int report_size; scalar_t__ cbuf_end; struct hid_device* hid; int /*<<< orphan*/  cbuf_lock; int /*<<< orphan*/  readers_lock; int /*<<< orphan*/  readers; int /*<<< orphan*/  wait; int /*<<< orphan*/  dev; } ;
struct hid_device {TYPE_1__* driver; int /*<<< orphan*/  dev; } ;
struct class {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,unsigned int) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 unsigned int ROCCAT_MAX_DEVICES ; 
 int /*<<< orphan*/  device_create (struct class*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,unsigned int) ; 
 struct roccat_device** devices ; 
 int /*<<< orphan*/  devices_lock ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct roccat_device*) ; 
 struct roccat_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  roccat_major ; 

int roccat_connect(struct class *klass, struct hid_device *hid, int report_size)
{
	unsigned int minor;
	struct roccat_device *device;
	int temp;

	device = kzalloc(sizeof(struct roccat_device), GFP_KERNEL);
	if (!device)
		return -ENOMEM;

	mutex_lock(&devices_lock);

	for (minor = 0; minor < ROCCAT_MAX_DEVICES; ++minor) {
		if (devices[minor])
			continue;
		break;
	}

	if (minor < ROCCAT_MAX_DEVICES) {
		devices[minor] = device;
	} else {
		mutex_unlock(&devices_lock);
		kfree(device);
		return -EINVAL;
	}

	device->dev = device_create(klass, &hid->dev,
			MKDEV(roccat_major, minor), NULL,
			"%s%s%d", "roccat", hid->driver->name, minor);

	if (IS_ERR(device->dev)) {
		devices[minor] = NULL;
		mutex_unlock(&devices_lock);
		temp = PTR_ERR(device->dev);
		kfree(device);
		return temp;
	}

	mutex_unlock(&devices_lock);

	init_waitqueue_head(&device->wait);
	INIT_LIST_HEAD(&device->readers);
	mutex_init(&device->readers_lock);
	mutex_init(&device->cbuf_lock);
	device->minor = minor;
	device->hid = hid;
	device->exist = 1;
	device->cbuf_end = 0;
	device->report_size = report_size;

	return minor;
}