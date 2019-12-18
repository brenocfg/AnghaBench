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
struct gb_svc {int /*<<< orphan*/  action; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  GB_SVC_WATCHDOG_BITE_PANIC_KERNEL ; 
 int /*<<< orphan*/  GB_SVC_WATCHDOG_BITE_RESET_UNIPRO ; 
 scalar_t__ sysfs_streq (char const*,char*) ; 
 struct gb_svc* to_gb_svc (struct device*) ; 

__attribute__((used)) static ssize_t watchdog_action_store(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t len)
{
	struct gb_svc *svc = to_gb_svc(dev);

	if (sysfs_streq(buf, "panic"))
		svc->action = GB_SVC_WATCHDOG_BITE_PANIC_KERNEL;
	else if (sysfs_streq(buf, "reset"))
		svc->action = GB_SVC_WATCHDOG_BITE_RESET_UNIPRO;
	else
		return -EINVAL;

	return len;
}