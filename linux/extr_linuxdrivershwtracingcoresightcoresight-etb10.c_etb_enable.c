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
typedef  scalar_t__ u32 ;
struct etb_drvdata {int /*<<< orphan*/  dev; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct coresight_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_MODE_DISABLED ; 
 scalar_t__ CS_MODE_PERF ; 
 scalar_t__ CS_MODE_SYSFS ; 
 int EBUSY ; 
 struct etb_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  etb_enable_hw (struct etb_drvdata*) ; 
 scalar_t__ local_cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int etb_enable(struct coresight_device *csdev, u32 mode)
{
	u32 val;
	unsigned long flags;
	struct etb_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	val = local_cmpxchg(&drvdata->mode,
			    CS_MODE_DISABLED, mode);
	/*
	 * When accessing from Perf, a HW buffer can be handled
	 * by a single trace entity.  In sysFS mode many tracers
	 * can be logging to the same HW buffer.
	 */
	if (val == CS_MODE_PERF)
		return -EBUSY;

	/* Don't let perf disturb sysFS sessions */
	if (val == CS_MODE_SYSFS && mode == CS_MODE_PERF)
		return -EBUSY;

	/* Nothing to do, the tracer is already enabled. */
	if (val == CS_MODE_SYSFS)
		goto out;

	spin_lock_irqsave(&drvdata->spinlock, flags);
	etb_enable_hw(drvdata);
	spin_unlock_irqrestore(&drvdata->spinlock, flags);

out:
	dev_info(drvdata->dev, "ETB enabled\n");
	return 0;
}