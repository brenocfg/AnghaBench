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
struct etm_drvdata {int traceid; int /*<<< orphan*/  dev; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  base; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CS_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETMTRACEIDR ; 
 int ETM_TRACEID_MASK ; 
 int etm_readl (struct etm_drvdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int etm_get_trace_id(struct etm_drvdata *drvdata)
{
	unsigned long flags;
	int trace_id = -1;

	if (!drvdata)
		goto out;

	if (!local_read(&drvdata->mode))
		return drvdata->traceid;

	pm_runtime_get_sync(drvdata->dev);

	spin_lock_irqsave(&drvdata->spinlock, flags);

	CS_UNLOCK(drvdata->base);
	trace_id = (etm_readl(drvdata, ETMTRACEIDR) & ETM_TRACEID_MASK);
	CS_LOCK(drvdata->base);

	spin_unlock_irqrestore(&drvdata->spinlock, flags);
	pm_runtime_put(drvdata->dev);

out:
	return trace_id;

}