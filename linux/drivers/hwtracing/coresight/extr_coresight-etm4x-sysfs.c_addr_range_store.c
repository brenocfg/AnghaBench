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
typedef  void* u64 ;
struct etmv4_config {int addr_idx; scalar_t__* addr_type; int mode; void** addr_val; } ;
struct etmv4_drvdata {int /*<<< orphan*/  spinlock; struct etmv4_config config; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t EPERM ; 
 scalar_t__ ETM_ADDR_TYPE_NONE ; 
 scalar_t__ ETM_ADDR_TYPE_RANGE ; 
 int ETM_MODE_EXCLUDE ; 
 struct etmv4_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  etm4_set_mode_exclude (struct etmv4_drvdata*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int sscanf (char const*,char*,unsigned long*,unsigned long*) ; 

__attribute__((used)) static ssize_t addr_range_store(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t size)
{
	u8 idx;
	unsigned long val1, val2;
	struct etmv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	struct etmv4_config *config = &drvdata->config;

	if (sscanf(buf, "%lx %lx", &val1, &val2) != 2)
		return -EINVAL;
	/* lower address comparator cannot have a higher address value */
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

	config->addr_val[idx] = (u64)val1;
	config->addr_type[idx] = ETM_ADDR_TYPE_RANGE;
	config->addr_val[idx + 1] = (u64)val2;
	config->addr_type[idx + 1] = ETM_ADDR_TYPE_RANGE;
	/*
	 * Program include or exclude control bits for vinst or vdata
	 * whenever we change addr comparators to ETM_ADDR_TYPE_RANGE
	 */
	etm4_set_mode_exclude(drvdata,
			      config->mode & ETM_MODE_EXCLUDE ? true : false);

	spin_unlock(&drvdata->spinlock);
	return size;
}