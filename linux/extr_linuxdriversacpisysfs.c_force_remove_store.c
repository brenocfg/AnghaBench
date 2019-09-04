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
struct kobj_attribute {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int strtobool (char const*,int*) ; 

__attribute__((used)) static ssize_t force_remove_store(struct kobject *kobj,
				  struct kobj_attribute *attr,
				  const char *buf, size_t size)
{
	bool val;
	int ret;

	ret = strtobool(buf, &val);
	if (ret < 0)
		return ret;

	if (val) {
		pr_err("Enabling force_remove is not supported anymore. Please report to linux-acpi@vger.kernel.org if you depend on this functionality\n");
		return -EINVAL;
	}
	return size;
}