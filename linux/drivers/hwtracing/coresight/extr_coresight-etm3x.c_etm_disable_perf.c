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
struct etm_drvdata {scalar_t__ cpu; int /*<<< orphan*/  base; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct coresight_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CS_UNLOCK (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  coresight_disclaim_device_unlocked (int /*<<< orphan*/ ) ; 
 struct etm_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  etm_set_prog (struct etm_drvdata*) ; 
 int /*<<< orphan*/  etm_set_pwrdwn (struct etm_drvdata*) ; 
 scalar_t__ smp_processor_id () ; 

__attribute__((used)) static void etm_disable_perf(struct coresight_device *csdev)
{
	struct etm_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	if (WARN_ON_ONCE(drvdata->cpu != smp_processor_id()))
		return;

	CS_UNLOCK(drvdata->base);

	/* Setting the prog bit disables tracing immediately */
	etm_set_prog(drvdata);

	/*
	 * There is no way to know when the tracer will be used again so
	 * power down the tracer.
	 */
	etm_set_pwrdwn(drvdata);
	coresight_disclaim_device_unlocked(drvdata->base);

	CS_LOCK(drvdata->base);
}