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
struct device {int dummy; } ;
struct cyttsp4 {TYPE_1__* cpdata; int /*<<< orphan*/  irq; int /*<<< orphan*/  startup_work; int /*<<< orphan*/  md; struct device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* init ) (TYPE_1__*,int /*<<< orphan*/ ,struct device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cyttsp4_free_si_ptrs (struct cyttsp4*) ; 
 int /*<<< orphan*/  cyttsp4_mt_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cyttsp4_stop_wd_timer (struct cyttsp4*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct cyttsp4*) ; 
 int /*<<< orphan*/  kfree (struct cyttsp4*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_suspend (struct device*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,struct device*) ; 

int cyttsp4_remove(struct cyttsp4 *cd)
{
	struct device *dev = cd->dev;

	cyttsp4_mt_release(&cd->md);

	/*
	 * Suspend the device before freeing the startup_work and stopping
	 * the watchdog since sleep function restarts watchdog on failure
	 */
	pm_runtime_suspend(dev);
	pm_runtime_disable(dev);

	cancel_work_sync(&cd->startup_work);

	cyttsp4_stop_wd_timer(cd);

	free_irq(cd->irq, cd);
	if (cd->cpdata->init)
		cd->cpdata->init(cd->cpdata, 0, dev);
	cyttsp4_free_si_ptrs(cd);
	kfree(cd);
	return 0;
}