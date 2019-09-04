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
struct tmc_drvdata {scalar_t__ mode; int /*<<< orphan*/  dev; int /*<<< orphan*/  spinlock; scalar_t__ reading; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct coresight_device {TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ CS_MODE_DISABLED ; 
 struct tmc_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tmc_etr_disable_hw (struct tmc_drvdata*) ; 

__attribute__((used)) static void tmc_disable_etr_sink(struct coresight_device *csdev)
{
	unsigned long flags;
	struct tmc_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	spin_lock_irqsave(&drvdata->spinlock, flags);
	if (drvdata->reading) {
		spin_unlock_irqrestore(&drvdata->spinlock, flags);
		return;
	}

	/* Disable the TMC only if it needs to */
	if (drvdata->mode != CS_MODE_DISABLED) {
		tmc_etr_disable_hw(drvdata);
		drvdata->mode = CS_MODE_DISABLED;
	}

	spin_unlock_irqrestore(&drvdata->spinlock, flags);

	dev_info(drvdata->dev, "TMC-ETR disabled\n");
}