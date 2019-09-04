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
struct etb_drvdata {int /*<<< orphan*/  dev; int /*<<< orphan*/  mode; int /*<<< orphan*/  spinlock; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct coresight_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_MODE_DISABLED ; 
 struct etb_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  etb_disable_hw (struct etb_drvdata*) ; 
 int /*<<< orphan*/  etb_dump_hw (struct etb_drvdata*) ; 
 int /*<<< orphan*/  local_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void etb_disable(struct coresight_device *csdev)
{
	struct etb_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);
	unsigned long flags;

	spin_lock_irqsave(&drvdata->spinlock, flags);
	etb_disable_hw(drvdata);
	etb_dump_hw(drvdata);
	spin_unlock_irqrestore(&drvdata->spinlock, flags);

	local_set(&drvdata->mode, CS_MODE_DISABLED);

	dev_info(drvdata->dev, "ETB disabled\n");
}