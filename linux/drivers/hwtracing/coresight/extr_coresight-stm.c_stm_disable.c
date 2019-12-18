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
struct stm_drvdata {int /*<<< orphan*/  mode; int /*<<< orphan*/  base; int /*<<< orphan*/  spinlock; } ;
struct perf_event {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct coresight_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_MODE_DISABLED ; 
 scalar_t__ CS_MODE_SYSFS ; 
 int /*<<< orphan*/  STMTCSR ; 
 int /*<<< orphan*/  STMTCSR_BUSY_BIT ; 
 int /*<<< orphan*/  coresight_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 struct stm_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 scalar_t__ local_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm_disable_hw (struct stm_drvdata*) ; 

__attribute__((used)) static void stm_disable(struct coresight_device *csdev,
			struct perf_event *event)
{
	struct stm_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	/*
	 * For as long as the tracer isn't disabled another entity can't
	 * change its status.  As such we can read the status here without
	 * fearing it will change under us.
	 */
	if (local_read(&drvdata->mode) == CS_MODE_SYSFS) {
		spin_lock(&drvdata->spinlock);
		stm_disable_hw(drvdata);
		spin_unlock(&drvdata->spinlock);

		/* Wait until the engine has completely stopped */
		coresight_timeout(drvdata->base, STMTCSR, STMTCSR_BUSY_BIT, 0);

		pm_runtime_put(csdev->dev.parent);

		local_set(&drvdata->mode, CS_MODE_DISABLED);
		dev_dbg(&csdev->dev, "STM tracing disabled\n");
	}
}