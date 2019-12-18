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
struct tmc_drvdata {char* buf; scalar_t__ mode; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  size; scalar_t__ reading; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct coresight_device {int /*<<< orphan*/  refcnt; TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ CS_MODE_SYSFS ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ ) ; 
 struct tmc_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int tmc_etb_enable_hw (struct tmc_drvdata*) ; 

__attribute__((used)) static int tmc_enable_etf_sink_sysfs(struct coresight_device *csdev)
{
	int ret = 0;
	bool used = false;
	char *buf = NULL;
	unsigned long flags;
	struct tmc_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	/*
	 * If we don't have a buffer release the lock and allocate memory.
	 * Otherwise keep the lock and move along.
	 */
	spin_lock_irqsave(&drvdata->spinlock, flags);
	if (!drvdata->buf) {
		spin_unlock_irqrestore(&drvdata->spinlock, flags);

		/* Allocating the memory here while outside of the spinlock */
		buf = kzalloc(drvdata->size, GFP_KERNEL);
		if (!buf)
			return -ENOMEM;

		/* Let's try again */
		spin_lock_irqsave(&drvdata->spinlock, flags);
	}

	if (drvdata->reading) {
		ret = -EBUSY;
		goto out;
	}

	/*
	 * In sysFS mode we can have multiple writers per sink.  Since this
	 * sink is already enabled no memory is needed and the HW need not be
	 * touched.
	 */
	if (drvdata->mode == CS_MODE_SYSFS) {
		atomic_inc(csdev->refcnt);
		goto out;
	}

	/*
	 * If drvdata::buf isn't NULL, memory was allocated for a previous
	 * trace run but wasn't read.  If so simply zero-out the memory.
	 * Otherwise use the memory allocated above.
	 *
	 * The memory is freed when users read the buffer using the
	 * /dev/xyz.{etf|etb} interface.  See tmc_read_unprepare_etf() for
	 * details.
	 */
	if (drvdata->buf) {
		memset(drvdata->buf, 0, drvdata->size);
	} else {
		used = true;
		drvdata->buf = buf;
	}

	ret = tmc_etb_enable_hw(drvdata);
	if (!ret) {
		drvdata->mode = CS_MODE_SYSFS;
		atomic_inc(csdev->refcnt);
	} else {
		/* Free up the buffer if we failed to enable */
		used = false;
	}
out:
	spin_unlock_irqrestore(&drvdata->spinlock, flags);

	/* Free memory outside the spinlock if need be */
	if (!used)
		kfree(buf);

	return ret;
}