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
struct pti_device {unsigned long clkdiv; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 struct pti_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  is_power_of_2 (unsigned long) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t
clock_divider_store(struct device *dev, struct device_attribute *attr,
		    const char *buf, size_t size)
{
	struct pti_device *pti = dev_get_drvdata(dev);
	unsigned long val;
	int ret;

	ret = kstrtoul(buf, 10, &val);
	if (ret)
		return ret;

	if (!is_power_of_2(val) || val > 8 || !val)
		return -EINVAL;

	pti->clkdiv = val;

	return size;
}