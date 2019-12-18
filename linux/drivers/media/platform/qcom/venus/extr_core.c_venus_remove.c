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
struct venus_core {int /*<<< orphan*/  v4l2_dev; struct device* dev; } ;
struct platform_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int hfi_core_deinit (struct venus_core*,int) ; 
 int /*<<< orphan*/  hfi_destroy (struct venus_core*) ; 
 int /*<<< orphan*/  of_platform_depopulate (struct device*) ; 
 struct venus_core* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  venus_firmware_deinit (struct venus_core*) ; 
 int /*<<< orphan*/  venus_shutdown (struct venus_core*) ; 

__attribute__((used)) static int venus_remove(struct platform_device *pdev)
{
	struct venus_core *core = platform_get_drvdata(pdev);
	struct device *dev = core->dev;
	int ret;

	ret = pm_runtime_get_sync(dev);
	WARN_ON(ret < 0);

	ret = hfi_core_deinit(core, true);
	WARN_ON(ret);

	hfi_destroy(core);
	venus_shutdown(core);
	of_platform_depopulate(dev);

	venus_firmware_deinit(core);

	pm_runtime_put_sync(dev);
	pm_runtime_disable(dev);

	v4l2_device_unregister(&core->v4l2_dev);

	return ret;
}