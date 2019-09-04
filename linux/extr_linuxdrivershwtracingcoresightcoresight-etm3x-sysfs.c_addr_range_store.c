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
typedef  int u8 ;
struct etm_config {int addr_idx; scalar_t__* addr_type; unsigned long* addr_val; int enable_ctrl1; } ;
struct etm_drvdata {int /*<<< orphan*/  spinlock; struct etm_config config; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t EPERM ; 
 scalar_t__ ETM_ADDR_TYPE_NONE ; 
 scalar_t__ ETM_ADDR_TYPE_RANGE ; 
 struct etm_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int sscanf (char const*,char*,unsigned long*,unsigned long*) ; 

__attribute__((used)) static ssize_t addr_range_store(struct device *dev,
			      struct device_attribute *attr,
			      const char *buf, size_t size)
{
	u8 idx;
	unsigned long val1, val2;
	struct etm_drvdata *drvdata = dev_get_drvdata(dev->parent);
	struct etm_config *config = &drvdata->config;

	if (sscanf(buf, "%lx %lx", &val1, &val2) != 2)
		return -EINVAL;
	/* Lower address comparator cannot have a higher address value */
	if (val1 > val2)
		return -EINVAL;

	spin_lock(&drvdata->spinlock);
	idx = config->addr_idx;
	if (idx % 2 != 0) {
		spin_unlock(&drvdata->spinlock);
		return -EPERM;
	}
	if (!((config->addr_type[idx] == ETM_ADDR_TYPE_NONE &&
	       config->addr_type[idx + 1] == ETM_ADDR_TYPE_NONE) ||
	      (config->addr_type[idx] == ETM_ADDR_TYPE_RANGE &&
	       config->addr_type[idx + 1] == ETM_ADDR_TYPE_RANGE))) {
		spin_unlock(&drvdata->spinlock);
		return -EPERM;
	}

	config->addr_val[idx] = val1;
	config->addr_type[idx] = ETM_ADDR_TYPE_RANGE;
	config->addr_val[idx + 1] = val2;
	config->addr_type[idx + 1] = ETM_ADDR_TYPE_RANGE;
	config->enable_ctrl1 |= (1 << (idx/2));
	spin_unlock(&drvdata->spinlock);

	return size;
}