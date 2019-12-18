#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct etm_drvdata {int traceid; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  base; int /*<<< orphan*/  mode; TYPE_2__* csdev; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device* parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CS_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETMTRACEIDR ; 
 int ETM_TRACEID_MASK ; 
 int etm_readl (struct etm_drvdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int etm_get_trace_id(struct etm_drvdata *drvdata)
{
	unsigned long flags;
	int trace_id = -1;
	struct device *etm_dev;

	if (!drvdata)
		goto out;

	etm_dev = drvdata->csdev->dev.parent;
	if (!local_read(&drvdata->mode))
		return drvdata->traceid;

	pm_runtime_get_sync(etm_dev);

	spin_lock_irqsave(&drvdata->spinlock, flags);

	CS_UNLOCK(drvdata->base);
	trace_id = (etm_readl(drvdata, ETMTRACEIDR) & ETM_TRACEID_MASK);
	CS_LOCK(drvdata->base);

	spin_unlock_irqrestore(&drvdata->spinlock, flags);
	pm_runtime_put(etm_dev);

out:
	return trace_id;

}