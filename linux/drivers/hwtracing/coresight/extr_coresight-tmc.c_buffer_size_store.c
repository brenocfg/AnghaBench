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
struct tmc_drvdata {scalar_t__ config_type; unsigned long size; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int PAGE_SIZE ; 
 scalar_t__ TMC_CONFIG_TYPE_ETR ; 
 struct tmc_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static ssize_t buffer_size_store(struct device *dev,
				 struct device_attribute *attr,
				 const char *buf, size_t size)
{
	int ret;
	unsigned long val;
	struct tmc_drvdata *drvdata = dev_get_drvdata(dev->parent);

	/* Only permitted for TMC-ETRs */
	if (drvdata->config_type != TMC_CONFIG_TYPE_ETR)
		return -EPERM;

	ret = kstrtoul(buf, 0, &val);
	if (ret)
		return ret;
	/* The buffer size should be page aligned */
	if (val & (PAGE_SIZE - 1))
		return -EINVAL;
	drvdata->size = val;
	return size;
}