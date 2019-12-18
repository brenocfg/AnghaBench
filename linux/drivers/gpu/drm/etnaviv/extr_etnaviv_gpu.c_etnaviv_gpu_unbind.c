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
struct etnaviv_gpu {int initialized; int /*<<< orphan*/ * cooling; int /*<<< orphan*/  fence_idr; int /*<<< orphan*/ * drm; int /*<<< orphan*/  buffer; int /*<<< orphan*/  dev; int /*<<< orphan*/  wq; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_DRM_ETNAVIV_THERMAL ; 
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 struct etnaviv_gpu* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  etnaviv_cmdbuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  etnaviv_gpu_hw_suspend (struct etnaviv_gpu*) ; 
 int /*<<< orphan*/  etnaviv_iommu_global_fini (struct etnaviv_gpu*) ; 
 int /*<<< orphan*/  etnaviv_sched_fini (struct etnaviv_gpu*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync_suspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thermal_cooling_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void etnaviv_gpu_unbind(struct device *dev, struct device *master,
	void *data)
{
	struct etnaviv_gpu *gpu = dev_get_drvdata(dev);

	DBG("%s", dev_name(gpu->dev));

	flush_workqueue(gpu->wq);
	destroy_workqueue(gpu->wq);

	etnaviv_sched_fini(gpu);

#ifdef CONFIG_PM
	pm_runtime_get_sync(gpu->dev);
	pm_runtime_put_sync_suspend(gpu->dev);
#else
	etnaviv_gpu_hw_suspend(gpu);
#endif

	if (gpu->initialized) {
		etnaviv_cmdbuf_free(&gpu->buffer);
		etnaviv_iommu_global_fini(gpu);
		gpu->initialized = false;
	}

	gpu->drm = NULL;
	idr_destroy(&gpu->fence_idr);

	if (IS_ENABLED(CONFIG_DRM_ETNAVIV_THERMAL))
		thermal_cooling_device_unregister(gpu->cooling);
	gpu->cooling = NULL;
}