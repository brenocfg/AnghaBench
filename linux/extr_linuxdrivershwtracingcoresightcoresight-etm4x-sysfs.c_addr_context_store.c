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
struct etmv4_config {size_t addr_idx; int* addr_acc; } ;
struct etmv4_drvdata {int numcidc; int numvmidc; int /*<<< orphan*/  spinlock; struct etmv4_config config; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int BIT (int) ; 
 size_t EINVAL ; 
 struct etmv4_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t addr_context_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t size)
{
	u8 idx;
	unsigned long val;
	struct etmv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	struct etmv4_config *config = &drvdata->config;

	if (kstrtoul(buf, 16, &val))
		return -EINVAL;
	if ((drvdata->numcidc <= 1) && (drvdata->numvmidc <= 1))
		return -EINVAL;
	if (val >=  (drvdata->numcidc >= drvdata->numvmidc ?
		     drvdata->numcidc : drvdata->numvmidc))
		return -EINVAL;

	spin_lock(&drvdata->spinlock);
	idx = config->addr_idx;
	/* clear context ID comparator bits[6:4] */
	config->addr_acc[idx] &= ~(BIT(4) | BIT(5) | BIT(6));
	config->addr_acc[idx] |= (val << 4);
	spin_unlock(&drvdata->spinlock);
	return size;
}