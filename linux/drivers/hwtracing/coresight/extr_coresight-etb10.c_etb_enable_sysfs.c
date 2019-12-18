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
struct etb_drvdata {scalar_t__ mode; int /*<<< orphan*/  spinlock; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct coresight_device {int /*<<< orphan*/  refcnt; TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ CS_MODE_DISABLED ; 
 scalar_t__ CS_MODE_PERF ; 
 scalar_t__ CS_MODE_SYSFS ; 
 int EBUSY ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ ) ; 
 struct etb_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int etb_enable_hw (struct etb_drvdata*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int etb_enable_sysfs(struct coresight_device *csdev)
{
	int ret = 0;
	unsigned long flags;
	struct etb_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	spin_lock_irqsave(&drvdata->spinlock, flags);

	/* Don't messup with perf sessions. */
	if (drvdata->mode == CS_MODE_PERF) {
		ret = -EBUSY;
		goto out;
	}

	if (drvdata->mode == CS_MODE_DISABLED) {
		ret = etb_enable_hw(drvdata);
		if (ret)
			goto out;

		drvdata->mode = CS_MODE_SYSFS;
	}

	atomic_inc(csdev->refcnt);
out:
	spin_unlock_irqrestore(&drvdata->spinlock, flags);
	return ret;
}