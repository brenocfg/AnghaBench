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
typedef  size_t u8 ;
struct etm_config {size_t addr_idx; scalar_t__* addr_type; unsigned long* addr_val; } ;
struct etm_drvdata {int /*<<< orphan*/  spinlock; struct etm_config config; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ETM_ADDR_TYPE_NONE ; 
 scalar_t__ ETM_ADDR_TYPE_SINGLE ; 
 struct etm_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t addr_single_store(struct device *dev,
				 struct device_attribute *attr,
				 const char *buf, size_t size)
{
	u8 idx;
	int ret;
	unsigned long val;
	struct etm_drvdata *drvdata = dev_get_drvdata(dev->parent);
	struct etm_config *config = &drvdata->config;

	ret = kstrtoul(buf, 16, &val);
	if (ret)
		return ret;

	spin_lock(&drvdata->spinlock);
	idx = config->addr_idx;
	if (!(config->addr_type[idx] == ETM_ADDR_TYPE_NONE ||
	      config->addr_type[idx] == ETM_ADDR_TYPE_SINGLE)) {
		spin_unlock(&drvdata->spinlock);
		return -EINVAL;
	}

	config->addr_val[idx] = val;
	config->addr_type[idx] = ETM_ADDR_TYPE_SINGLE;
	spin_unlock(&drvdata->spinlock);

	return size;
}