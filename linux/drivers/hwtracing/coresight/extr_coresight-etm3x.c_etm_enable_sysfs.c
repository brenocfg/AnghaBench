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
struct etm_enable_arg {int rc; struct etm_drvdata* drvdata; int /*<<< orphan*/  member_0; } ;
struct etm_drvdata {int sticky_enable; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  cpu; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct coresight_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ cpu_online (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 struct etm_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  etm_enable_hw_smp_call ; 
 int smp_call_function_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct etm_enable_arg*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int etm_enable_sysfs(struct coresight_device *csdev)
{
	struct etm_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);
	struct etm_enable_arg arg = { 0 };
	int ret;

	spin_lock(&drvdata->spinlock);

	/*
	 * Configure the ETM only if the CPU is online.  If it isn't online
	 * hw configuration will take place on the local CPU during bring up.
	 */
	if (cpu_online(drvdata->cpu)) {
		arg.drvdata = drvdata;
		ret = smp_call_function_single(drvdata->cpu,
					       etm_enable_hw_smp_call, &arg, 1);
		if (!ret)
			ret = arg.rc;
		if (!ret)
			drvdata->sticky_enable = true;
	} else {
		ret = -ENODEV;
	}

	spin_unlock(&drvdata->spinlock);

	if (!ret)
		dev_dbg(&csdev->dev, "ETM tracing enabled\n");
	return ret;
}