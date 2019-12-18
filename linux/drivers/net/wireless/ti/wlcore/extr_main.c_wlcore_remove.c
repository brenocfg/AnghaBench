#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct wlcore_platdev_data {TYPE_2__* family; } ;
struct wl1271 {int /*<<< orphan*/  irq; TYPE_3__* dev; scalar_t__ irq_wake_enabled; int /*<<< orphan*/  wakeirq; int /*<<< orphan*/  initialized; int /*<<< orphan*/  nvs_loading_complete; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_12__ {TYPE_1__* driver; } ;
struct TYPE_11__ {scalar_t__ nvs_name; } ;
struct TYPE_10__ {int /*<<< orphan*/ * pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct wlcore_platdev_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_pm_clear_wake_irq (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  device_init_wakeup (TYPE_3__*,int) ; 
 int /*<<< orphan*/  disable_irq_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct wl1271*) ; 
 struct wl1271* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (TYPE_3__*) ; 
 int pm_runtime_get_sync (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (TYPE_3__*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl1271_unregister_hw (struct wl1271*) ; 
 int /*<<< orphan*/  wlcore_free_hw (struct wl1271*) ; 

int wlcore_remove(struct platform_device *pdev)
{
	struct wlcore_platdev_data *pdev_data = dev_get_platdata(&pdev->dev);
	struct wl1271 *wl = platform_get_drvdata(pdev);
	int error;

	error = pm_runtime_get_sync(wl->dev);
	if (error < 0)
		dev_warn(wl->dev, "PM runtime failed: %i\n", error);

	wl->dev->driver->pm = NULL;

	if (pdev_data->family && pdev_data->family->nvs_name)
		wait_for_completion(&wl->nvs_loading_complete);
	if (!wl->initialized)
		return 0;

	if (wl->wakeirq >= 0) {
		dev_pm_clear_wake_irq(wl->dev);
		wl->wakeirq = -ENODEV;
	}

	device_init_wakeup(wl->dev, false);

	if (wl->irq_wake_enabled)
		disable_irq_wake(wl->irq);

	wl1271_unregister_hw(wl);

	pm_runtime_put_sync(wl->dev);
	pm_runtime_dont_use_autosuspend(wl->dev);
	pm_runtime_disable(wl->dev);

	free_irq(wl->irq, wl);
	wlcore_free_hw(wl);

	return 0;
}