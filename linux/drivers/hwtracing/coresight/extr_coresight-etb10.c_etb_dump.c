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
struct etb_drvdata {scalar_t__ mode; TYPE_1__* csdev; int /*<<< orphan*/  spinlock; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CS_MODE_SYSFS ; 
 int /*<<< orphan*/  __etb_disable_hw (struct etb_drvdata*) ; 
 int /*<<< orphan*/  __etb_enable_hw (struct etb_drvdata*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  etb_dump_hw (struct etb_drvdata*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void etb_dump(struct etb_drvdata *drvdata)
{
	unsigned long flags;

	spin_lock_irqsave(&drvdata->spinlock, flags);
	if (drvdata->mode == CS_MODE_SYSFS) {
		__etb_disable_hw(drvdata);
		etb_dump_hw(drvdata);
		__etb_enable_hw(drvdata);
	}
	spin_unlock_irqrestore(&drvdata->spinlock, flags);

	dev_dbg(&drvdata->csdev->dev, "ETB dumped\n");
}