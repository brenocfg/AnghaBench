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
struct hidraw {int minor; int exist; struct hid_device* hid; int /*<<< orphan*/  list; int /*<<< orphan*/  list_lock; int /*<<< orphan*/  wait; int /*<<< orphan*/  dev; } ;
struct hid_device {struct hidraw* hidraw; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HIDRAW_MAX_DEVICES ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  hidraw_class ; 
 int /*<<< orphan*/  hidraw_major ; 
 struct hidraw** hidraw_table ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct hidraw*) ; 
 struct hidraw* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  minors_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int hidraw_connect(struct hid_device *hid)
{
	int minor, result;
	struct hidraw *dev;

	/* we accept any HID device, all applications */

	dev = kzalloc(sizeof(struct hidraw), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;

	result = -EINVAL;

	mutex_lock(&minors_lock);

	for (minor = 0; minor < HIDRAW_MAX_DEVICES; minor++) {
		if (hidraw_table[minor])
			continue;
		hidraw_table[minor] = dev;
		result = 0;
		break;
	}

	if (result) {
		mutex_unlock(&minors_lock);
		kfree(dev);
		goto out;
	}

	dev->dev = device_create(hidraw_class, &hid->dev, MKDEV(hidraw_major, minor),
				 NULL, "%s%d", "hidraw", minor);

	if (IS_ERR(dev->dev)) {
		hidraw_table[minor] = NULL;
		mutex_unlock(&minors_lock);
		result = PTR_ERR(dev->dev);
		kfree(dev);
		goto out;
	}

	init_waitqueue_head(&dev->wait);
	spin_lock_init(&dev->list_lock);
	INIT_LIST_HEAD(&dev->list);

	dev->hid = hid;
	dev->minor = minor;

	dev->exist = 1;
	hid->hidraw = dev;

	mutex_unlock(&minors_lock);
out:
	return result;

}