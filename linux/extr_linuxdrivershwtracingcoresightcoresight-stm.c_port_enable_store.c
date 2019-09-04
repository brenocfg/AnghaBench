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
struct stm_drvdata {unsigned long stmsper; int /*<<< orphan*/  spinlock; scalar_t__ base; int /*<<< orphan*/  mode; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CS_LOCK (scalar_t__) ; 
 int /*<<< orphan*/  CS_UNLOCK (scalar_t__) ; 
 scalar_t__ STMSPER ; 
 struct stm_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 scalar_t__ local_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned long,scalar_t__) ; 

__attribute__((used)) static ssize_t port_enable_store(struct device *dev,
				 struct device_attribute *attr,
				 const char *buf, size_t size)
{
	struct stm_drvdata *drvdata = dev_get_drvdata(dev->parent);
	unsigned long val;
	int ret = 0;

	ret = kstrtoul(buf, 16, &val);
	if (ret)
		return ret;

	spin_lock(&drvdata->spinlock);
	drvdata->stmsper = val;

	if (local_read(&drvdata->mode)) {
		CS_UNLOCK(drvdata->base);
		writel_relaxed(drvdata->stmsper, drvdata->base + STMSPER);
		CS_LOCK(drvdata->base);
	}
	spin_unlock(&drvdata->spinlock);

	return size;
}