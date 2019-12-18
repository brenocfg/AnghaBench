#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct wlcore_platdev_data {TYPE_1__* family; } ;
struct wl1271 {TYPE_3__* dev; int /*<<< orphan*/  nvs_loading_complete; struct platform_device* pdev; int /*<<< orphan*/  ptable; int /*<<< orphan*/  ops; } ;
struct TYPE_10__ {TYPE_2__* driver; } ;
struct platform_device {TYPE_3__ dev; } ;
struct TYPE_9__ {int /*<<< orphan*/ * pm; } ;
struct TYPE_8__ {char* nvs_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FW_ACTION_HOTPLUG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 struct wlcore_platdev_data* dev_get_platdata (TYPE_3__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct wl1271*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (TYPE_3__*,int) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (TYPE_3__*) ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,TYPE_3__*,int /*<<< orphan*/ ,struct wl1271*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,struct wl1271*)) ; 
 int /*<<< orphan*/  wl1271_error (char*,char const*,int) ; 
 int /*<<< orphan*/  wlcore_nvs_cb (int /*<<< orphan*/ *,struct wl1271*) ; 
 int /*<<< orphan*/  wlcore_pm_ops ; 

int wlcore_probe(struct wl1271 *wl, struct platform_device *pdev)
{
	struct wlcore_platdev_data *pdev_data = dev_get_platdata(&pdev->dev);
	const char *nvs_name;
	int ret = 0;

	if (!wl->ops || !wl->ptable || !pdev_data)
		return -EINVAL;

	wl->dev = &pdev->dev;
	wl->pdev = pdev;
	platform_set_drvdata(pdev, wl);

	if (pdev_data->family && pdev_data->family->nvs_name) {
		nvs_name = pdev_data->family->nvs_name;
		ret = request_firmware_nowait(THIS_MODULE, FW_ACTION_HOTPLUG,
					      nvs_name, &pdev->dev, GFP_KERNEL,
					      wl, wlcore_nvs_cb);
		if (ret < 0) {
			wl1271_error("request_firmware_nowait failed for %s: %d",
				     nvs_name, ret);
			complete_all(&wl->nvs_loading_complete);
		}
	} else {
		wlcore_nvs_cb(NULL, wl);
	}

	wl->dev->driver->pm = &wlcore_pm_ops;
	pm_runtime_set_autosuspend_delay(wl->dev, 50);
	pm_runtime_use_autosuspend(wl->dev);
	pm_runtime_enable(wl->dev);

	return ret;
}