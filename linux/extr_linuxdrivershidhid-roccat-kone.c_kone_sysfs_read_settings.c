#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kone_settings {int dummy; } ;
struct kone_device {int /*<<< orphan*/  kone_lock; int /*<<< orphan*/  settings; } ;
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct device {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int loff_t ;
struct TYPE_4__ {TYPE_1__* parent; } ;
struct TYPE_3__ {struct device* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 struct kone_device* hid_get_drvdata (int /*<<< orphan*/ ) ; 
 TYPE_2__* kobj_to_dev (struct kobject*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t kone_sysfs_read_settings(struct file *fp, struct kobject *kobj,
		struct bin_attribute *attr, char *buf,
		loff_t off, size_t count) {
	struct device *dev = kobj_to_dev(kobj)->parent->parent;
	struct kone_device *kone = hid_get_drvdata(dev_get_drvdata(dev));

	if (off >= sizeof(struct kone_settings))
		return 0;

	if (off + count > sizeof(struct kone_settings))
		count = sizeof(struct kone_settings) - off;

	mutex_lock(&kone->kone_lock);
	memcpy(buf, ((char const *)&kone->settings) + off, count);
	mutex_unlock(&kone->kone_lock);

	return count;
}