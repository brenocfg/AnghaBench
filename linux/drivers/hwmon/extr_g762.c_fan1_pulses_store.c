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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int do_set_fan_pulses (struct device*,unsigned long) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t fan1_pulses_store(struct device *dev,
				 struct device_attribute *da, const char *buf,
				 size_t count)
{
	unsigned long val;
	int ret;

	if (kstrtoul(buf, 10, &val))
		return -EINVAL;

	ret = do_set_fan_pulses(dev, val);
	if (ret < 0)
		return ret;

	return count;
}