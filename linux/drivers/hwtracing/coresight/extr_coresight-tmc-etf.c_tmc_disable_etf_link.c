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
struct tmc_drvdata {int /*<<< orphan*/  spinlock; int /*<<< orphan*/  mode; scalar_t__ reading; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct coresight_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_MODE_DISABLED ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 struct tmc_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tmc_etf_disable_hw (struct tmc_drvdata*) ; 

__attribute__((used)) static void tmc_disable_etf_link(struct coresight_device *csdev,
				 int inport, int outport)
{
	unsigned long flags;
	struct tmc_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	spin_lock_irqsave(&drvdata->spinlock, flags);
	if (drvdata->reading) {
		spin_unlock_irqrestore(&drvdata->spinlock, flags);
		return;
	}

	tmc_etf_disable_hw(drvdata);
	drvdata->mode = CS_MODE_DISABLED;
	spin_unlock_irqrestore(&drvdata->spinlock, flags);

	dev_dbg(&csdev->dev, "TMC-ETF disabled\n");
}