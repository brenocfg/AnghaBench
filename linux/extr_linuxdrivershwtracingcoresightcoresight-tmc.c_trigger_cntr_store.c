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
struct tmc_drvdata {unsigned long trigger_cntr; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct tmc_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t trigger_cntr_store(struct device *dev,
			     struct device_attribute *attr,
			     const char *buf, size_t size)
{
	int ret;
	unsigned long val;
	struct tmc_drvdata *drvdata = dev_get_drvdata(dev->parent);

	ret = kstrtoul(buf, 16, &val);
	if (ret)
		return ret;

	drvdata->trigger_cntr = val;
	return size;
}