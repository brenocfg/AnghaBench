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
struct etmv4_drvdata {int sticky_enable; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  cpu; } ;
struct etm4_enable_arg {int rc; struct etmv4_drvdata* drvdata; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct coresight_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 struct etmv4_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  etm4_enable_hw_smp_call ; 
 int smp_call_function_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct etm4_enable_arg*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int etm4_enable_sysfs(struct coresight_device *csdev)
{
	struct etmv4_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);
	struct etm4_enable_arg arg = { 0 };
	int ret;

	spin_lock(&drvdata->spinlock);

	/*
	 * Executing etm4_enable_hw on the cpu whose ETM is being enabled
	 * ensures that register writes occur when cpu is powered.
	 */
	arg.drvdata = drvdata;
	ret = smp_call_function_single(drvdata->cpu,
				       etm4_enable_hw_smp_call, &arg, 1);
	if (!ret)
		ret = arg.rc;
	if (!ret)
		drvdata->sticky_enable = true;
	spin_unlock(&drvdata->spinlock);

	if (!ret)
		dev_dbg(&csdev->dev, "ETM tracing enabled\n");
	return ret;
}