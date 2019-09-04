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
struct sysc {int /*<<< orphan*/  rsts; int /*<<< orphan*/ * dev; int /*<<< orphan*/  idle_work; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_platform_depopulate (int /*<<< orphan*/ *) ; 
 struct sysc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysc_unprepare (struct sysc*) ; 

__attribute__((used)) static int sysc_remove(struct platform_device *pdev)
{
	struct sysc *ddata = platform_get_drvdata(pdev);
	int error;

	cancel_delayed_work_sync(&ddata->idle_work);

	error = pm_runtime_get_sync(ddata->dev);
	if (error < 0) {
		pm_runtime_put_noidle(ddata->dev);
		pm_runtime_disable(ddata->dev);
		goto unprepare;
	}

	of_platform_depopulate(&pdev->dev);

	pm_runtime_put_sync(&pdev->dev);
	pm_runtime_disable(&pdev->dev);
	reset_control_assert(ddata->rsts);

unprepare:
	sysc_unprepare(ddata);

	return 0;
}