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
typedef  int u32 ;
struct etm_config {int* cntr_val; } ;
struct etm_drvdata {int nr_cntr; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  mode; struct etm_config config; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETMCNTVRn (int) ; 
 struct etm_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int etm_readl (struct etm_drvdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sprintf (char*,char*,int,int) ; 

__attribute__((used)) static ssize_t cntr_val_show(struct device *dev,
			     struct device_attribute *attr, char *buf)
{
	int i, ret = 0;
	u32 val;
	struct etm_drvdata *drvdata = dev_get_drvdata(dev->parent);
	struct etm_config *config = &drvdata->config;

	if (!local_read(&drvdata->mode)) {
		spin_lock(&drvdata->spinlock);
		for (i = 0; i < drvdata->nr_cntr; i++)
			ret += sprintf(buf, "counter %d: %x\n",
				       i, config->cntr_val[i]);
		spin_unlock(&drvdata->spinlock);
		return ret;
	}

	for (i = 0; i < drvdata->nr_cntr; i++) {
		val = etm_readl(drvdata, ETMCNTVRn(i));
		ret += sprintf(buf, "counter %d: %x\n", i, val);
	}

	return ret;
}