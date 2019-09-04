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
struct wacom {int /*<<< orphan*/  lock; int /*<<< orphan*/  hdev; } ;
struct kobject {int /*<<< orphan*/  parent; } ;
struct kobj_attribute {int dummy; } ;
struct hid_device {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 unsigned char WAC_CMD_UNPAIR_ALL ; 
 struct wacom* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hid_info (int /*<<< orphan*/ ,char*,char const*) ; 
 struct device* kobj_to_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 struct hid_device* to_hid_device (struct device*) ; 
 int wacom_cmd_unpair_remote (struct wacom*,unsigned char) ; 

__attribute__((used)) static ssize_t wacom_store_unpair_remote(struct kobject *kobj,
					 struct kobj_attribute *attr,
					 const char *buf, size_t count)
{
	unsigned char selector = 0;
	struct device *dev = kobj_to_dev(kobj->parent);
	struct hid_device *hdev = to_hid_device(dev);
	struct wacom *wacom = hid_get_drvdata(hdev);
	int err;

	if (!strncmp(buf, "*\n", 2)) {
		selector = WAC_CMD_UNPAIR_ALL;
	} else {
		hid_info(wacom->hdev, "remote: unrecognized unpair code: %s\n",
			 buf);
		return -1;
	}

	mutex_lock(&wacom->lock);

	err = wacom_cmd_unpair_remote(wacom, selector);
	mutex_unlock(&wacom->lock);

	return err < 0 ? err : count;
}