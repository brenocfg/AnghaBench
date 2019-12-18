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
struct tmc_drvdata {scalar_t__ config_type; scalar_t__ mode; int reading; int /*<<< orphan*/  spinlock; struct etr_buf* sysfs_buf; } ;
struct etr_buf {int dummy; } ;

/* Variables and functions */
 scalar_t__ CS_MODE_SYSFS ; 
 int EINVAL ; 
 scalar_t__ TMC_CONFIG_TYPE_ETR ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __tmc_etr_enable_hw (struct tmc_drvdata*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tmc_etr_free_sysfs_buf (struct etr_buf*) ; 

int tmc_read_unprepare_etr(struct tmc_drvdata *drvdata)
{
	unsigned long flags;
	struct etr_buf *sysfs_buf = NULL;

	/* config types are set a boot time and never change */
	if (WARN_ON_ONCE(drvdata->config_type != TMC_CONFIG_TYPE_ETR))
		return -EINVAL;

	spin_lock_irqsave(&drvdata->spinlock, flags);

	/* RE-enable the TMC if need be */
	if (drvdata->mode == CS_MODE_SYSFS) {
		/*
		 * The trace run will continue with the same allocated trace
		 * buffer. Since the tracer is still enabled drvdata::buf can't
		 * be NULL.
		 */
		__tmc_etr_enable_hw(drvdata);
	} else {
		/*
		 * The ETR is not tracing and the buffer was just read.
		 * As such prepare to free the trace buffer.
		 */
		sysfs_buf = drvdata->sysfs_buf;
		drvdata->sysfs_buf = NULL;
	}

	drvdata->reading = false;
	spin_unlock_irqrestore(&drvdata->spinlock, flags);

	/* Free allocated memory out side of the spinlock */
	if (sysfs_buf)
		tmc_etr_free_sysfs_buf(sysfs_buf);

	return 0;
}