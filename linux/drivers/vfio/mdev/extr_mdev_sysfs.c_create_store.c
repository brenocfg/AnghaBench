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
struct kobject {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  guid_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t UUID_STRING_LEN ; 
 int guid_parse (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrndup (char const*,size_t,int /*<<< orphan*/ ) ; 
 int mdev_device_create (struct kobject*,struct device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t create_store(struct kobject *kobj, struct device *dev,
			    const char *buf, size_t count)
{
	char *str;
	guid_t uuid;
	int ret;

	if ((count < UUID_STRING_LEN) || (count > UUID_STRING_LEN + 1))
		return -EINVAL;

	str = kstrndup(buf, count, GFP_KERNEL);
	if (!str)
		return -ENOMEM;

	ret = guid_parse(str, &uuid);
	kfree(str);
	if (ret)
		return ret;

	ret = mdev_device_create(kobj, dev, &uuid);
	if (ret)
		return ret;

	return count;
}