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
struct etm_drvdata {unsigned long traceid; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int ssize_t ;

/* Variables and functions */
 unsigned long ETM_TRACEID_MASK ; 
 struct etm_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t traceid_store(struct device *dev,
			     struct device_attribute *attr,
			     const char *buf, size_t size)
{
	int ret;
	unsigned long val;
	struct etm_drvdata *drvdata = dev_get_drvdata(dev->parent);

	ret = kstrtoul(buf, 16, &val);
	if (ret)
		return ret;

	drvdata->traceid = val & ETM_TRACEID_MASK;
	return size;
}