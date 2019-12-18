#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tmc_drvdata {scalar_t__ size; scalar_t__ mode; int /*<<< orphan*/  spinlock; struct etr_buf* sysfs_buf; scalar_t__ reading; } ;
struct etr_buf {scalar_t__ size; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct coresight_device {TYPE_1__ dev; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 scalar_t__ CS_MODE_PERF ; 
 scalar_t__ CS_MODE_SYSFS ; 
 int EBUSY ; 
 scalar_t__ IS_ERR (struct etr_buf*) ; 
 int PTR_ERR (struct etr_buf*) ; 
 struct etr_buf* READ_ONCE (struct etr_buf*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 struct tmc_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int tmc_etr_enable_hw (struct tmc_drvdata*,struct etr_buf*) ; 
 int /*<<< orphan*/  tmc_etr_free_sysfs_buf (struct etr_buf*) ; 
 struct etr_buf* tmc_etr_setup_sysfs_buf (struct tmc_drvdata*) ; 

__attribute__((used)) static int tmc_enable_etr_sink_sysfs(struct coresight_device *csdev)
{
	int ret = 0;
	unsigned long flags;
	struct tmc_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);
	struct etr_buf *sysfs_buf = NULL, *new_buf = NULL, *free_buf = NULL;

	/*
	 * If we are enabling the ETR from disabled state, we need to make
	 * sure we have a buffer with the right size. The etr_buf is not reset
	 * immediately after we stop the tracing in SYSFS mode as we wait for
	 * the user to collect the data. We may be able to reuse the existing
	 * buffer, provided the size matches. Any allocation has to be done
	 * with the lock released.
	 */
	spin_lock_irqsave(&drvdata->spinlock, flags);
	sysfs_buf = READ_ONCE(drvdata->sysfs_buf);
	if (!sysfs_buf || (sysfs_buf->size != drvdata->size)) {
		spin_unlock_irqrestore(&drvdata->spinlock, flags);

		/* Allocate memory with the locks released */
		free_buf = new_buf = tmc_etr_setup_sysfs_buf(drvdata);
		if (IS_ERR(new_buf))
			return PTR_ERR(new_buf);

		/* Let's try again */
		spin_lock_irqsave(&drvdata->spinlock, flags);
	}

	if (drvdata->reading || drvdata->mode == CS_MODE_PERF) {
		ret = -EBUSY;
		goto out;
	}

	/*
	 * In sysFS mode we can have multiple writers per sink.  Since this
	 * sink is already enabled no memory is needed and the HW need not be
	 * touched, even if the buffer size has changed.
	 */
	if (drvdata->mode == CS_MODE_SYSFS) {
		atomic_inc(csdev->refcnt);
		goto out;
	}

	/*
	 * If we don't have a buffer or it doesn't match the requested size,
	 * use the buffer allocated above. Otherwise reuse the existing buffer.
	 */
	sysfs_buf = READ_ONCE(drvdata->sysfs_buf);
	if (!sysfs_buf || (new_buf && sysfs_buf->size != new_buf->size)) {
		free_buf = sysfs_buf;
		drvdata->sysfs_buf = new_buf;
	}

	ret = tmc_etr_enable_hw(drvdata, drvdata->sysfs_buf);
	if (!ret) {
		drvdata->mode = CS_MODE_SYSFS;
		atomic_inc(csdev->refcnt);
	}
out:
	spin_unlock_irqrestore(&drvdata->spinlock, flags);

	/* Free memory outside the spinlock if need be */
	if (free_buf)
		tmc_etr_free_sysfs_buf(free_buf);

	if (!ret)
		dev_dbg(&csdev->dev, "TMC-ETR enabled\n");

	return ret;
}