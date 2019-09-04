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
struct tmc_drvdata {scalar_t__ config_type; int reading; scalar_t__ mode; int /*<<< orphan*/  spinlock; int /*<<< orphan*/ * etr_buf; } ;

/* Variables and functions */
 scalar_t__ CS_MODE_PERF ; 
 scalar_t__ CS_MODE_SYSFS ; 
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ TMC_CONFIG_TYPE_ETR ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tmc_etr_disable_hw (struct tmc_drvdata*) ; 

int tmc_read_prepare_etr(struct tmc_drvdata *drvdata)
{
	int ret = 0;
	unsigned long flags;

	/* config types are set a boot time and never change */
	if (WARN_ON_ONCE(drvdata->config_type != TMC_CONFIG_TYPE_ETR))
		return -EINVAL;

	spin_lock_irqsave(&drvdata->spinlock, flags);
	if (drvdata->reading) {
		ret = -EBUSY;
		goto out;
	}

	/* Don't interfere if operated from Perf */
	if (drvdata->mode == CS_MODE_PERF) {
		ret = -EINVAL;
		goto out;
	}

	/* If drvdata::etr_buf is NULL the trace data has been read already */
	if (drvdata->etr_buf == NULL) {
		ret = -EINVAL;
		goto out;
	}

	/* Disable the TMC if need be */
	if (drvdata->mode == CS_MODE_SYSFS)
		tmc_etr_disable_hw(drvdata);

	drvdata->reading = true;
out:
	spin_unlock_irqrestore(&drvdata->spinlock, flags);

	return ret;
}