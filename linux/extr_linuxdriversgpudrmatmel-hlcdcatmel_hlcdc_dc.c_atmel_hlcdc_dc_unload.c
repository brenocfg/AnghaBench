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
struct drm_device {int /*<<< orphan*/  dev; struct atmel_hlcdc_dc* dev_private; } ;
struct atmel_hlcdc_dc {int /*<<< orphan*/  wq; TYPE_1__* hlcdc; } ;
struct TYPE_2__ {int /*<<< orphan*/  periph_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_atomic_helper_shutdown (struct drm_device*) ; 
 int /*<<< orphan*/  drm_fb_cma_fbdev_fini (struct drm_device*) ; 
 int /*<<< orphan*/  drm_irq_uninstall (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_fini (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atmel_hlcdc_dc_unload(struct drm_device *dev)
{
	struct atmel_hlcdc_dc *dc = dev->dev_private;

	drm_fb_cma_fbdev_fini(dev);
	flush_workqueue(dc->wq);
	drm_kms_helper_poll_fini(dev);
	drm_atomic_helper_shutdown(dev);
	drm_mode_config_cleanup(dev);

	pm_runtime_get_sync(dev->dev);
	drm_irq_uninstall(dev);
	pm_runtime_put_sync(dev->dev);

	dev->dev_private = NULL;

	pm_runtime_disable(dev->dev);
	clk_disable_unprepare(dc->hlcdc->periph_clk);
	destroy_workqueue(dc->wq);
}