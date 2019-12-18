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
struct thermal_cooling_device {TYPE_1__* ops; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int (* get_cur_state ) (struct thermal_cooling_device*,unsigned long*) ;} ;

/* Variables and functions */
 int sprintf (char*,char*,unsigned long) ; 
 int stub1 (struct thermal_cooling_device*,unsigned long*) ; 
 struct thermal_cooling_device* to_cooling_device (struct device*) ; 

__attribute__((used)) static ssize_t cur_state_show(struct device *dev, struct device_attribute *attr,
			      char *buf)
{
	struct thermal_cooling_device *cdev = to_cooling_device(dev);
	unsigned long state;
	int ret;

	ret = cdev->ops->get_cur_state(cdev, &state);
	if (ret)
		return ret;
	return sprintf(buf, "%ld\n", state);
}