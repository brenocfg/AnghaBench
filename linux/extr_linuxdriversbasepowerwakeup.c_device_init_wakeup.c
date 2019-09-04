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
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  device_set_wakeup_capable (struct device*,int) ; 
 int /*<<< orphan*/  device_wakeup_disable (struct device*) ; 
 int device_wakeup_enable (struct device*) ; 

int device_init_wakeup(struct device *dev, bool enable)
{
	int ret = 0;

	if (!dev)
		return -EINVAL;

	if (enable) {
		device_set_wakeup_capable(dev, true);
		ret = device_wakeup_enable(dev);
	} else {
		device_wakeup_disable(dev);
		device_set_wakeup_capable(dev, false);
	}

	return ret;
}