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
struct etm_config {unsigned long seq_curr_state; } ;
struct etm_drvdata {int /*<<< orphan*/  spinlock; int /*<<< orphan*/  base; int /*<<< orphan*/  mode; struct etm_config config; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CS_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CS_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETMSQR ; 
 unsigned long ETM_SQR_MASK ; 
 struct etm_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 unsigned long etm_readl (struct etm_drvdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long) ; 

__attribute__((used)) static ssize_t seq_curr_state_show(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	unsigned long val, flags;
	struct etm_drvdata *drvdata = dev_get_drvdata(dev->parent);
	struct etm_config *config = &drvdata->config;

	if (!local_read(&drvdata->mode)) {
		val = config->seq_curr_state;
		goto out;
	}

	pm_runtime_get_sync(dev->parent);
	spin_lock_irqsave(&drvdata->spinlock, flags);

	CS_UNLOCK(drvdata->base);
	val = (etm_readl(drvdata, ETMSQR) & ETM_SQR_MASK);
	CS_LOCK(drvdata->base);

	spin_unlock_irqrestore(&drvdata->spinlock, flags);
	pm_runtime_put(dev->parent);
out:
	return sprintf(buf, "%#lx\n", val);
}