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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int (* set_suspend_mode ) (int) ;} ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int EINVAL ; 
 int PM_SUSPEND_MODE_FIRST ; 
 TYPE_1__* eemi_ops ; 
 scalar_t__ likely (int) ; 
 int stub1 (int) ; 
 int suspend_mode ; 
 scalar_t__* suspend_modes ; 
 scalar_t__ sysfs_streq (scalar_t__,char const*) ; 

__attribute__((used)) static ssize_t suspend_mode_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t count)
{
	int md, ret = -EINVAL;

	if (!eemi_ops->set_suspend_mode)
		return ret;

	for (md = PM_SUSPEND_MODE_FIRST; md < ARRAY_SIZE(suspend_modes); md++)
		if (suspend_modes[md] &&
		    sysfs_streq(suspend_modes[md], buf)) {
			ret = 0;
			break;
		}

	if (!ret && md != suspend_mode) {
		ret = eemi_ops->set_suspend_mode(md);
		if (likely(!ret))
			suspend_mode = md;
	}

	return ret ? ret : count;
}