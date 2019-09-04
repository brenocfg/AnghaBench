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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ STMSPER ; 
 struct stm_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_read (int /*<<< orphan*/ *) ; 
 unsigned long readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t port_enable_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct stm_drvdata *drvdata = dev_get_drvdata(dev->parent);
	unsigned long val;

	if (!local_read(&drvdata->mode)) {
		val = drvdata->stmsper;
	} else {
		spin_lock(&drvdata->spinlock);
		val = readl_relaxed(drvdata->base + STMSPER);
		spin_unlock(&drvdata->spinlock);
	}

	return scnprintf(buf, PAGE_SIZE, "%#lx\n", val);
}