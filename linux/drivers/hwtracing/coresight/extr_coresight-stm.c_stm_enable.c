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
struct stm_drvdata {int /*<<< orphan*/  spinlock; int /*<<< orphan*/  mode; } ;
struct perf_event {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct coresight_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_MODE_DISABLED ; 
 scalar_t__ CS_MODE_SYSFS ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 struct stm_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 scalar_t__ local_cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm_enable_hw (struct stm_drvdata*) ; 

__attribute__((used)) static int stm_enable(struct coresight_device *csdev,
		      struct perf_event *event, u32 mode)
{
	u32 val;
	struct stm_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	if (mode != CS_MODE_SYSFS)
		return -EINVAL;

	val = local_cmpxchg(&drvdata->mode, CS_MODE_DISABLED, mode);

	/* Someone is already using the tracer */
	if (val)
		return -EBUSY;

	pm_runtime_get_sync(csdev->dev.parent);

	spin_lock(&drvdata->spinlock);
	stm_enable_hw(drvdata);
	spin_unlock(&drvdata->spinlock);

	dev_dbg(&csdev->dev, "STM tracing enabled\n");
	return 0;
}